/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "RenderCommand.h"

namespace FPS
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}

#endif