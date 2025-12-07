/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #include "Renderer/Renderer.h"

namespace FPS
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{
		
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}