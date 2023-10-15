#pragma once

#include "hg/Core/Base.h"

#include "hg/Events/Event.h"
#include "hg/Core/Timestep.h"

namespace hg {

	class  Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& e){}

		inline const std::string& GetName()const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}