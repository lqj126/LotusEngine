#pragma once

#include "Lotus/Renderer/RenderCommand.h"

#include "Lotus/Renderer/OrthographicCamera.h"
#include "Lotus/Renderer/Shader.h"
#include "Lotus/Renderer/Material.h"

namespace Lotus {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Material>& material);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Material>& material);
	};

}

