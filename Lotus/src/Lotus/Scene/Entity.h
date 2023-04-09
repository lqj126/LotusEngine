#pragma once
#include "Lotus/Scene/Scene.h"
#include <entt.hpp>

namespace Lotus
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename ... Args>
		T& AddComponent(Args&&... args)
		{
			LT_ASSERT(!HasComponent<T>(), "Entity Already Have component ");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			LT_ASSERT(HasComponent<T>(), "Entity don't Have component ");
			return m_Scene->Reg().get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->Reg().all_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			LT_ASSERT(HasComponent<T>(), "Entity don't Have component ");
			m_Scene->Reg().remove<T>(m_EntityHandle);
		}


		operator bool() const { return (m_EntityHandle != entt::null) && m_Scene; }

		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		operator entt::entity() const { return m_EntityHandle; }

		bool operator== (const Entity& other) const { return other.m_EntityHandle == this->m_EntityHandle; }
		bool operator!= (const Entity& other) const { return !(*this == other); }

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}