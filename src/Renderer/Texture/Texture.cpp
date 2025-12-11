/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Renderer/Texture/Texture.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Sandbox
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    SANDBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		SANDBOX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}