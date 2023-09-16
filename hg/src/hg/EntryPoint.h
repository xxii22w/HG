#pragma once

#ifdef HG_PLATFORM_WINDOWS

extern hg::Application* hg::CreateApplication(); //CreateApplication在客户端实现的东西

int main(int argc, char** argv)
{
	printf("hg Engine\n");
	auto app = hg::CreateApplication();
	app->run();
	delete app;
}


#endif // HG_PLATFORM_WINDOWS
