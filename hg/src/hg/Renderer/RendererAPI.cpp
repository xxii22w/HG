#include "hgpch.h"
#include "RendererAPI.h"

namespace hg {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	void RendererAPI::SetClearColor(const glm::vec4& color)
	{
	}
	void RendererAPI::Clear()
	{
	}
	void RendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}
}