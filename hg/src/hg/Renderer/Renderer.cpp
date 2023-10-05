#include "hgpch.h"
#include "Renderer.h"
#include <Platform/OpenGL/OpenGLShader.h>


namespace hg {

	Renderer::ScaneData* Renderer::m_ScaneData = new ScaneData;
	void Renderer::Init()
	{
		RenderCommand::Init();
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