#include "ltpch.h"
#include "Scene.h"

#include "Components.h"
#include "Lotus/Renderer/Renderer2D.h"
#include "Lotus/Renderer/Renderer.h"
#include "Lotus/Renderer/Light.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Lotus {
	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		Entity cameraEntity = GetCameraEntity();
		//SceneInfo
		SceneInfo sceneinfo = {};

		CameraComponent& cameraCMP = cameraEntity.GetComponent<CameraComponent>();
		cameraCMP.Camera.SetPosition({ 0, 0, 1.0f });

		sceneinfo.sceneCamera.camera = cameraCMP.Camera;
		glm::mat4 Cameratransform = cameraEntity.GetComponent<TransformComponent>().GetTransform();
		glm::vec3 camaerapos = cameraEntity.GetComponent<TransformComponent>().Position;

		Ref<DirectionalLight> m_DirectionalLight;
		Ref<PointLight> m_PointLight;
		Ref<SpotLight> m_SpotLight;


		//Renderer preparation
		{
			//viePosition;
			sceneinfo.sceneCamera.Position = camaerapos;
			sceneinfo.sceneCamera.viewMatrix = glm::inverse(Cameratransform);
			//dirLight
			{
				auto view = m_Registry.view<DirLightComponent>();
				for (auto entity : view)
				{
					//auto& cameraComponent = view.get<CameraComponent>(entity);
					auto& dirlightCMP = view.get<DirLightComponent>(entity);
					sceneinfo.dirLight.Color				= dirlightCMP.Color;
					sceneinfo.dirLight.Direction			= dirlightCMP.Direction;
					sceneinfo.dirLight.Ambient_Intensity	= dirlightCMP.Ambient_Intensity;
					sceneinfo.dirLight.Diffuse_Intensity	= dirlightCMP.Diffuse_Intensity;
					sceneinfo.dirLight.Specular_Intensity	= dirlightCMP.Specular_Intensity;
					m_DirectionalLight = Lotus::CreateRef<Lotus::DirectionalLight>(
						sceneinfo.dirLight.Color,
						sceneinfo.dirLight.Direction,
						sceneinfo.dirLight.Ambient_Intensity,
						sceneinfo.dirLight.Diffuse_Intensity,
						sceneinfo.dirLight.Specular_Intensity
					);
					m_DirectionalLight->SetColor(sceneinfo.dirLight.Color);
					m_DirectionalLight->SetDirection(sceneinfo.dirLight.Direction);
					m_DirectionalLight->SetIntensity(
						sceneinfo.dirLight.Ambient_Intensity,
						sceneinfo.dirLight.Diffuse_Intensity,	
						sceneinfo.dirLight.Specular_Intensity
					);
				}

			}
			//pointLight
			{
				auto view = m_Registry.view<PointLightComponent>();
				for (auto entity : view)
				{
					auto& pointLightCMP = view.get<PointLightComponent>(entity);
					sceneinfo.pointLight.Color				= pointLightCMP.Color;
					sceneinfo.pointLight.Position			= pointLightCMP.Position;
					sceneinfo.pointLight.Diffuse_Intensity	= pointLightCMP.Diffuse_Intensity;
					sceneinfo.pointLight.Specular_Intensity	= pointLightCMP.Specular_Intensity;
					sceneinfo.pointLight.Ambient_Intensity	= pointLightCMP.Ambient_Intensity;
					sceneinfo.pointLight.Constant			= pointLightCMP.Constant;
					sceneinfo.pointLight.Linear				= pointLightCMP.Linear;
					sceneinfo.pointLight.Quadratic			= pointLightCMP.Quadratic;

					 m_PointLight = Lotus::CreateRef<Lotus::PointLight>(
					sceneinfo.pointLight.Color,
					sceneinfo.pointLight.Position,
					sceneinfo.pointLight.Diffuse_Intensity,
					sceneinfo.pointLight.Specular_Intensity,
					sceneinfo.pointLight.Ambient_Intensity,
					sceneinfo.pointLight.Constant,
					sceneinfo.pointLight.Linear,
					sceneinfo.pointLight.Quadratic
					);

					m_PointLight->SetColor(sceneinfo.pointLight.Color);
					m_PointLight->SetPosition(sceneinfo.pointLight.Position);
					m_PointLight->SetIntensity(
						sceneinfo.pointLight.Ambient_Intensity,
						sceneinfo.pointLight.Diffuse_Intensity,
						sceneinfo.pointLight.Specular_Intensity
					);
					m_PointLight->SetAttenuation(
						sceneinfo.pointLight.Constant,
						sceneinfo.pointLight.Linear,
						sceneinfo.pointLight.Quadratic
					);
					
				}
			}
			
			//spotLight
			{
				auto view = m_Registry.view<SpotLightComponent, CameraComponent>();
				for (auto entity : view)
				{
					auto [spotlightCMP, cameraCMP] = view.get(entity);
					sceneinfo.spotLight.Color				= spotlightCMP.Color;
					sceneinfo.spotLight.Diffuse_Intensity	= spotlightCMP.Diffuse_Intensity;
					sceneinfo.spotLight.Specular_Intensity	= spotlightCMP.Specular_Intensity;
					sceneinfo.spotLight.Ambient_Intensity	= spotlightCMP.Ambient_Intensity;
					sceneinfo.spotLight.Constant			= spotlightCMP.Constant;
					sceneinfo.spotLight.Linear				= spotlightCMP.Linear;
					sceneinfo.spotLight.Quadratic			= spotlightCMP.Quadratic;
					sceneinfo.spotLight.CutOff				= spotlightCMP.CutOff;
					sceneinfo.spotLight.Epsilon				= spotlightCMP.Epsilon;

					m_SpotLight = Lotus::CreateRef<Lotus::SpotLight>(
						sceneinfo.spotLight.Color,
						cameraCMP.Camera.GetPosition(), 
						-cameraCMP.Camera.GetZAxis(),
						sceneinfo.spotLight.Ambient_Intensity,
						sceneinfo.spotLight.Diffuse_Intensity,
						sceneinfo.spotLight.Specular_Intensity,
						sceneinfo.spotLight.Constant,
						sceneinfo.spotLight.Linear,
						sceneinfo.spotLight.Quadratic,
						glm::cos(glm::radians(spotlightCMP.CutOff)),
						glm::cos(glm::radians(spotlightCMP.CutOff + spotlightCMP.Epsilon))
						);

					m_SpotLight->SetColor(sceneinfo.spotLight.Color);
					m_SpotLight->SetPosition(cameraCMP.Camera.GetPosition());
					m_SpotLight->SetDirection(-cameraCMP.Camera.GetZAxis());
					m_SpotLight->SetIntensity(
						sceneinfo.spotLight.Ambient_Intensity,
						sceneinfo.spotLight.Diffuse_Intensity,
						sceneinfo.spotLight.Specular_Intensity
					);
					m_SpotLight->SetAttenuation(
						sceneinfo.spotLight.Constant,
						sceneinfo.spotLight.Linear,
						sceneinfo.spotLight.Quadratic
					);
					m_SpotLight->SetCutOffs(
						glm::cos(glm::radians(sceneinfo.spotLight.CutOff)),
						glm::cos(glm::radians(sceneinfo.spotLight.CutOff + sceneinfo.spotLight.Epsilon))
					);
				}
			}


		}

		std::vector<Lotus::Ref<Lotus::PointLight>> m_PointLights;
		m_PointLights.push_back(m_PointLight);
		//renderer
		Lotus::Renderer::BeginScene(
			sceneinfo.sceneCamera.camera,
			m_DirectionalLight, m_PointLights, m_SpotLight
		);

		{
			auto view = m_Registry.view<ModelComponent>();
			for (auto entity : view)
			{
				auto& [Model, ModelPos, ModelScale, ModelAngle] = view.get<ModelComponent>(entity);

				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), ModelPos);
				modelMatrix = glm::rotate(modelMatrix, glm::radians(ModelAngle), glm::vec3(1.0f, 0.3f, 0.5f));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(ModelScale));
				if (Model != NULL)
				{
					Renderer::Submit(
						*Model, modelMatrix
					);
				}
				else
				{
					LT_CORE_ERROR("Model does not exist!");
				}
		}


		}


		//others

		/*
		auto view = m_Registry.view<ModelComponent>();
		for (auto entity : view)
		{
			auto& [Model, ModelPos, ModelScale, ModelAngle] = view.get<ModelComponent>(entity);

			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), ModelPos);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(ModelAngle), glm::vec3(1.0f, 0.3f, 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(ModelScale));
			if (Model != NULL)
			{
				Renderer::Submit(
					*Model, modelMatrix
				);
			}
			else 
			{
				LT_CORE_ERROR("Model does not exist!");
			}
		}
		/*
		view = m_Registry.view<DirLightComponent>();
		for (auto entity : view)
		{
			auto& [DirLightProp] = view.get<DirLightComponent>(entity);



		}
		*/
	}

	Lotus::Entity Scene::GetCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraCMP = view.get<CameraComponent>(entity);
			if (cameraCMP.Primary)
			{
				return { entity ,this };
			}

		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdd(Entity entity, T& component)
	{
		static_assert(false);
	}


	template<>
	void Scene::OnComponentAdd<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdd<TransformComponent>(Entity entity, TransformComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdd<TagComponent>(Entity entity, TagComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdd<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdd<DirLightComponent>(Entity entity, DirLightComponent& component)
	{

	}

	template<>
	void Scene::OnComponentAdd<PointLightComponent>(Entity entity, PointLightComponent& component)
	{

	}

}