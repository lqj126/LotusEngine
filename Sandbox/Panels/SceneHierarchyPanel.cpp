#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "Lotus/Scene/Components.h"
#include <glm/glm/gtc/type_ptr.hpp>

namespace Lotus {

	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");
		if (ImGui::BeginPopupContextItem("Select"))
		{
			if (ImGui::MenuItem("Add Entity"))
			{
				m_Context->CreateEntity();
			}
			ImGui::EndPopup();
		}
		m_Context->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID , m_Context.get() };
				DrawEntityNode(entity);
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		ImGui::End();

		ImGui::Begin("Properties");
		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}
		/*Assertion failed: SizeOfIDStack == window->IDStack.Size && "PushID/PopID or TreeNode/TreePop Mismatch!",
		if (opened && ImGui::BeginPopupContextItem("Select"))
		{
			if (ImGui::MenuItem("Delete Entity"))
			{
				//m_Context->RemoveEntity(entity);
				m_Context->m_Registry.destroy(entity.GetEntityHandle());
			}
			ImGui::EndPopup();
		}
		*/
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}
		else if (!opened && ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Right-click to Add");
		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{

		if (ImGui::BeginPopupContextItem("Select"))
		{
			if (ImGui::MenuItem("Add ModelComponent"))
			{
				if (!entity.HasComponent<ModelComponent>())
				{
					entity.AddComponent<ModelComponent>(CreateRef<Model>("C:/Code/Lotus/Sandbox/assets/models/blueball/wooden_sphere.obj"));
				}
			}
			ImGui::EndPopup();
		}

		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			//typeid can return object of std::type_info 
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				ImGui::DragFloat3("Position", glm::value_ptr(entity.GetComponent<TransformComponent>().Position), 0.1f);
				ImGui::DragFloat3("Rotation", glm::value_ptr(entity.GetComponent<TransformComponent>().Rotation), 0.1f);
				ImGui::DragFloat3("Scale", glm::value_ptr(entity.GetComponent<TransformComponent>().Scale), 0.1f);
				ImGui::DragFloat("Angle", &(entity.GetComponent<TransformComponent>().Angle), 0.1f);
				ImGui::TreePop();
			}
		}
		if (entity.HasComponent<ModelComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(ModelComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "ModelComponent"))
			{
				static char path[255]{};
				ImGui::Text("Input Path");
				ImGui::InputText("path", path, IM_ARRAYSIZE(path));
				if (ImGui::Button("Submit"))
				{
					auto& CMP = entity.GetComponent<ModelComponent>().Model;
					CMP = CreateRef<Model>(std::string(path));
				}
				ImGui::TreePop();
			}
		}
	}

}