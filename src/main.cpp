/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Core/Engine.h"

class ExampleLayer : public Sandbox::Layer
{
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
    {
		m_VertexArray.reset(Sandbox::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Sandbox::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Sandbox::VertexBuffer::Create(vertices, sizeof(vertices)));
		Sandbox::BufferLayout layout = {
			{ Sandbox::ShaderDataType::Float3, "a_Position" },
			{ Sandbox::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Sandbox::IndexBuffer> indexBuffer;
		indexBuffer.reset(Sandbox::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Sandbox::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<Sandbox::VertexBuffer> squareVB;
		squareVB.reset(Sandbox::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Sandbox::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Sandbox::IndexBuffer> squareIB;
		squareIB.reset(Sandbox::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Sandbox::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Sandbox::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

    void OnUpdate(Sandbox::Timestep ts) override
    {
        //LOG_TRACE("ExampleLayer::Update");

		if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Sandbox::Input::IsKeyPressed(SANDBOX_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Sandbox::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Sandbox::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Sandbox::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Sandbox::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}
		}
		Sandbox::Renderer::Submit(m_Shader, m_VertexArray);

		Sandbox::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
	{
        ImGui::Begin("Sandbox ENGINE");
        ImGui::Text("WELCOME TO Sandbox ENGINE!");
        ImGui::End();
	}

    void OnEvent(Sandbox::Event& event) override
    {
        //LOG_TRACE("{}", event.ToString());
    }

private:
	std::shared_ptr<Sandbox::Shader> m_Shader;
	std::shared_ptr<Sandbox::VertexArray> m_VertexArray;

	std::shared_ptr<Sandbox::Shader> m_BlueShader;
	std::shared_ptr<Sandbox::VertexArray> m_SquareVA;

	Sandbox::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class TestApp : public Sandbox::Application
{
public:
    TestApp()
    {
        PushLayer(new ExampleLayer());
    }

    ~TestApp()
    {

    }
};

Sandbox::Application* Sandbox::CreateApplication()
{
    return new TestApp();
}
