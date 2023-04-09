#pragma once

#include "entt.hpp"
#include "glm/glm.hpp"

#include "Lotus/Core/Timestep.h"
#include "Lotus/Scene/SceneCamera.h"

namespace Lotus {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity GetCameraEntity();
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		template<typename T>
		void OnComponentAdd(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		friend class Entity;
	};


	struct SceneRendererCamera
	{
		SceneCamera camera;
		glm::mat4 viewMatrix;
		glm::vec3 Position;
	};

	//BlingPhong Material
	struct DirLight_temp
	{
		glm::vec3 Color;
		glm::vec3 Direction;
		float Diffuse_Intensity;
		float Specular_Intensity;
		float Ambient_Intensity;
	};
	struct PointLight_temp
	{
		glm::vec3 Color;
		glm::vec3 Position;

		float Diffuse_Intensity;
		float Specular_Intensity;
		float Ambient_Intensity;

		float Constant;
		float Linear;
		float Quadratic;

		float CutOff;
		float Epsilon;

	};

	struct SpotLight_temp
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
	};

	struct SceneInfo
	{
		DirLight_temp dirLight;
		PointLight_temp pointLight;
		SpotLight_temp spotLight;
		SceneRendererCamera sceneCamera;
	};



}