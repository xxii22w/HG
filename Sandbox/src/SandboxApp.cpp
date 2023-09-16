#include <hg.h>

class Sandbox :public hg::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

hg::Application* hg::CreateApplication()
{
	return new Sandbox();
}