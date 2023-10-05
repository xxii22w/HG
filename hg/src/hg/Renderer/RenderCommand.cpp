#include "hgpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace hg {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}