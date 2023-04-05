#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Lotus/Renderer/Camera.h"
#include "Lotus/Scene/Entity.h"
#include "Lotus/Renderer/Texture.h"
#include "Lotus/Renderer/Mesh.h"
#include "Lotus/Renderer/Model.h"
#include "Lotus/Renderer/Material.h"
#include "Lotus/Renderer/Light.h"
#include "Lotus/Renderer/CameraController.h"

namespace Lotus {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::vec3 Position = glm::vec3(0.0f);
		//rotation here is radians
		glm::vec3 Rotation = glm::vec3(0.0f);

		glm::vec3 Scale = glm::vec3(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
			:Position(position), Rotation(rotation), Scale(scale)
		{}

		glm::mat4 GetTransform() const
		{
			glm::mat4  translation = glm::translate(glm::mat4(1.0f), Position);

			glm::mat4  ratation = glm::rotate(glm::mat4(1.0f), (Rotation.x), { 1.0f,0.0f,0.0f });
			ratation *= glm::rotate(ratation, (Rotation.y), { 0.0,1.0f,0.0f });
			ratation *= glm::rotate(ratation, (Rotation.z), { 0.0f,0.0f,1.0f });

			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
			return translation * ratation * scale;
		}

	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct ModelComponent
	{
		Lotus::Ref<Lotus::Model> Model;

		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent(const Ref<Lotus::Model> model)
			: Model(model) {}
	};

	struct MeshComponent
	{
		//TODO
		//use subMeh vector;
		//MeshSource now have the material ,SubMesh 

		Ref<Mesh> Mesh;
		Ref<Material>  Material;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		//temp know We Don't have any asset system,should have not instance in the Component 
		//Ref<Material> MeshMaterial;

	};
	
	struct DirLightComponent
	{
		Ref<DirectionalLight> DirLight;
		Ref<DirectionalLightProp> DirLightProp;

		DirLightComponent() = default;
		DirLightComponent(const DirLightComponent&) = default;
		DirLightComponent(const Ref<DirectionalLight> dirLight, Ref<DirectionalLightProp> dirLightProp)
			: DirLight(dirLight), DirLightProp(dirLightProp){}
	};
	
	struct PointLightComponent
	{
		/*
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
		*/
		Ref<VertexArray> m_PointLightVA;
		glm::vec3 pointLightPosition;
		Ref<PointLight> PLight;
		Ref<PointLightProps> PLightProps;

	
		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;
	};

	struct SpotLightComponent
	{
		Ref<SpotLight> SpLight;
		Ref<SpotLightProp> SpLightProp;
		Ref<CameraController> CamController;
	
		SpotLightComponent() = default;
		SpotLightComponent(const SpotLightComponent&) = default;
	};

	/*
	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		Ref<MaterialTable>  MaterialTable;
	};
	*/
}