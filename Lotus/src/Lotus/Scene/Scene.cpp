#include "ltpch.h"
#include "Scene.h"

#include "Components.h"
#include "Lotus/Renderer/Renderer2D.h"
#include "Lotus/Renderer/Renderer.h"

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

	void Scene::RemoveEntity(Entity& entity)
	{
		m_Registry.destroy(entity.GetEntityHandle());
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
		}

		auto view = m_Registry.view<ModelComponent, TransformComponent>();
		for (auto entity : view)
		{
			auto& [c_model] = view.get<ModelComponent>(entity);
			auto& [Position, Rotation, Scale, Angle] = view.get<TransformComponent>(entity);

			auto& Model = c_model;
			glm::vec3 m_ModelPos = Position;

			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_ModelPos);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(Angle), Rotation);
			modelMatrix = glm::scale(modelMatrix, Scale);
			Renderer::Submit(
				*Model, modelMatrix
			);
		}



	}

}