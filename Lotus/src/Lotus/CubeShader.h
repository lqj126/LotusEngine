#pragma once

std::string vertexSrc = R"(
#version 330 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 model;
uniform mat4 view; 
uniform mat4 projection; 

out vec4 VertexColor;

void main()
{
    gl_Position = projection*view*model*vec4(a_Position.x,a_Position.y,a_Position.z, 1.0);
    VertexColor = a_Color;
}
)";

std::string fragmentSrc = R"(
#version 330 core
out vec4 FragColor;

in vec4 VertexColor;

void main()
{
   FragColor = VertexColor; 
}
)";