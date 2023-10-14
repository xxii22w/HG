#pragma once


#ifdef HG_PLATFORM_WINDOWS

extern hg::Application* hg::CreateApplication(); //CreateApplication在客户端实现的东西

int main(int argc, char** argv)
{
	hg::Log::Init();

	HG_PROFILE_BEGIN_SESSION("Startup", "Hgprofile-Startup.json");
	auto app = hg::CreateApplication();
	HG_PROFILE_END_SESSION();

	HG_PROFILE_BEGIN_SESSION("Runtime", "Hgprofile-runtime.json");
	app->run();
	HG_PROFILE_END_SESSION();

	HG_PROFILE_BEGIN_SESSION("Shutdown", "Hgprofile-Shutdown.json");
	delete app;
	HG_PROFILE_END_SESSION();

}


#endif // HG_PLATFORM_WINDOWS
