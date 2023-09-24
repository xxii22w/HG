#pragma once

#include "hg/Layer.h"
#include "hg/Events/KeyEvent.h"
#include "hg/Events/MouseEvent.h"
#include "hg/Events/ApplicationEvent.h"

namespace hg {

	class HG_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};
}