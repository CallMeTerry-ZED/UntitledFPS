/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */


#include "Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FPS
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}