#include "ltpch.h"
#include "Material.h"
#include "Renderer.h"

namespace Lotus {

	Material::Material(Ref<Texture2D> diffuseMap, Ref<Texture2D> specularMap, Ref<Texture2D> emissionMap, float shininess)
		: m_Shininess(shininess)
	{
		// create the black texture as default specular and emission map
		auto blackTexture = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_DiffuseMap = (diffuseMap) ? diffuseMap : blackTexture;
		m_SpecularMap = (specularMap) ? specularMap : blackTexture;
		m_EmissionMap = (emissionMap) ? emissionMap : blackTexture;

	}

	void Material::SetTextureMap(Ref<Texture2D> texture, Texture::Type type)
	{
		switch (type)
		{
		case Texture::Type::Diffuse:
			SetDiffuseMap(texture);
			break;
		case Texture::Type::Specular:
			SetSpecularMap(texture);
			break;
		case Texture::Type::Emission:
			SetEmissionMap(texture);
			break;
		default:
			LT_CORE_ASSERT(false, "Unknown texture type!");
		}
	}

	void Material::Bind(const Ref<Shader>& shader)
	{
		shader->Bind();

		// diffuse
		LT_CORE_ASSERT(m_DiffuseMap, "Material has no diffuse map!");
		m_DiffuseMap->Bind(s_DiffuseSlot);
		shader->SetInt("u_Material.diffuse", s_DiffuseSlot);
		// specular
		m_SpecularMap->Bind(s_SpecularSlot);
		shader->SetInt("u_Material.specular", s_SpecularSlot);
		shader->SetFloat("u_Material.shininess", m_Shininess);
		// emission
		m_EmissionMap->Bind(s_EmissionSlot);
		shader->SetInt("u_Material.emission", s_EmissionSlot);

		m_DiffuseMap->Bind(s_DiffuseSlot);
	}

	Material_PBR::Material_PBR(
		Ref<Texture2D> albedoMap,
		Ref<Texture2D> normalMap,
		Ref<Texture2D> metallicMap,
		Ref<Texture2D> roughnessMap,
		Ref<Texture2D> aoMap
	)
	{
		// create the black texture as default map
		auto blackTexture = Texture2D::CreateFlatColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_AlbedoMap = (albedoMap) ? albedoMap : blackTexture;
		m_NormalMap = (normalMap) ? normalMap : blackTexture;
		m_MetallicMap = (metallicMap) ? metallicMap : blackTexture;
		m_RoughnessMap = (roughnessMap) ? roughnessMap : blackTexture;
		m_AoMap = (aoMap) ? aoMap : blackTexture;
	}

	void Material_PBR::SetTextureMap(Ref<Texture2D> texture, Texture::Type_PBR type)
	{
		switch (type)
		{
		case Texture::Type_PBR::Albedo:
			SetAlbedoMap(texture);
			break;
		case Texture::Type_PBR::Normal:
			SetNormalMap(texture);
			break;
		case Texture::Type_PBR::Metallic:
			SetMetallicMap(texture);
			break;
		case Texture::Type_PBR::Roughness:
			SetRoughnessMap(texture);
			break;
		case Texture::Type_PBR::Ao:
			SetAoMap(texture);
			break;
		default:
			LT_CORE_ASSERT(false, "Unknown texture type!");
		}
	}

	void Material_PBR::Bind(const Ref<Shader>& shader)
	{
		shader->Bind();

		// albedo
		LT_CORE_ASSERT(m_AlbedoMap, "Material has no AlbedoMap!");
		m_AlbedoMap->Bind(s_AlbedoSlot);
		shader->SetInt("albedoMap", s_AlbedoSlot);
		// normal
		m_NormalMap->Bind(s_NormalSlot);
		shader->SetInt("normalMap", s_NormalSlot);
		// metallic
		m_MetallicMap->Bind(s_MetallicSlot);
		shader->SetInt("metallicMap", s_MetallicSlot);
		// roughness
		m_RoughnessMap->Bind(s_RoughnessSlot);
		shader->SetInt("roughnessMap", s_RoughnessSlot);
		// ao
		m_AoMap->Bind(s_AoSlot);
		shader->SetInt("aoMap", s_AoSlot);
	}
}

