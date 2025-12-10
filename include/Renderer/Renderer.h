/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "RenderCommand.h"
#include "Camera/OrthographicCamera.h"
#include "Renderer/Shader/Shader.h"

namespace Sandbox
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}

#endif