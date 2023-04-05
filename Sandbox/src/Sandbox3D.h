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
	Lotus::DirectionalLightProp m_DirectionalLightProp;

	std::vector<Lotus::Ref<Lotus::PointLight>> m_PointLights;

	std::vector<Lotus::PointLightProps> m_PointLightProps;
	Lotus::Ref<Lotus::VertexArray> m_PointLightVA;
	int m_PointLightActivated = 0;

	Lotus::Ref<Lotus::SpotLight> m_SpotLight;
	Lotus::SpotLightProp m_SpotLightProp;

	Lotus::Ref<Lotus::Texture2D> m_Texture;
	Lotus::Ref<Lotus::Framebuffer> m_Framebuffer;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };


	Lotus::Ref<Lotus::Scene> m_ActiveScene;
	Lotus::Ref<Lotus::Entity> m_ModelEntity;
	Lotus::Entity m_LightEntity;
	Lotus::Entity m_CameraEntity;
	//Lotus::Entity m_ModelEntity;
};

