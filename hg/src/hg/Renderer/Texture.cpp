#include "hgpch.h"
#include "hg/Renderer/Texture.h"

#include "hg/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace hg {

	hg::Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}