#include "hgpch.h"
#include "hg/Renderer/Shader.h"

#include "hg/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace hg {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: HG_CORE_ASSERT(false, "RendererAPI::None is currently not support!");
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(filepath);
		}

		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: HG_CORE_ASSERT(false, "RendererAPI::None is currently not support!");
			case RendererAPI::API::OpenGL: return std::make_shared<OpenGLShader>(name,vertexSrc, fragmentSrc);
		}

		HG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HG_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name,shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string name)
	{
		HG_CORE_ASSERT(Exists(name), "Shader not found!");
		return m_Shaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}