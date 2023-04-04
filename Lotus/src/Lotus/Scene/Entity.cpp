#include "ltpch.h"
#include "Entity.h"

namespace Lotus {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}