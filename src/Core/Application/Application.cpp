/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired By The Cherno
 * Referenced https://github.com/TheCherno/Hazel/blob/f9fbbd2bf3d870a6586c5c4f70a867d78e27b113/Hazel/src/Hazel/Application.cpp
 *
 */

#include "Core/Application/Application.h"
#include "Core/Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Core/Logger/Logger.h"

#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"

namespace Sandbox
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

            float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

            // Update all layers
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
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
