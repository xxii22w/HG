#pragma once

#include "Shader.h"
#include "RenderCommand.h"
#include "hg/Renderer/OrthographicCamera.h"

namespace hg {

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScane(OrthographicCamera& camera);
		static void EndScane();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct ScaneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static ScaneData* m_ScaneData;
	};
}