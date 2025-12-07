/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired By The Cherno
 * Referenced https://github.com/TheCherno/Hazel/blob/f9fbbd2bf3d870a6586c5c4f70a867d78e27b113/Hazel/src/Hazel/Application.h
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Events/Event.h"
#include "Core/Window/Window.h"
#include "Core/Layer/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h" 
#include "Renderer/Shader/Shader.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Buffer/VertexArray.h"

#include <vector>
#include <memory>

namespace FPS
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        // Event handling
        void OnEvent(Event& event);

        // Deferred event system
        void QueueEvent(std::unique_ptr<Event> event);

        // Layer management
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

    private:
        void ProcessEvents();

        bool IsRunning;

        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;

        std::vector<std::unique_ptr<Event>> m_EventQueue;
        
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
    };

    // Client Defined
    Application* CreateApplication();
}

#endif
