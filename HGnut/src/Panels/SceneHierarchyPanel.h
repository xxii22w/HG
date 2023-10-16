#pragma once

#include "hg/Core/Base.h"
#include "hg/Scene/Scene.h"
#include "hg/Scene/Entity.h"
#include "hg/Core/Log.h"

namespace hg {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}