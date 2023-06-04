#include "SandboxPBRModel.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lotus/Renderer/RenderCommand.h"
#include "Lotus/Renderer/Shader.h"

#include <numeric>

namespace Lotus
{
	SandboxPBRModel::SandboxPBRModel() :
		m_CameraController(
			true, (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT
		), Layer("SandboxPBRModel")
	{
		float aspectRatio = (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT;
	}

	void SandboxPBRModel::OnAttach()
	{
		Renderer_PBR::Init();
		m_CameraController.SetPosition({ 0.0f, 0.0f, 5.0f });
		//m_Model_PBR = CreateRef<Model_PBR>("C:/Users/17298/Desktop/gun/lee_enfield_mk1.obj");
		//m_Model_PBR = CreateRef<Model_PBR>("C:/Users/17298/Desktop/Helmet/Helmet.obj");
		m_Model_PBR = CreateRef<Model_PBR>(
			"C:/Users/17298/Downloads/TinyPBR-main/Resources/Models/Helmet/Helmet.gltf");

		auto& mesh = const_cast<Mesh&>(m_Model_PBR->GetMeshes()[0]);

		auto m_ModelVB = m_Model_PBR->GetMeshes()[0].GetVertexArray()->GetVertexBuffers();
		auto m_ModelVA = m_Model_PBR->GetMeshes()[0].GetVertexArray();
		m_ModelVA->AddVertexBuffer(m_ModelVB[0]);

		albedo = Texture2D::Create("C:/Users/17298/Desktop/Helmet/Default_albedo.jpg");
		normal = Texture2D::Create("C:/Users/17298/Desktop/Helmet/Default_normal.jpg");
		metallic = Texture2D::Create("C:/Users/17298/Desktop/Helmet/Default_emissive.jpg");
		roughness = Texture2D::Create("C:/Users/17298/Desktop/Helmet/Default_metalRoughness.jpg");
		ao = Texture2D::Create("C:/Users/17298/Desktop/Helmet/Default_AO.jpg");
		/*
		albedo =			Texture2D::Create("C:/Users/17298/Desktop/gun/textures/lee_enfield_mk1_Albedo.png");
		normal =			Texture2D::Create("C:/Users/17298/Desktop/gun/textures/lee_enfield_mk1_Normal.png");
		metallic =		Texture2D::Create("C:/Users/17298/Desktop/gun/textures/lee_enfield_mk1_Metalness.png");
		roughness =	Texture2D::Create("C:/Users/17298/Desktop/gun/textures/lee_enfield_mk1_Roughness.png");
		ao =					Texture2D::Create("C:/Users/17298/Desktop/gun/textures/lee_enfield_mk1_AO.png");
			*/
		Ref<Material_PBR> material = CreateRef<Material_PBR>(
			albedo, normal, metallic, roughness, ao
		);
	

		mesh.SetPBRMaterial(material);



		// point light
		float lightVertices[] = {
			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,

			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,

			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,

			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f
		};
		Ref<VertexBuffer> pointLightVB = VertexBuffer::Create(lightVertices, sizeof(lightVertices));
		pointLightVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
			});

		m_PointLightVA = Lotus::VertexArray::Create();
		m_PointLightVA->AddVertexBuffer(pointLightVB);
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		m_PBRPointLights.push_back(CreateRef<PointLight_PBR>(
			glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 10.0f)
			));

		m_CameraController.SetPosition({ 0.0f, 0.0f, 0.0f });
		m_CameraController.SetRotation(glm::normalize(glm::quat(1.0f, 0.09f, 0.04f, 0.0f)));

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = static_cast<std::shared_ptr<Framebuffer>>(Framebuffer::Create(fbSpec));
	}

	void SandboxPBRModel::OnUpdate(Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		m_Framebuffer->Bind();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		m_CameraController.SetPerspective(m_isPerspective);

		for (int i = 0; i < m_PBRPointLights.size(); ++i)
		{
			m_PBRPointLights[i]->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
			m_PBRPointLights[i]->SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
		}
		Renderer_PBR::BeginScene(
			m_CameraController.GetCamera(),
			m_PBRPointLights
		);

		//
		Renderer_PBR::Submit(
			m_Model_PBR->GetMeshes()[0],
			glm::translate(glm::mat4(1.0f), glm::vec3(-0.2f, -1.0f, -0.3f)),
			true
		);


		Lotus::Renderer_PBR::EndScene();
	}

	void SandboxPBRModel::OnDetach()
	{
		m_Model_PBR.reset();
		m_PBRPointLights.clear();
	}

	void SandboxPBRModel::OnImGuiRender()
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
			ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
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

		ImGui::Begin("Texture Option");
		//ImGui::Checkbox("Loaded Texture", &LoadTexture);
		ImGui::Text("This is a test");
		ImGui::End();


		m_Framebuffer->Unbind();

	}

	void SandboxPBRModel::OnEvent(Event& e)
	{
		m_CameraController.OnEvent(e);
	}

}
