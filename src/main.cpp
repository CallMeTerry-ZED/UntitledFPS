/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Core/Engine.h"


class ExampleLayer : public FPS::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        //LOG_TRACE("ExampleLayer::Update");

        if (FPS::Input::IsKeyPressed(FPS_KEY_TAB))
		LOG_TRACE("Tab key is pressed (poll)!");
    }

    void OnEvent(FPS::Event& event) override
    {
        //LOG_TRACE("{}", event.ToString());

        if (event.GetEventType() == FPS::EventType::KeyPressed)
		{
			FPS::KeyPressedEvent& e = (FPS::KeyPressedEvent&)event;
			if (e.GetKeyCode() == FPS_KEY_TAB)
            {
                LOG_TRACE("Tab key is pressed (event)!");
            }
			LOG_TRACE("{} - Key code: {}", event.ToString(), e.GetKeyCode());
		}
    }
};

class TestApp : public FPS::Application
{
public:
    TestApp()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new FPS::ImGuiLayer());
    }

    ~TestApp()
    {

    }
};

FPS::Application* FPS::CreateApplication()
{
    return new TestApp();
}
