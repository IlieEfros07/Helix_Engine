#include "hxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Helix {


	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}