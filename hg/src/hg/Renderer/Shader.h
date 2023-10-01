#pragma once
#include <string>

namespace hg {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& faagmentSrc);
		~Shader();

		void bind();
		void unbind();
	private:
		uint32_t m_RendererID;
	};
}