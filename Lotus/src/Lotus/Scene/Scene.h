#pragma once

#include "../entt/include/entt.hpp"

#include "Lotus/Core/Timestep.h"

namespace Lotus {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void RemoveEntity(Entity& entity);

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;

		friend class Entity;
		friend class SceneHierarchyPanel;
	};

}