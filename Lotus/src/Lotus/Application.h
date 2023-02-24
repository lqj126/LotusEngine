#pragma once

#include "Core.h"

#include "Window.h"
#include "Lotus/LayerStack.h"
#include "Lotus/Events/Event.h"
#include "Lotus/Events/ApplicationEvent.h"

#include "Lotus/ImGui/ImGuiLayer.h"

#include "Lotus/Renderer/Shader.h"
#include "Lotus/Renderer/Buffer.h"
#include "Lotus/Renderer/VertexArray.h"

namespace Lotus {

	class LOTUS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}