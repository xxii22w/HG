#include "hgpch.h"
#include "SceneHierarchyPanel.h"
#include <imgui/imgui.h>
#include "hg/Scene/Components.h"

namespace hg {

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

		m_Context->m_Registry.each([&](auto entityID)
			{
				Entity entity{ entityID,m_Context.get() };
				DrawEntityNode(entity);

			});

		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;
		
		// 像树结构 设置为 选择 展开
		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected  : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}
		// 树节点的小三角形展开
		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;

			bool opened = ImGui::TreeNodeEx((void*)7868982, flags, tag.c_str());

			if (opened)
				ImGui::TreePop();

			ImGui::TreePop();	// 展开树节点
		}
	}

}


