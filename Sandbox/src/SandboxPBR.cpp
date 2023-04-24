#include "SandboxPBR.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lotus/Renderer/RenderCommand.h"
#include <numeric>

namespace Lotus
{
	SandboxPBR::SandboxPBR() :
		m_CameraController(
			true, (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT
		), Layer("SandboxPBR")
	{
		float aspectRatio = (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT;
	}

	void SandboxPBR::OnAttach()
	{

		m_CameraController.SetPosition({ 0.0f, 0.0f, 5.0f });
		PBRShader = m_ShaderLibrary.Load("assets/shaders/PBRShader.glsl");
		//s_ShaderLibrary->Load("H:/Dev/Lotus/Sandbox/assets/shaders/PBRShader.glsl");
		//s_ShaderLibrary->Load("H:/Dev/Lotus/Sandbox/assets/shaders/lightShader.glsl");
		//PBRShader->Create("H:/Dev/Lotus/Sandbox/assets/shaders/PBRShader.glsl");
		//PBRShader = Renderer::GetShaderLib()->Get("PBRShader");
		PBRShader->Bind();

		PBRShader->SetInt("albedoMap", 0);
		PBRShader->SetInt("normalMap", 1);
		PBRShader->SetInt("metallicMap", 2);
		PBRShader->SetInt("roughnessMap", 3);
		PBRShader->SetInt("aoMap", 4);

		albedo		= Texture2D::Create("assets/textures/PBRBall/albedo.png");
		normal		= Texture2D::Create("assets/textures/PBRBall/normal.png");
		metallic	= Texture2D::Create("assets/textures/PBRBall/metallic.png");
		roughness	= Texture2D::Create("assets/textures/PBRBall/roughness.png");
		ao			= Texture2D::Create("assets/textures/PBRBall/ao.png");

		PBRShader->SetMat4("projection", m_CameraController.GetCamera().GetProjectionMatrix());


		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = static_cast<std::shared_ptr<Framebuffer>>(Framebuffer::Create(fbSpec));
	}

	void SandboxPBR::OnUpdate(Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		m_Framebuffer->Bind();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		m_CameraController.SetPerspective(m_isPerspective);

		PBRShader->Bind();
		glm::mat4 view = m_CameraController.GetCamera().GetViewMatrix();
		PBRShader->SetMat4("view", view);
		PBRShader->SetFloat3("camPos", m_CameraController.GetCamera().GetPosition());

		albedo->Bind(0);
		normal->Bind(1);
		metallic->Bind(2);
		roughness->Bind(3);
		ao->Bind(4);

		glm::mat4 model = glm::mat4(1.0f);
		for (int row = 0; row < nrRows; ++row)
		{
			for (int col = 0; col < nrColumns; ++col)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(
					(float)(col - (nrColumns / 2)) * spacing,
					(float)(row - (nrRows / 2)) * spacing,
					0.0f
				));
				PBRShader->SetMat4("model", model);
				RenderCommand::DrawSphere();
			}
		}

		for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		{
			glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(ts * 5.0) * 5.0, 0.0, 0.0);
			newPos = lightPositions[i];
			PBRShader->SetFloat3("lightPositions[" + std::to_string(i) + "]", newPos);
			PBRShader->SetFloat3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

			model = glm::mat4(1.0f);
			model = glm::translate(model, newPos);
			model = glm::scale(model, glm::vec3(0.5f));
			PBRShader->SetMat4("model", model);
			RenderCommand::DrawSphere();
		}

		
	}

	void SandboxPBR::OnDetach()
	{

	}

	void SandboxPBR::OnImGuiRender()
	{
		//----------------------------------
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

					if (ImGui::MenuItem("Exit")) Application::Get().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}




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

	void SandboxPBR::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}

}
