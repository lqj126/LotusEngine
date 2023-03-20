#include <Lotus.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Lotus::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(Lotus::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Lotus::Ref<Lotus::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lotus::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lotus::BufferLayout layout = {
			{ Lotus::ShaderDataType::Float3, "a_Position" },
			{ Lotus::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Lotus::Ref<Lotus::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lotus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lotus::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Lotus::Ref<Lotus::VertexBuffer> squareVB;
		squareVB.reset(Lotus::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Lotus::ShaderDataType::Float3, "a_Position" },
			{ Lotus::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Lotus::Ref<Lotus::IndexBuffer> squareIB;
		squareIB.reset(Lotus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Lotus::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Lotus::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Lotus::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = Lotus::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Lotus::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Lotus::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Lotus::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);
		m_Framebuffer->Bind();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		// Render
		Lotus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Lotus::RenderCommand::Clear();

		Lotus::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Lotus::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Lotus::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Lotus::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Lotus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Lotus::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Lotus::Renderer::Submit(m_Shader, m_VertexArray);

		Lotus::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		// Note: Switch this to true to enable dockspace
		static bool dockingEnabled = true;
		if (dockingEnabled)
		{
			static bool dockspaceOpen = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->Pos);
				ImGui::SetNextWindowSize(viewport->Size);
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}

			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					// Disabling fullscreen would allow the window to be moved to the front of other windows, 
					// which we can't undo at the moment without finer window depth/z control.
					//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

					if (ImGui::MenuItem("Exit")) Lotus::Application::Get().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			ImGui::Begin("Settings");


			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

			uint32_t textureID = m_ChernoLogoTexture->GetRendererID();
			ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
			ImGui::End();

			ImGui::End();
		}
		else
		{
			ImGui::Begin("Settings");


			ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

			uint32_t textureID = m_ChernoLogoTexture->GetRendererID();
			ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
			ImGui::End();
		}

// 		ImGui::Begin("Settings");
// 		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
// 		ImGui::End();
// 
		ImGui::Begin("m_viewport");

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		LT_WARN("{0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
		ImGui::Image((void*)textureID, ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
// 
/*		ImGui::End();*/

		m_Framebuffer->Unbind();
	}

	virtual void OnAttach() override 
	{
		//
		//m_CheckerboardTexture = Lotus::Texture2D::Create("assets/textures/Checkerboard.png");
		Lotus::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = static_cast<std::shared_ptr<Lotus::Framebuffer>>(Lotus::Framebuffer::Create(fbSpec));
	}

	void OnEvent(Lotus::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
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
};

class Sandbox : public Lotus::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Lotus::Application* Lotus::CreateApplication()
{
	return new Sandbox();
}