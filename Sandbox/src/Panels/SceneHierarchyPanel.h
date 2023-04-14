#pragma once

#include "Lotus/Core/Core.h"
#include "Lotus/Core/Log.h"
#include "Lotus/Scene/Scene.h"
#include "Lotus/Scene/Entity.h"

namespace Lotus {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}