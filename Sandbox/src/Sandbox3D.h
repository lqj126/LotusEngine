#pragma once

#include <Lotus.h>

#include "Lotus/Renderer/IBLTemp.h"
#include "imgui/imgui.h"
#include "../Panels/SceneHierarchyPanel.h"
#include <memory>
namespace Lotus
{
	class Sandbox3D : public Layer
	{
	public:
		Sandbox3D();

		virtual void OnAttach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnDetach() override;

		virtual void OnImGuiRender() override;

		virtual void OnEvent(Event& e) override;

	private:
		CameraController m_CameraController;
		bool m_isPerspective = true;
		Ref<Scene> m_ActiveScene0;
		Ref<Scene> m_ActiveScene1;
		Ref<Scene> m_ActiveScene2;

		std::vector<Entity> EntityList;
		SceneHierarchyPanel m_SceneHierarchyPanel;
		Ref<Model> m_Model;
		glm::vec3 m_ModelPos = { 0.0f, -1.3f, 0.0f };
		float m_ModelScale = 0.2f;

		Ref<DirectionalLight> m_DirectionalLight;
		struct {
			glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			float ambient = 0.1f;
			float diffuse = 1.0f;
			float specular = 1.0f;
		} m_DirectionalLightProp;

		std::vector<Ref<PointLight>> m_PointLights;
		struct PointLightProps
		{
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 position = glm::vec3(-0.2f, -1.0f, -0.3f);
			float ambient = 0.1f;
			float diffuse = 1.0f;
			float specular = 1.0f;
			float constant = 1.0f;
			float linear = 0.09f;
			float quadratic = 0.032f;
		};
		std::vector<PointLightProps> m_PointLightProps;
		Ref<VertexArray> m_PointLightVA;
		int m_PointLightActivated = 0;

		Ref<SpotLight> m_SpotLight;
		struct {
			glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
			float ambient = 0.1f;
			float diffuse = 1.0f;
			float specular = 1.0f;
			float constant = 1.0f;
			float linear = 0.09f;
			float quadratic = 0.032f;
			float cutOff = 12.5f;
			float epsilon = 5.0f;
		} m_SpotLightProp;

		Ref<Framebuffer> m_Framebuffer;
		Ref<Framebuffer> m_ScreenFramebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		//PBR
		Ref<Shader> PBRShader;
		bool LoadTexture = true;
		Ref<Texture2D> albedo;
		Ref<Texture2D> normal;
		Ref<Texture2D> metallic;
		Ref<Texture2D> roughness;
		Ref<Texture2D> ao;
		glm::vec3 lightPositions[4] = {
			glm::vec3(-10.0f,  10.0f, 10.0f),
			glm::vec3(10.0f,  10.0f, 10.0f),
			glm::vec3(-10.0f, -10.0f, 10.0f),
			glm::vec3(10.0f, -10.0f, 10.0f)
		};
		glm::vec3 lightColors[1] = {
			glm::vec3(150.0f, 150.0f, 150.0f),
		};
		int nrRows = 7;
		int nrColumns = 7;
		float spacing = 2.5;
		ShaderLibrary m_ShaderLibrary;
		//IBL

		//post-process
		Ref<Shader> PostProcessingShader;
		int process = 1;
	};
}