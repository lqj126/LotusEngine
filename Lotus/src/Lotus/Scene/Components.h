#pragma once
#include <string>
#include <glm/glm.hpp>
#include "Lotus/Scene/Entity.h"
#include "Lotus/Scene/SceneCamera.h"

#include "Lotus/Renderer/Camera.h"
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
		Ref<Model> Model;
		glm::vec3 ModelPos;
		float ModelScale = 0.2f;
		float ModelAngle = 20.0f;

		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;
		ModelComponent(	const Ref<Lotus::Model> model, 
						glm::vec3 modelPos = { 0.0f, -1.3f, 0.0f }, 
						float modelScale = 0.2f, 
						float modelAngle = 20.0f)
			: Model(model), ModelPos(modelPos), ModelScale(modelScale), ModelAngle(modelAngle){}
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
		glm::vec3 Color;
		glm::vec3 Direction;
		float Diffuse_Intensity;
		float Specular_Intensity;
		float Ambient_Intensity;

		DirLightComponent() = default;
		DirLightComponent(const DirLightComponent&) = default;
	};

	struct PointLightComponent
	{
		glm::vec3 Color;
		glm::vec3 Position;
		float Diffuse_Intensity;
		float Specular_Intensity;
		float Ambient_Intensity;
		//衰减系数（常数，一次项，二次项）
		float Constant;
		float Linear;
		float Quadratic;

		PointLightComponent() = default;
		PointLightComponent(const PointLightComponent&) = default;
	};

	struct SpotLightComponent
	{
		glm::vec3 Color;

		float Diffuse_Intensity;
		float Specular_Intensity;
		float Ambient_Intensity;

		float Constant;
		float Linear;
		float Quadratic;

		float CutOff;
		float Epsilon;
	
		SpotLightComponent() = default;
		SpotLightComponent(const SpotLightComponent&) = default;
	};




	struct CameraComponent
	{
		Lotus::SceneCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	/*
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: think about moving to Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent&) = default;

		Ref<MaterialTable>  MaterialTable;
	};
	*/
}