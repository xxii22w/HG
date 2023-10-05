#include "hgpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace hg {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:		HG_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case  RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(vertices, size);

		}
		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}