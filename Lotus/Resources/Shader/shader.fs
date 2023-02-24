#version 330 core
out vec4 FragColor;

in vec4 VertexColor;

void main()
{
   FragColor = VertexColor; 
}