#pragma once

#include "entt.hpp"
#include "hg/Core/Timestep.h"

namespace hg {

	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());


		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;		// 基本上所有组件和实体的容器  包括了  组件数据  以及  实体ID

		friend class Entity;
	};
}