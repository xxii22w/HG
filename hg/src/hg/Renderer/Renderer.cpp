#include "hgpch.h"
#include "Renderer.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "hg/Renderer/Renderer2D.h"

namespace hg {

	Renderer::ScaneData* Renderer::m_ScaneData = new ScaneData;

	void Renderer::Init()
	{
		HG_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::BeginScane(OrthographicCamera& camera)
	{
		m_ScaneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScane()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader ,const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_ScaneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}