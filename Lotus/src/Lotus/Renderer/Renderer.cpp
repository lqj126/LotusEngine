#include "ltpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Lotus {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	Ref<ShaderLibrary> Renderer::s_ShaderLibrary = CreateRef<ShaderLibrary>();

	Ref<ShaderLibrary> Renderer_PBR::s_ShaderLibrary = CreateRef<ShaderLibrary>();

	void Renderer::Init()
	{
		Renderer2D::Init();

		s_ShaderLibrary->Load("C:/Code/Lotus/Lotus/assets/shaders/Material.glsl");
		s_ShaderLibrary->Load("C:/Code/Lotus/Lotus/assets/shaders/Light.glsl");
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(
		const Camera& camera,
		// lighting
		const Ref<DirectionalLight>& directionalLight,
		const std::vector<Ref<PointLight>>& pointLights,
		const Ref<SpotLight>& spotLight,
		const int postProsess
	)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			// camera
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
			shader->SetFloat3("u_ViewPosition", camera.GetPosition());
			shader->SetInt("PostPorcess", postProsess);
			// directional light
			if (directionalLight)
			{
				directionalLight->Bind(shader);
			}
			shader->SetInt("u_PointLightCount", pointLights.size());
			for (int i = 0; i < pointLights.size(); ++i)
			{
				const auto& pointLight = pointLights[i];
				pointLight->Bind(shader, i);
			}
			if (spotLight)
			{
				shader->SetInt("u_SpotLightCount", 1); 
				spotLight->Bind(shader);
			}
		}
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(
		const Mesh& mesh,
		const glm::mat4& modelTransform
	)
	{
		auto shader = Lotus::Renderer::GetShaderLib()->Get("Material");
		mesh.GetMaterial()->Bind(shader);
		shader->SetMat4("u_Transform", modelTransform);
		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
		shader->SetMat3("u_TransformNormal", modelTransformNormal);

		DrawVertexArray(mesh.GetVertexArray());
	}

	void Renderer::Submit(
		const Model& model,
		const glm::mat4& modelTransform
	)
	{
		for (const Mesh& mesh : model.GetMeshes())
		{
			Submit(mesh, modelTransform);
		}
	}

	void Renderer::Submit(
		const Ref<VertexArray>& vertexArray, 
		const Ref<Light>& light, 
		const glm::mat4& modelTransform
	)
	{
		auto shader = Lotus::Renderer::GetShaderLib()->Get("Light");
		shader->Bind();
		shader->SetMat4("u_Transform", modelTransform);
		shader->SetFloat3("u_Color", light->GetColor());
		DrawVertexArray(vertexArray);
	}

	void Renderer::DrawVertexArray(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		if (vertexArray->GetIndexBuffer())
		{
			RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer()->GetCount());
		}
		else
		{
			RenderCommand::Draw(0, vertexArray->GetVertexCount());
		}
	}


	void Renderer_PBR::Init()
	{
		Renderer2D::Init();

		//s_ShaderLibrary->Load("C:/Code/Lotus/Lotus/assets/shaders/PBRShader.glsl");
		s_ShaderLibrary->Load("C:/Code/Lotus/Lotus/assets/shaders/PBRModelShader.glsl");
		s_ShaderLibrary->Load("C:/Code/Lotus/Lotus/assets/shaders/Light.glsl");
	}

	void Renderer_PBR::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer_PBR::BeginScene(
		const Camera& camera,
		// lighting
		const std::vector<Ref<PointLight_PBR>>& pointLights
	)
	{
		for (auto& [shaderName, shader] : Renderer_PBR::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			// camera
			shader->SetMat4("projection", camera.GetViewProjectionMatrix());
			shader->SetMat4("view", camera.GetViewMatrix());
			shader->SetFloat3("camPos", camera.GetPosition()); 
			glm::mat4 model = glm::mat4(1.0f);
			shader->SetMat4("model", model);

			for (unsigned int i = 0; i < pointLights.size(); i++)
			{
				const auto& pointLight = pointLights[i];
				pointLight->Bind(shader, i);
			}
		}
	}


	void Renderer_PBR::EndScene()
	{
	}

	void Renderer_PBR::Submit(
		const Mesh& mesh,
		const glm::mat4& modelTransform
	)
	{
		auto shader = Lotus::Renderer_PBR::GetShaderLib()->Get("PBRModelShader");
		mesh.GetPBRMaterial()->Bind(shader);
		/*
		shader->SetMat4("u_Transform", modelTransform);

		glm::mat3 modelTransformNormal = glm::transpose(glm::inverse(glm::mat3(modelTransform)));
		shader->SetMat3("u_TransformNormal", modelTransformNormal);
		*/
		DrawVertexArray(mesh.GetVertexArray());
	}


	void Renderer_PBR::Submit(
		const Mesh& mesh,
		const glm::mat4& modelTransform,
		bool isPBR
	)
	{
		LT_CORE_ASSERT(isPBR, "Renderer::Submit is  a PBR API");
		auto shader = Lotus::Renderer_PBR::GetShaderLib()->Get("PBRModelShader");
		mesh.GetPBRMaterial()->Bind(shader);
		shader->SetMat4("model", modelTransform);

		DrawVertexArray(mesh.GetVertexArray());
	}

	void Renderer_PBR::Submit(
		const Model_PBR& model,
		const glm::mat4& modelTransform
	)
	{
		for (const Mesh& mesh : model.GetMeshes())
		{
			Submit(mesh, modelTransform);
		}
	}

	void Renderer_PBR::Submit(const Ref<VertexArray>& vertexArray, const Ref<Light_PBR>& light, const glm::mat4& modelTransform)
	{
		auto shader = Lotus::Renderer_PBR::GetShaderLib()->Get("Light");
		shader->Bind();//TODO:should be deleted
		shader->SetMat4("u_Transform", modelTransform);
		shader->SetFloat3("u_Color", light->GetColor());
		DrawVertexArray(vertexArray);
	}

	void Renderer_PBR::DrawVertexArray(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		if (vertexArray->GetIndexBuffer())
		{
			RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer()->GetCount());
		}
		else
		{
			RenderCommand::Draw(0, vertexArray->GetVertexCount());
		}
	}
}