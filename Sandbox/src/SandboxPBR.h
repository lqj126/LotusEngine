#pragma once

#include <Lotus.h>

#include "imgui/imgui.h"
#include "Lotus/Renderer/Shader.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace Lotus
{
	class SandboxPBR : public Layer
	{
	public:
		SandboxPBR();

		virtual void OnAttach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Event& e) override;

	private:
		CameraController m_CameraController;
		bool m_isPerspective = true;

		ShaderLibrary m_ShaderLibrary;
		Ref<Shader> PBRShader;
		bool LoadTexture = true;
		Ref<Texture2D> albedo;
		Ref<Texture2D> normal;
		Ref<Texture2D> metallic;
		Ref<Texture2D> roughness;
		Ref<Texture2D> ao;

		glm::vec3 lightPositions[1] = {
			glm::vec3(0.0f, 0.0f, 10.0f),
		};
		glm::vec3 lightColors[1] = {
			glm::vec3(150.0f, 150.0f, 150.0f),
		};
		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;


		Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	};
}
