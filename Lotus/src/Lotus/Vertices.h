#pragma once
#include "ltpch.h"
#include "glm/glm.hpp"
#include "Lotus/Core.h"

float vertices[] = {
-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,

-0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,

-0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,

 0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,

-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, -0.5f, -0.5f,	0.8f, 0.6f, 0.3f, 1.0f,

-0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
 0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, 0.5f,		0.8f, 0.6f, 0.3f, 1.0f,
-0.5f, 0.5f, -0.5f,		0.8f, 0.6f, 0.3f, 1.0f
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.1f, 0.2f, 0.3f),
};

unsigned int indices[] = { // ע�⣬���Ǵ��㿪ʼ��! 
	0, 1, 3, // ��һ�������� 
	1, 2, 3 // �ڶ��������� 
};