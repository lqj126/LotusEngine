#include "ltpch.h"
#include "Mesh.h"

namespace Lotus {

	void Mesh::SetupMesh()
	{
		m_VertexArray = Lotus::VertexArray::Create();

		m_VertexBuffer = Lotus::VertexBuffer::Create(
			reinterpret_cast<float*>(m_Vertices.data()),
			m_Vertices.size() * sizeof(Vertex)
		);
		m_VertexBuffer->SetLayout(Vertex::GetLayout());
		m_IndexBuffer = Lotus::IndexBuffer::Create(
			m_Indices.data(),
			m_Indices.size()
		);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();
	}

	void Mesh::MoveMesh(Mesh&& other)
	{
		m_Vertices = std::move(other.m_Vertices);
		m_Indices = std::move(other.m_Indices);
		m_Material = std::move(other.m_Material);

		m_VertexArray = std::move(other.m_VertexArray);
		m_VertexBuffer = std::move(other.m_VertexBuffer);
		m_IndexBuffer = std::move(other.m_IndexBuffer);
	}

	void Mesh::MoveMesh_PBR(Mesh&& other)
	{
		m_Vertices = std::move(other.m_Vertices);
		m_Indices = std::move(other.m_Indices);
		m_PBRMaterial = std::move(other.m_PBRMaterial);

		m_VertexArray = std::move(other.m_VertexArray);
		m_VertexBuffer = std::move(other.m_VertexBuffer);
		m_IndexBuffer = std::move(other.m_IndexBuffer);
	}

}
