#pragma once

#include "Lotus.h"

class Sandbox2D : public Lotus::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Lotus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Lotus::Event& e) override;
private:
	Lotus::ShaderLibrary m_ShaderLibrary;
	Lotus::Ref<Lotus::Shader> m_Shader;
	Lotus::Ref<Lotus::VertexArray> m_VertexArray;

	Lotus::Ref<Lotus::Shader> m_FlatColorShader;
	Lotus::Ref<Lotus::VertexArray> m_SquareVA;

	Lotus::Ref<Lotus::Texture2D> m_Texture, m_ChernoLogoTexture;
	Lotus::Ref<Lotus::Framebuffer> m_Framebuffer;
	Lotus::Ref<Lotus::Texture2D> m_TestTexture;
	Lotus::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};

