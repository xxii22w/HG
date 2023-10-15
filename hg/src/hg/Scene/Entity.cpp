#include "hgpch.h"
#include "Entity.h"

namespace hg {

	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle),m_Scene(scene)
	{
	}
}