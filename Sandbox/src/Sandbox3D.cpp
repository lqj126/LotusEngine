#include "Sandbox3D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <numeric>
#include "Lotus/Renderer/IBLTemp.h"

namespace Lotus
{
	int Type = 1;
	IBLRenderer IBLRenderCtrl;

	Sandbox3D::Sandbox3D() :
		m_CameraController(
			true, (float)Lotus::DEFAULT_WINDOW_WIDTH / (float)Lotus::DEFAULT_WINDOW_HEIGHT
		), Layer("Sandbox3D")
	{
		float aspectRatio = (float)Lotus::DEFAULT_WINDOW_WIDTH / (float)Lotus::DEFAULT_WINDOW_HEIGHT;
	}

	void Sandbox3D::OnAttach()
	{
		Lotus::Renderer::Init();
		//m_Model = Lotus::CreateRef<Lotus::Model>("C:/Code/Lotus/Sandbox/assets/models/sponza/sponza.obj");
		//m_Model = Lotus::CreateRef<Lotus::Model>("C:/Users/BlueStoneLotus/Downloads/SciFiRoom_max_3ds/Scifi.3DS");

		//lighting

		// directional light
		m_DirectionalLight = Lotus::CreateRef<Lotus::DirectionalLight>(
			m_DirectionalLightProp.color, m_DirectionalLightProp.direction,
			m_DirectionalLightProp.ambient, m_DirectionalLightProp.diffuse, m_DirectionalLightProp.specular
			);

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
		Lotus::Ref<Lotus::VertexBuffer> pointLightVB = Lotus::VertexBuffer::Create(lightVertices, sizeof(lightVertices));
		pointLightVB->SetLayout({
			{ Lotus::ShaderDataType::Float3, "a_Position" }
			});
		// vertices array
		m_PointLightVA = Lotus::VertexArray::Create();
		m_PointLightVA->AddVertexBuffer(pointLightVB);
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};
		for (int i = 0; i < 4; ++i)
		{
			PointLightProps prop = PointLightProps();
			prop.position = pointLightPositions[i];
			m_PointLightProps.push_back(prop);

			m_PointLights.push_back(Lotus::CreateRef<Lotus::PointLight>(
				prop.color, prop.position,
				prop.ambient, prop.diffuse, prop.specular,
				prop.constant, prop.linear, prop.quadratic
				));
		}

		// spot light
		m_SpotLight = Lotus::CreateRef<Lotus::SpotLight>(
			m_SpotLightProp.color, m_CameraController.GetCamera().GetPosition(), -m_CameraController.GetCamera().GetZAxis(),
			m_SpotLightProp.ambient, m_SpotLightProp.diffuse, m_SpotLightProp.specular,
			m_SpotLightProp.constant, m_SpotLightProp.linear, m_SpotLightProp.quadratic,
			glm::cos(glm::radians(m_SpotLightProp.cutOff)), glm::cos(glm::radians(m_SpotLightProp.cutOff + m_SpotLightProp.epsilon))
			);

		// view phong illumination clearly
		m_CameraController.SetPosition({ 0.0f, 0.0f, 8.0f });
		m_CameraController.SetRotation(glm::normalize(glm::quat(1.0f, 0.09f, 0.04f, 0.0f)));

		//*********************************************************************************
		Renderer_PBR::Init();
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

		albedo = Texture2D::Create("assets/textures/PBRBall/albedo.png");
		normal = Texture2D::Create("assets/textures/PBRBall/normal.png");
		metallic = Texture2D::Create("assets/textures/PBRBall/metallic.png");
		roughness = Texture2D::Create("assets/textures/PBRBall/roughness.png");
		ao = Texture2D::Create("assets/textures/PBRBall/ao.png");

		PBRShader->SetMat4("projection", m_CameraController.GetCamera().GetProjectionMatrix());

		m_ActiveScene0 = CreateRef<Scene>(); 
		auto e_model = m_ActiveScene0->CreateEntity("Model");
		auto& c_model = e_model.AddComponent<ModelComponent>();
		auto& CMP = e_model.GetComponent<ModelComponent>().Model;
		CMP = CreateRef<Model>("C:/Code/Lotus/Sandbox/assets/models/sponza/sponza.obj");
		//CMP = CreateRef<Model>("C:/Code/Lotus/Sandbox/assets/models/nanosuit/nanosuit.obj");
		//CMP = CreateRef<Model>("C:/Code/Lotus/Sandbox/assets/models/blueball/wooden_sphere.obj");

