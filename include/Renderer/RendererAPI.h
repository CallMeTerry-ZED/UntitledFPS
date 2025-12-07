/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef RENDERER_API_H
#define RENDERER_API_H

#include <glm/glm.hpp>

#include "Renderer/Buffer/VertexArray.h"

namespace FPS
{

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
            OpenGL = 1
		};

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
        
	private:
		static API s_API;
	};

}

#endif