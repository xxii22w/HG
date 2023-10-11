#include "hgpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace hg {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}