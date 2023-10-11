#include "hgpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace hg {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(size);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* vertices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case  RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(vertices, count);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}