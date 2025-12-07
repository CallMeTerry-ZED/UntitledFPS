/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef OPENGL_RENDERER_API
#define OPENGL_RENDERER_API

#include "Renderer/RendererAPI.h"

namespace FPS
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}

#endif