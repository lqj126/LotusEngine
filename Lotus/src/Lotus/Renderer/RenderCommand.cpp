#include "ltpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lotus {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}