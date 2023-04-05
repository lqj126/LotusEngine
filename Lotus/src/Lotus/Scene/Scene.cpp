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

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			//Renderer2D::DrawQuad(transform, sprite.Color);
		}

		auto view = m_Registry.view<ModelComponent>();
		for (auto entity : view)
		{
			auto& [c_model] = view.get<ModelComponent>(entity);

			auto& Model = c_model;
			glm::vec3 m_ModelPos = { 0.0f, -1.3f, 0.0f };
			glm::vec3 cubePositions[] = {glm::vec3(0.0f,  0.0f,  0.0f), };


			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), m_ModelPos);
			modelMatrix = glm::translate(modelMatrix, cubePositions[0]);
			float angle = 20.0f * 0;
			modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
			Renderer::Submit(
				*Model, modelMatrix
			);
		}



	}

}