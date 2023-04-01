#pragma once

#include "glm/glm.hpp"

#include "Lotus/Renderer/Buffer.h"

namespace Lotus {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;

		static inline BufferLayout GetLayout()
		{
			return {
				{ Lotus::ShaderDataType::Float3, "a_Position" },
				{ Lotus::ShaderDataType::Float3, "a_Normal" },
				{ Lotus::ShaderDataType::Float2, "a_TexCoord" }
			};
		}
	};

}

