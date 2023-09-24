#include <hg.h>

#include "imgui/imgui.h"

class ExampleLayer :public hg::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}

	void OnUpdate()override
	{

		if (hg::Input::IsKeyPressed(HG_KEY_TAB))
			HG_TRACE("Tab key is Pressed (poll) !");
	}

	/*virtual void OnImGuiRender() override
	{
		ImGui::Begin("Text");
		ImGui::Text("Hello world");
		ImGui::End();
	}*/

	void OnEvent(hg::Event& event)override
	{
		if (event.GetEventType() == hg::EventType::KeyPressed) {
			hg::KeyPressEvent& e = (hg::KeyPressEvent&)event;
			if(e.GetKeyCode() == HG_KEY_TAB)
				HG_TRACE("Tab key is Pressed (event) !");
			HG_TRACE("{0}", (char)e.GetKeyCode());
		}
		
	} 
};

class Sandbox :public hg::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}
	~Sandbox()
	{

	}
};

hg::Application* hg::CreateApplication()
{
	return new Sandbox();
}