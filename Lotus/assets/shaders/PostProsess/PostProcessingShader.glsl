//Post-Processing Shader

#type vertex

	#version 330 core
	layout (location = 0) in vec2 a_Position;
	layout (location = 1) in vec2 a_TexCoord;

	out vec2 TexCoords;

	void main()
	{
  	  TexCoords = a_TexCoord;
 	   gl_Position = vec4(a_Position.x, a_Position.y, 0.0, 1.0); 
	}  

#type fragment
	#version 330 core
	out vec4 FragColor;

	in vec2 TexCoords;

	uniform sampler2D screenTexture;

	void main()
	{
 	   vec3 col = vec3(1.0) - texture(screenTexture, TexCoords).rgb;
 	   FragColor = vec4(col, 1.0);
	} 