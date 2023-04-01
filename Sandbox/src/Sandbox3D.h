#pragma once

#include <Lotus.h>

#include "imgui/imgui.h"

#include <memory>

class Sandbox3D : public Lotus::Layer
{
public:
	Sandbox3D();

	virtual void OnAttach() override;
	virtual void OnUpdate(Lotus::Timestep ts) override;
	virtual void OnDetach() override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Lotus::Event& e) override;

private:
	Lotus::CameraController m_CameraController;
	bool m_isPerspective = true;

	Lotus::Ref<Lotus::Model> m_Model;
	glm::vec3 m_ModelPos = { 0.0f, -1.3f, 0.0f };
	float m_ModelScale = 0.2f;

	Lotus::Ref<Lotus::DirectionalLight> m_DirectionalLight;
	struct {
		glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		float ambient = 0.1f;
		float diffuse = 1.0f;
		float specular = 1.0f;
	} m_DirectionalLightProp;

	std::vector<Lotus::Ref<Lotus::PointLight>> m_PointLights;
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
	Lotus::Ref<Lotus::VertexArray> m_PointLightVA;
	int m_PointLightActivated = 0;

	Lotus::Ref<Lotus::SpotLight> m_SpotLight;
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

	Lotus::Ref<Lotus::Texture2D> m_Texture;
	Lotus::Ref<Lotus::Framebuffer> m_Framebuffer;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};

