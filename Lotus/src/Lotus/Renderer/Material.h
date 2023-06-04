#pragma once

#include "Lotus/Core/Core.h"
#include <Lotus/Renderer/Texture.h>
#include <Lotus/Renderer/Shader.h>

#include <glm/glm.hpp>

namespace Lotus {

	class Material
	{
	public:
		Material(
			Ref<Texture2D> diffuseMap = nullptr,
			Ref<Texture2D> specularMap = nullptr,
			Ref<Texture2D> emissionMap = nullptr,
			float shininess = 32.0f
		);

		inline void SetDiffuseMap(Ref<Texture2D> texture)
		{
			m_DiffuseMap = texture;
		}
		inline void SetSpecularMap(Ref<Texture2D> texture)
		{
			m_SpecularMap = texture;
		}
		inline void SetEmissionMap(Ref<Texture2D> texture)
		{
			m_EmissionMap = texture;
		}

		void SetTextureMap(Ref<Texture2D> texture, Texture::Type type);

		inline float GetShininess() const { return  m_Shininess; }
		inline void SetShininess(float shininess) { m_Shininess = shininess; }

		void Bind(const Ref<Shader>& shader);
	private:
		static const int s_DiffuseSlot = 0;
		static const int s_SpecularSlot = 1;
		static const int s_EmissionSlot = 2;
	private:
		Ref<Texture2D> m_DiffuseMap;
		Ref<Texture2D> m_SpecularMap;
		Ref<Texture2D> m_EmissionMap;
		float m_Shininess;
	};

	class Material_PBR
	{
	public:
		Material_PBR(
			Ref<Texture2D> albedoMap = nullptr,
			Ref<Texture2D> normalMap = nullptr,
			Ref<Texture2D> metallicMap = nullptr,
			Ref<Texture2D> roughnessMap = nullptr,
			Ref<Texture2D> aoMap = nullptr
		);


		Material_PBR& operator=(Material_PBR&& other) {
			if (this != &other) {
				m_AlbedoMap = other.m_AlbedoMap;
				m_NormalMap = other.m_NormalMap;
				m_MetallicMap = other.m_MetallicMap;
				m_RoughnessMap = other.m_RoughnessMap;
				m_AoMap = other.m_AoMap;
			}
			return  *this;
		}

		inline void SetAlbedoMap(Ref<Texture2D> texture)
		{
			m_AlbedoMap = texture;
		}
		inline void SetNormalMap(Ref<Texture2D> texture)
		{
			m_NormalMap = texture;
		}
		inline void SetMetallicMap(Ref<Texture2D> texture)
		{
			m_MetallicMap = texture;
		}
		inline void SetRoughnessMap(Ref<Texture2D> texture)
		{
			m_RoughnessMap = texture;
		}		
		inline void SetAoMap(Ref<Texture2D> texture)
		{
			m_AoMap = texture;
		}

		inline Ref<Texture2D> GetAlbedoMap()
		{
			return m_AlbedoMap;
		}
		inline Ref<Texture2D> GetNormalMap()
		{
			 return m_NormalMap;
		}
		inline Ref<Texture2D> GetMetallicMap()
		{
			return m_MetallicMap;
		}
		inline Ref<Texture2D> GetRoughnessMap()
		{
			return m_RoughnessMap;
		}
		inline Ref<Texture2D> GetAoMap()
		{
			return m_AoMap;
		}

		void SetTextureMap(Ref<Texture2D> texture, Texture::Type_PBR type);



		void Bind(const Ref<Shader>& shader);
	private:
		static const int s_AlbedoSlot = 0;
		static const int s_NormalSlot = 1;
		static const int s_MetallicSlot = 2;
		static const int s_RoughnessSlot = 3;
		static const int s_AoSlot = 4;
	private:
		Ref<Texture2D>	m_AlbedoMap;
		Ref<Texture2D>	m_NormalMap;
		Ref<Texture2D>	m_MetallicMap;
		Ref<Texture2D>	m_RoughnessMap;
		Ref<Texture2D>	m_AoMap;
	};
}
