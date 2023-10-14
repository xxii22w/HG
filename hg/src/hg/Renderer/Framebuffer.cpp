#include "hgpch.h"
#include "hg/Renderer/Framebuffer.h"
#include "hg/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace hg {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
