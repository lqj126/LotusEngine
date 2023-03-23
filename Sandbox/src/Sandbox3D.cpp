#include "Sandbox3d.h"

#include "Lotus.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D()
	: Layer("Sandbox3D")
{

}

void Sandbox3D::OnAttach()
{
	m_VertexArray.reset(Lotus::VertexArray::Create());
	float vertices[] = {

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,

		-0.5f,  0.5f, 0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	};

	Lotus::Ref<Lotus::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Lotus::VertexBuffer::Create(vertices, sizeof(vertices)));
	Lotus::BufferLayout layout = {
		{ Lotus::ShaderDataType::Float3, "aPos" },
		{ Lotus::ShaderDataType::Float2, "aTexCoord" }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	uint32_t indices[] = {
		0, 1, 2, // Side 0
		2, 1, 3,
		5, 4, 7, 
		7, 4, 6, 
		1, 5, 3, 
		3, 5, 7, 
		4, 0, 6, 
		6, 0, 3, 
		4, 5, 0, 
		0, 5, 1, 
		2, 3, 6, 
		6, 3, 7, 
	};

	Lotus::Ref<Lotus::IndexBuffer> indexBuffer;
	indexBuffer.reset(Lotus::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	auto CubeShader = m_ShaderLibrary.Load("assets/shaders/Cube3D.glsl");
	m_Texture = Lotus::Texture2D::Create("assets/textures/Checkerboard.png");
	m_ChernoLogoTexture = Lotus::Texture2D::Create("assets/textures/ChernoLogo.png");

	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->Bind();
	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->UploadUniformInt("u_Texture", 0);

	Lotus::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = static_cast<std::shared_ptr<Lotus::Framebuffer>>(Lotus::Framebuffer::Create(fbSpec));
}

void Sandbox3D::OnDetach()
{

}
          
void Sandbox3D::OnUpdate(Lotus::Timestep ts)
{
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
	};
	m_Framebuffer->Bind();
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	// Render
	Lotus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Lotus::RenderCommand::Clear();
	auto CubeShader = m_ShaderLibrary.Get("Cube3D");

	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->Bind();
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 1280.0f / 720.0f, 0.1f, 100.0f);
	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->UploadUniformMat4("projection", projection);
	// camera/view transformation
	glm::mat4 view = camera.GetViewMatrix();
	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->UploadUniformMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, cubePositions[0]);
	float angle = 20.0f;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	std::dynamic_pointer_cast<Lotus::OpenGLShader>(CubeShader)->UploadUniformMat4("model", model);

	m_Texture->Bind();
	Lotus::Renderer::Submit(CubeShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Lotus::Renderer::Submit(CubeShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Lotus::Renderer::EndScene();
}

void Sandbox3D::OnImGuiRender()
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


		//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_ChernoLogoTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();

		ImGui::End();
	}
	else
	{
		ImGui::Begin("Settings");


		//ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_ChernoLogoTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	ImGui::Begin("Viewport");
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
	{
		m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

	}
	uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
	LT_WARN("{0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
	ImGui::Image((void*)textureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
	ImGui::End();
	ImGui::PopStyleVar();



	m_Framebuffer->Unbind();
}
void Sandbox3D::OnEvent(Lotus::Event& e)
{

}
