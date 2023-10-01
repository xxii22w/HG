#include "hgpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace hg {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HG_CORE_ASSERT(windowHandle, "window handle is null!");

	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HG_CORE_ASSERT(status, "Failed to initialize Glad!");

		// 展现当前我们使用的是什么GPU
		HG_CORE_INFO("OpenGL Info : ");
		printf("	Vendor : %s\n", glGetString(GL_VENDOR));
		printf("	Renderer : %s\n", glGetString(GL_RENDERER));
		printf("	Version : %s\n", glGetString(GL_VERSION));


	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	} 
}