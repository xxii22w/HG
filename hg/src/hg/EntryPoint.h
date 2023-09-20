#pragma once

#ifdef HG_PLATFORM_WINDOWS

extern hg::Application* hg::CreateApplication(); //CreateApplication在客户端实现的东西

int main(int argc, char** argv)
{
	hg::Log::Init();
	HG_CORE_WARN("Initialized Log!");
	int a = 5;
	HG_INFO("hello! Var={0}",a);


	auto app = hg::CreateApplication();
	app->run();
	delete app;
}


#endif // HG_PLATFORM_WINDOWS
