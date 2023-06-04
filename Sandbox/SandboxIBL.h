#pragma once
/*
#include <Lotus.h>

#include "imgui/imgui.h"
#include "Lotus/Renderer/Shader.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Lotus/Renderer/IBLTemp.h"
namespace Lotus
{
	class SandboxIBL : public Layer
	{
	public:
		SandboxIBL();

		virtual void OnAttach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Event& e) override;

	private:
		CameraController m_CameraController;
		bool m_isPerspective = true;

		ShaderLibrary m_ShaderLibrary;
		Ref<Shader> IBLShader;
		bool LoadTexture = true;





		Ref<Framebuffer> m_Framebuffer;
		Ref<Framebuffer> m_CubemapFramebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
	private:
		#ifndef true
				// rusted iron
				Ref<Texture2D>ironAlbedoMap;
				Ref<Texture2D>ironNormalMap;
				Ref<Texture2D>ironMetallicMap;
				Ref<Texture2D>ironRoughnessMap;
				Ref<Texture2D>ironAOMap;

				// gold
				Ref<Texture2D>goldAlbedoMap;
				Ref<Texture2D>goldNormalMap;
				Ref<Texture2D>goldMetallicMap;
				Ref<Texture2D>goldRoughnessMap;
				Ref<Texture2D>goldAOMap;

				// copper
				Ref<Texture2D>grassAlbedoMap;
				Ref<Texture2D>grassNormalMap;
				Ref<Texture2D>grassMetallicMap;
				Ref<Texture2D>grassRoughnessMap;
				Ref<Texture2D>grassAOMap;

				// spaceship
				Ref<Texture2D>plasticAlbedoMap;
				Ref<Texture2D>plasticNormalMap;
				Ref<Texture2D>plasticMetallicMap;
				Ref<Texture2D>plasticRoughnessMap;
				Ref<Texture2D>plasticAOMap;

				// wall
				Ref<Texture2D>wallAlbedoMap;
				Ref<Texture2D>wallNormalMap;
				Ref<Texture2D>wallMetallicMap;
				Ref<Texture2D>wallRoughnessMap;
				Ref<Texture2D>wallAOMap;
		#endif
	};
}
*/