//PBR Texture Shader

#type vertex
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aTexCoords;

    out vec3 Normal;
    out vec2 TexCoords;
    out vec3 WorldPos;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    void main()
    {
        TexCoords = aTexCoords;
        WorldPos = vec3(model * vec4(aPos, 1.0));
        Normal = mat3(model) * aNormal;   

        gl_Position =  projection * view * vec4(WorldPos, 1.0);
    }

#type fragment
    #version 330 core
    out vec4 FragColor;
    in vec3 Normal;
    in vec2 TexCoords;
    in vec3 WorldPos;

    uniform vec3 CameraPosition;

    uniform vec3 lightPositions[3];
    uniform vec3 lightColors[3];
    uniform float lightIntensity[3];

    uniform sampler2D albedoMap;
    uniform sampler2D normalMap;
    uniform sampler2D metallicMap;
    uniform sampler2D roughnessMap;
    uniform sampler2D aoMap;

    const int metallicChannel = 0;
    const int roughnessChannel = 0;
    const int aoChannel = 0;
    const vec2 texMultiplier = {1.0, 1.0};

    const float PI = 3.14159265359;

    vec2 TextureCoords = TexCoords;

    vec3 getNormalFromMap()
    {
        vec3 tangentNormal = texture(normalMap, TextureCoords).xyz * 2.0 - 1.0;

        vec3 Q1  = dFdx(WorldPos);
        vec3 Q2  = dFdy(WorldPos);
        vec2 st1 = dFdx(TextureCoords);
        vec2 st2 = dFdy(TextureCoords);

        vec3 N   = normalize(Normal);
        vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
        vec3 B  = -normalize(cross(N, T));
        mat3 TBN = mat3(T, B, N);

        return normalize(TBN * tangentNormal);
    }

    float DistributionGGX(vec3 N, vec3 H, float roughness)
    {
        float a = roughness*roughness;
        float a2 = a*a;
        float NdotH = max(dot(N, H), 0.0);
        float NdotH2 = NdotH*NdotH;

        float nom   = a2;
        float denom = (NdotH2 * (a2 - 1.0) + 1.0);
        denom = PI * denom * denom;

        return nom / denom;
    }

    float GeometrySchlickGGX(float NdotV, float roughness)
    {
        float r = (roughness + 1.0);
        float k = (r*r) / 8.0;

        float nom   = NdotV;
        float denom = NdotV * (1.0 - k) + k;

        return nom / denom;
    }

    float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
    {
        float NdotV = max(dot(N, V), 0.0);
        float NdotL = max(dot(N, L), 0.0);
        float ggx2 = GeometrySchlickGGX(NdotV, roughness);
        float ggx1 = GeometrySchlickGGX(NdotL, roughness);

        return ggx1 * ggx2;
    }

    vec3 fresnelSchlick(float cosTheta, vec3 F0)
    {
        return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
    }

    void main()
    {
        TextureCoords = TextureCoords * texMultiplier;

        vec3 albedo = texture(albedoMap, TextureCoords).rgb;
        vec4 metallicTex = texture(metallicMap, TextureCoords);
        vec4 roughnessTex = texture(roughnessMap, TextureCoords);
        vec4 aoTex = texture(aoMap, TextureCoords);
        float metallic = metallicTex[metallicChannel];
        float roughness = roughnessTex[roughnessChannel];
        float ao = aoTex[aoChannel];

        if(texture(albedoMap, TextureCoords).a < 0.75)
        {
            discard;
        }

        if(metallic == 0.0)
        {
            metallic = 0.001;
        }

	    vec3 N = getNormalFromMap();
        vec3 V = normalize(CameraPosition - WorldPos);

        // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0 
        // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)    
        vec3 F0 = vec3(0.04); 
        F0 = mix(F0, albedo, metallic);

        // reflectance equation
        vec3 Lo = vec3(0.0);
        for(int i = 0; i < 3; ++i) 
        {
            // calculate per-light radiance
            vec3 L = normalize(lightPositions[i] - WorldPos);
            vec3 H = normalize(V + L);
            float distance = length(lightPositions[i] - WorldPos);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance = (lightColors[i] * lightIntensity[i]) * attenuation;

            // Cook-Torrance BRDF
            float NDF = DistributionGGX(N, H, roughness);   
            float G   = GeometrySmith(N, V, L, roughness);      
            vec3 F    = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);
           
            vec3 numerator    = NDF * G * F; 
            float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
            vec3 specular = numerator / denominator;
        
            // kS is equal to Fresnel
            vec3 kS = F;
            // for energy conservation, the diffuse and specular light can't
            // be above 1.0 (unless the surface emits light); to preserve this
            // relationship the diffuse component (kD) should equal 1.0 - kS.
            vec3 kD = vec3(1.0) - kS;
            // multiply kD by the inverse metalness such that only non-metals 
            // have diffuse lighting, or a linear blend if partly metal (pure metals
            // have no diffuse light).
            kD *= 1.0 - metallic;	  

            // scale light by NdotL
            float NdotL = max(dot(N, L), 0.0);        

            // add to outgoing radiance Lo
            Lo += (kD * albedo / PI + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
        }   
    
        // ambient lighting (note that the next IBL tutorial will replace 
        // this ambient lighting with environment lighting).
        vec3 ambient = vec3(0.0005) * albedo;
        if(ao > 0.001)
        {
            ambient *= ao;
        }

        vec3 color = ambient + Lo;

        // HDR tonemapping
        color = color / (color + vec3(1.0));
        // gamma correct
        color = pow(color, vec3(1.0/2.2)); 

        FragColor = vec4(color, 1.0);
    }