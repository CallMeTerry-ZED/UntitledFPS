/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #include "Renderer/Renderer.h"

namespace Sandbox
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene()
	{

	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
		
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
 		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}