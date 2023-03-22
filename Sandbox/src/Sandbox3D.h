#pragma once

#include "Lotus.h"

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
};

