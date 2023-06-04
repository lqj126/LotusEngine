#pragma once

#include "Lotus/Core/Core.h"
#include "Lotus/Renderer/Vertex.h"
#include "Lotus/Renderer/Texture.h"
#include "Lotus/Renderer/VertexArray.h"
#include "Lotus/Renderer/Material.h"
#include "Lotus/Renderer/Buffer.h"
#include "Lotus/Renderer/Shader.h"

namespace Lotus {
	static bool isPBR;
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
			isPBR = false;
			SetupMesh();
		}

		Mesh(
			const std::vector<Vertex>& vertices,
			const std::vector<uint32_t>& indices,
			const Ref<Material_PBR>& material = nullptr
		) :
			m_Vertices(vertices), m_Indices(indices), m_PBRMaterial(material)
		{
			isPBR = true;
			SetupMesh();
		}

		Mesh(Mesh&& other)
		{
			if (isPBR)
			{
				MoveMesh_PBR(std::move(other));
			}
			else
			{
				MoveMesh(std::move(other));
			}
		}

		Mesh& operator=(Mesh&& other)
		{
			if (isPBR)
			{
				MoveMesh_PBR(std::move(other));
			}
			else
			{
				MoveMesh(std::move(other));
			}
			return *this;
		}

		inline void SetPBRMaterial(Ref<Material_PBR> PBRmaterial)
		{
			m_PBRMaterial->SetAlbedoMap(PBRmaterial->GetAlbedoMap());
			m_PBRMaterial->SetNormalMap(PBRmaterial->GetNormalMap());
			m_PBRMaterial->SetMetallicMap(PBRmaterial->GetMetallicMap());
			m_PBRMaterial->SetRoughnessMap(PBRmaterial->GetRoughnessMap());
			m_PBRMaterial->SetAoMap(PBRmaterial->GetAoMap());
		}

		inline Ref<Material> GetMaterial() const { return m_Material; }
		inline Ref<Material_PBR> GetPBRMaterial() const { return m_PBRMaterial; }
		inline Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
	private:
		void SetupMesh();
		void MoveMesh(Mesh&& other);
		void MoveMesh_PBR(Mesh&& other);
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		Ref<Material> m_Material;
		Ref<Material_PBR> m_PBRMaterial;

		Ref<VertexArray> m_VertexArray;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};

}
