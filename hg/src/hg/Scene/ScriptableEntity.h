#pragma once

#include "Entity.h"

namespace hg {

	class ScriptableEntity
	{
	public:
		~ScriptableEntity() = default;

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnCreate(){}
		virtual void OnDestory() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}