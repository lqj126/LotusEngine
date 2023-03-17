#pragma once

#include "Lotus/Core/Layer.h"

#include "Lotus/Events/ApplicationEvent.h"
#include "Lotus/Events/KeyEvent.h"
#include "Lotus/Events/MouseEvent.h"

namespace Lotus {

	class Lotus_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}