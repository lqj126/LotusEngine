#pragma once

#include "Core.h"

#include "Window.h"
#include "Lotus/Core/LayerStack.h"
#include "Lotus/Events/Event.h"
#include "Lotus/Events/ApplicationEvent.h"

#include "Lotus/Core/Timestep.h"

<<<<<<< HEAD:Lotus/src/Lotus/Core/Application.h
#include "Lotus/ImGui/ImGuiLayer.h"
=======
#include "Lotus/Renderer/Shader.h"
#include "Lotus/Renderer/Buffer.h"
#include "Lotus/Renderer/VertexArray.h"
<<<<<<< HEAD:Lotus/src/Lotus/Core/Application.h
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e:Lotus/src/Lotus/Application.h
=======
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e:Lotus/src/Lotus/Application.h

namespace Lotus {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
<<<<<<< HEAD:Lotus/src/Lotus/Core/Application.h
		float m_LastFrameTime = 0.0f;
=======


		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

<<<<<<< HEAD:Lotus/src/Lotus/Core/Application.h
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e:Lotus/src/Lotus/Application.h
=======
>>>>>>> 2b2bd744763595dbc2248baf9251b6cb29fc7e8e:Lotus/src/Lotus/Application.h
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}