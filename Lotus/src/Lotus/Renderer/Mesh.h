#pragma once

#include "Lotus/Core/Core.h"
#include "Lotus/Renderer/Vertex.h"
#include "Lotus/Renderer/Texture.h"
#include "Lotus/Renderer/VertexArray.h"
#include "Lotus/Renderer/Material.h"
#include "Lotus/Renderer/Buffer.h"
#include "Lotus/Renderer/Shader.h"

namespace Lotus {

	class Mesh
	{
	public:
		Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector<uint32_t>& indices,
			const Ref<Material>& material = nullptr
		) :
			m_Vertices(vertices), m_Indices(indices), m_Material(material)
		{
			SetupMesh();
		}

		Mesh(Mesh&& other)
		{
			MoveMesh(std::move(other));
		}

		Mesh& operator=(Mesh&& other)
		{
			MoveMesh(std::move(other));
			return *this;
		}

		inline Ref<Material> GetMaterial() const { return m_Material; }
		inline Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
	private:
		void SetupMesh();
		void MoveMesh(Mesh&& other);
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		Ref<Material> m_Material;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
