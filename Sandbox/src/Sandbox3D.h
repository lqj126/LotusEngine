#pragma once

#include "Lotus.h"
#include "Lotus/Renderer/camera.h"


class Sandbox3D : public Lotus::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Lotus::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Lotus::Event & e) override;
private:
	Lotus::Ref<Lotus::VertexArray> m_VertexArray;
	Lotus::ShaderLibrary m_ShaderLibrary;
	Lotus::Ref<Lotus::Texture2D> m_Texture, m_ChernoLogoTexture;
	Lotus::Ref<Lotus::Framebuffer> m_Framebuffer;
	glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
};

