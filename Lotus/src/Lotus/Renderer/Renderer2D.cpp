#include "ltpch.h"
#include "Renderer2D.h"

#include "Lotus/Renderer/VertexArray.h"
#include "Lotus/Renderer/Shader.h"
#include "Lotus/Renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Lotus {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		RenderCommand::Init();

		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = Lotus::VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Lotus::Ref<Lotus::VertexBuffer> squareVB;
		squareVB = Lotus::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Lotus::ShaderDataType::Float3, "a_Position" },
			{ Lotus::ShaderDataType::Float2, "a_TexCoord" }
			});
		s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
		Lotus::Ref<Lotus::IndexBuffer> squareIB;
		squareIB = Lotus::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		for (auto& [shaderName, shader] : Renderer::GetShaderLib()->GetShaders())
		{
			shader->Bind();
			shader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		}
	}

	void Renderer2D::EndScene()
	{
	}

	static inline void SetPosSize(const Ref<Shader>& shader, const glm::vec3& position, const glm::vec2& size)
	{
		shader->SetMat4(
			"u_Transform",
			glm::scale(
				glm::translate(glm::mat4(1.0f), position),
				{ size.x, size.y, 1.0f }
			)
		);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Material>& material)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, material);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Material>& material)
	{
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray->GetIndexBuffer()->GetCount());
	}

	void Renderer2D::DrawScreen(const glm::vec3& position, const glm::vec2& size, const uint32_t& textureID)
	{
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray->GetIndexBuffer()->GetCount());
	}
}