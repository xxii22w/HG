#pragma once

#include "hg/Core/Layer.h"
#include "hg/Events/KeyEvent.h"
#include "hg/Events/MouseEvent.h"
#include "hg/Events/ApplicationEvent.h"

namespace hg {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemColors();

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;

	};
}