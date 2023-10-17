#include "hgpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace hg {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case  RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}