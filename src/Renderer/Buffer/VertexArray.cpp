/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Renderer/Buffer/VertexArray.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace FPS
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:    FPS_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		FPS_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}