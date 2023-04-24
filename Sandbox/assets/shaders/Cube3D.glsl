//3DCube Texture Shader

#type vertex
	#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTexCoord;

	out vec2 TexCoord;
	uniform mat4 model;
	uniform mat4 view; 
	uniform mat4 projection; 

	void main()
	{
		gl_Position = projection*view*model*vec4(aPos.x,aPos.y,aPos.z, 1.0);
	}

#type fragment
	#version 330 core
	out vec4 FragColor;

	in vec2 TexCoord;

	// texture samplers
	uniform sampler2D u_Texture;

	void main()
	{
		FragColor = texture(u_Texture, TexCoord);
	}