		Lotus::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = static_cast<std::shared_ptr<Lotus::Framebuffer>>(Lotus::Framebuffer::Create(fbSpec));

		IBLRenderCtrl.setupIBL(m_CameraController, fbSpec);
		//post-process
		PostProcessingShader = m_ShaderLibrary.Load("C:/Code/Lotus/Lotus/assets/shaders/PostProsess/PostProcessingShader.glsl");
		m_SceneHierarchyPanel.SetContext(m_ActiveScene0);
	}

	void Sandbox3D::OnUpdate(Lotus::Timestep ts)
	{
		m_CameraController.OnUpdate(ts);

		m_Framebuffer->Bind();
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();

		Lotus::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Lotus::RenderCommand::Clear();

		m_CameraController.SetPerspective(m_isPerspective);
		if(Type == 0)
		{
			m_DirectionalLight->SetColor(m_DirectionalLightProp.color);
			m_DirectionalLight->SetDirection(m_DirectionalLightProp.direction);
			m_DirectionalLight->SetIntensity(
				m_DirectionalLightProp.ambient,
				m_DirectionalLightProp.diffuse,
				m_DirectionalLightProp.specular
			);

			for (int i = 0; i < m_PointLights.size(); ++i)
			{
				m_PointLights[i]->SetColor(m_PointLightProps[i].color);
				m_PointLights[i]->SetPosition(m_PointLightProps[i].position);
				m_PointLights[i]->SetIntensity(
					m_PointLightProps[i].ambient,
					m_PointLightProps[i].diffuse,
					m_PointLightProps[i].specular
				);
				m_PointLights[i]->SetAttenuation(
					m_PointLightProps[i].constant,
					m_PointLightProps[i].linear,
					m_PointLightProps[i].quadratic
				);
			}

			m_SpotLight->SetColor(m_SpotLightProp.color);
			m_SpotLight->SetPosition(m_CameraController.GetCamera().GetPosition());
			m_SpotLight->SetDirection(-m_CameraController.GetCamera().GetZAxis());
			m_SpotLight->SetIntensity(
				m_SpotLightProp.ambient,
				m_SpotLightProp.diffuse,
				m_SpotLightProp.specular
			);
			m_SpotLight->SetAttenuation(
				m_SpotLightProp.constant,
				m_SpotLightProp.linear,
				m_SpotLightProp.quadratic
			);
			m_SpotLight->SetCutOffs(
				glm::cos(glm::radians(m_SpotLightProp.cutOff)),
				glm::cos(glm::radians(m_SpotLightProp.cutOff + m_SpotLightProp.epsilon))
			);
			/*
			auto lib = Renderer::GetShaderLib();
			auto shader = lib->Get("Material");
			shader->SetInt("PostPorcess", process);
			*/
			Lotus::Renderer::BeginScene(
				m_CameraController.GetCamera(),
				m_DirectionalLight, m_PointLights, m_SpotLight,
				process
			);


			glm::vec3 cubePositions[] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};
			/*
			for (unsigned int i = 0; i < 1; i++)
			{
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_ModelPos);
				modelMatrix = glm::translate(modelMatrix, cubePositions[i]);
				float angle = 20.0f * i;
				modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(m_ModelScale));
				Lotus::Renderer::Submit(
					*m_Model, modelMatrix
				);
			}
			*/

			//Scene update
			m_ActiveScene0->OnUpdate(ts);

			for (int i = 0; i < m_PointLights.size(); ++i)
			{
				Lotus::Renderer::Submit(
					m_PointLightVA, m_PointLights[i],
					glm::translate(glm::mat4(1.0f), m_PointLightProps[i].position)
				);
			}
			Lotus::Renderer::EndScene();
		}
		else if (Type == 1)
		{
			PBRShader->Bind();
			glm::mat4 view = m_CameraController.GetCamera().GetViewMatrix();
			PBRShader->SetMat4("view", view);
			PBRShader->SetFloat3("camPos", m_CameraController.GetCamera().GetPosition());

			if (LoadTexture)
			{
				albedo->Bind(0);
				normal->Bind(1);
				metallic->Bind(2);
				roughness->Bind(3);
				ao->Bind(4);
			}
			else
			{
				albedo->Unbind();
				normal->Bind(1);
				metallic->Bind(2);
				roughness->Bind(3);
				ao->Bind(4);
			}


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
		else if (Type == 2)
		{
			IBLRenderCtrl.renderLoop(m_CameraController, m_Framebuffer->GetSpecification());
		}
		if (0)
		{
			m_Framebuffer->Unbind();

			m_ScreenFramebuffer = static_cast<std::shared_ptr<Lotus::Framebuffer>>(
				Lotus::Framebuffer::Create(m_Framebuffer->GetSpecification())
				);
			m_ScreenFramebuffer->Bind();


			//PostProcessingShader->Create("C:/Code/Lotus/Lotus/assets/shaders/PostProsess/PostProcessingShader.glsl");
			PostProcessingShader->Bind();
			PostProcessingShader->SetInt("screenTexture", 0);
			Ref<Texture2D> screenTexture = Texture2D::Create(m_Framebuffer->GetSpecification().Width, m_Framebuffer->GetSpecification().Height, m_Framebuffer->GetColorAttachmentRendererID());
			screenTexture->Bind(0);
			Renderer2D::DrawScreen({ 0.0f, 0.0f,  0.0f }, { 0.8f, 0.8f }, textureID);
			uint32_t screenTextureID = m_Framebuffer->GetColorAttachmentRendererID();
			m_ScreenFramebuffer->Unbind();
			m_Framebuffer->Bind();
		}
	}

	void Sandbox3D::OnDetach()
	{
		m_Model.reset();

		m_DirectionalLight.reset();

		m_PointLightVA.reset();
		m_PointLights.clear();
		m_PointLightProps.clear();
	}

	void Sandbox3D::OnImGuiRender()
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
					bool open = false, save = false;
					if (ImGui::BeginMenu("Menu"))
					{
						if (ImGui::MenuItem("Open", NULL))
							open = true;
						if (ImGui::MenuItem("Save", NULL))
							save = true;

						ImGui::EndMenu();
					}
					if (ImGui::MenuItem("Exit")) Lotus::Application::Get().Close();
					ImGui::EndMenu();
				}

				ImGui::EndMenuBar();
			}

			m_SceneHierarchyPanel.OnImGuiRender();

			if (Type == 0)
			{
				ImGui::Begin("Directional Light");
				ImGui::DragFloat3("Direction", glm::value_ptr(m_DirectionalLightProp.direction), 0.1f);
				ImGui::SliderFloat3("Color", glm::value_ptr(m_DirectionalLightProp.color), 0.0f, 1.0f);
				ImGui::SliderFloat3("Intensity (Ambient, Diffuse, and Specular Light)", &(m_DirectionalLightProp.ambient), 0.0f, 1.0f);
				ImGui::End();

				ImGui::Begin("Point Lights");
				for (int i = 0; i < m_PointLights.size(); ++i)
				{
					std::string hint = std::to_string(i);
					ImGui::RadioButton(hint.c_str(), &m_PointLightActivated, i);
					if (i < m_PointLights.size() - 1)
					{
						ImGui::SameLine();
					}
				}
				ImGui::DragFloat3("Position", glm::value_ptr(m_PointLightProps[m_PointLightActivated].position), 0.1f);
				ImGui::SliderFloat3("Color", glm::value_ptr(m_PointLightProps[m_PointLightActivated].color), 0.0f, 1.0f);
				ImGui::SliderFloat3("Intensity (Ambient, Diffuse, and Specular Light)", &(m_PointLightProps[m_PointLightActivated].ambient), 0.0f, 1.0f);
				ImGui::SliderFloat3("Attenuation", &(m_PointLightProps[m_PointLightActivated].constant), 0.0f, 1.0f);
				ImGui::End();

				ImGui::Begin("Spot Light");
				ImGui::SliderFloat3("Color", glm::value_ptr(m_SpotLightProp.color), 0.0f, 1.0f);
				ImGui::SliderFloat3("Intensity (Ambient, Diffuse, and Specular Light)", &(m_SpotLightProp.ambient), 0.0f, 1.0f);
				ImGui::SliderFloat3("Attenuation", &(m_SpotLightProp.constant), 0.0f, 1.0f);
				ImGui::SliderFloat("Light CutOff", &m_SpotLightProp.cutOff, 0.0f, 90.0f);
				ImGui::SliderFloat("Light CutOff Epsilon", &m_SpotLightProp.epsilon, 0, 90.0f - m_SpotLightProp.cutOff);
				ImGui::End();

				ImGui::Begin("PostProcess");
				ImGui::InputInt("PostProcess Value", &process);
				ImGui::End();
	
			}
			else if (Type == 1)
			{
				ImGui::Begin("Point Lights");
				for (int i = 0; i < m_PointLights.size(); ++i)
				{
					std::string hint = std::to_string(i);
					ImGui::RadioButton(hint.c_str(), &m_PointLightActivated, i);
					if (i < m_PointLights.size() - 1)
					{
						ImGui::SameLine();
					}
				}
				ImGui::DragFloat3("Position", glm::value_ptr(m_PointLightProps[m_PointLightActivated].position), 0.1f);
				ImGui::SliderFloat3("Color", glm::value_ptr(m_PointLightProps[m_PointLightActivated].color), 0.0f, 1.0f);
				ImGui::SliderFloat3("Intensity (Ambient, Diffuse, and Specular Light)", &(m_PointLightProps[m_PointLightActivated].ambient), 0.0f, 1.0f);
				ImGui::SliderFloat3("Attenuation", &(m_PointLightProps[m_PointLightActivated].constant), 0.0f, 1.0f);
				ImGui::End();
			}
			else if (Type == 2)
			{
				ImGui::Begin("Point Lights");
				for (int i = 0; i < m_PointLights.size(); ++i)
				{
					std::string hint = std::to_string(i);
					ImGui::RadioButton(hint.c_str(), &m_PointLightActivated, i);
					if (i < m_PointLights.size() - 1)
					{
						ImGui::SameLine();
					}
				}
				ImGui::DragFloat3("Position", glm::value_ptr(m_PointLightProps[m_PointLightActivated].position), 0.1f);
				ImGui::SliderFloat3("Color", glm::value_ptr(m_PointLightProps[m_PointLightActivated].color), 0.0f, 1.0f);
				ImGui::SliderFloat3("Intensity (Ambient, Diffuse, and Specular Light)", &(m_PointLightProps[m_PointLightActivated].ambient), 0.0f, 1.0f);
				ImGui::SliderFloat3("Attenuation", &(m_PointLightProps[m_PointLightActivated].constant), 0.0f, 1.0f);
				ImGui::End();
			}
			ImGui::End();
			
		}

		ImGui::Begin("Camera Status");
		ImGui::Checkbox("Perspective", &m_isPerspective);
		// show the current camera state
		const glm::vec3& cameraPos = m_CameraController.GetCamera().GetPosition();
		ImGui::Text("Position: (%.1f, %.1f, %.1f)", cameraPos.x, cameraPos.y, cameraPos.z);
		ImGui::Text("AspectRatio: %.2f, Fovy: %.1f, Zoom: %.1f", m_CameraController.GetAspectRatio(), m_CameraController.GetFovy(), m_CameraController.GetZoomLevel());
		const glm::quat& cameraRotation = m_CameraController.GetCamera().GetRotation();
		ImGui::Text("Rotation: %.2f + %.2fi + %.2fj + %.2fk (Norm: %.2f)", cameraRotation.w, cameraRotation.x, cameraRotation.y, cameraRotation.z, glm::length(cameraRotation));
		const glm::vec3& cameraX = m_CameraController.GetCamera().GetXAxis();
		ImGui::Text("X: (%.2f, %.2f, %.2f)", cameraX.x, cameraX.y, cameraX.z);
		const glm::vec3& cameraY = m_CameraController.GetCamera().GetYAxis();
		ImGui::Text("Y: (%.2f, %.2f, %.2f)", cameraY.x, cameraY.y, cameraY.z);
		const glm::vec3& cameraZ = m_CameraController.GetCamera().GetZAxis();
		ImGui::Text("Z: (%.2f, %.2f, %.2f)", cameraZ.x, cameraZ.y, cameraZ.z);
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		}
		uint32_t TextureID = m_Framebuffer->GetColorAttachmentRendererID();
		LT_WARN("{0}, {1}", viewportPanelSize.x, viewportPanelSize.y);
		ImGui::Image((void*)TextureID, ImVec2{ viewportPanelSize.x, viewportPanelSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::Begin("SandboxType");

		if (ImGui::Button("SandboxPhong"))
		{
			Type = 0;
		}
		if (ImGui::Button("SandboxPBR"))
		{
			Type = 1;
		}
		if (ImGui::Button("SandboxPBR2"))
		{
			Type = 2;
		}
		ImGui::End();


		m_Framebuffer->Unbind();

	}

	void Sandbox3D::OnEvent(Lotus::Event& e)
	{
		m_CameraController.OnEvent(e);
	}
}