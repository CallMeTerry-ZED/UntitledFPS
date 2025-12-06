/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired By The Cherno
 * Referenced https://github.com/TheCherno/Hazel/blob/f9fbbd2bf3d870a6586c5c4f70a867d78e27b113/Hazel/src/Hazel/Application.cpp
 *
 */

#include "Core/Application/Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/Logger/Logger.h"

#include <glad.h>

namespace FPS
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        if (s_Instance)
        {
            LOG_ERROR("Application already exists!");
            return;
        }
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetQueueEventCallback([this](std::unique_ptr<Event> e) {
            this->QueueEvent(std::move(e));
        });

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

        IsRunning = true;
    }

    Application::~Application()
    {
        IsRunning = false;
    }

    void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

    void Application::OnEvent(Event& event)
    {
        // Dispatch to layers (overlays first, then regular layers)
        // Overlays are at the end, so iterates in reverse
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(event);
            if (event.IsHandled())
            {
                break;
            }
        }

        // EventDispatcher for type-safe event handling
        EventDispatcher dispatcher(event);

        // Handle WindowCloseEvent
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {
            LOG_INFO("Window close event");
            IsRunning = false;
            return true;
        });

        // Handle WindowResizeEvent
        dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e) {
            LOG_INFO("Window resized: {}x{}", e.GetWidth(), e.GetHeight());
            return false;
        });

        // Handle KeyPressedEvent
        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) {
            LOG_DEBUG("Key pressed: {}", e.GetKeyCode());
            return false;
        });
    }

    void Application::QueueEvent(std::unique_ptr<Event> event)
    {
        m_EventQueue.push_back(std::move(event));
    }

    void Application::ProcessEvents()
    {
        // Process all queued events
        for (auto& event : m_EventQueue)
        {
            OnEvent(*event);
        }
        m_EventQueue.clear();
    }

    void Application::Run()
    {
        while (IsRunning)
        {
            // Process deferred events always first
            ProcessEvents();

            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            // Update all layers
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }
}
