/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Application/Application.h"
#include "Logger/Logger.h"

class TestApp : public FPS::Application
{
public:
    TestApp()
    {

    }

    ~TestApp()
    {

    }
};

FPS::Application* FPS::CreateApplication()
{
    return new TestApp();
}

int main(int argc, char** argv)
{
    FPS::Logger logger;

    auto app = FPS::CreateApplication();
    app->Run();
    delete app;

    return 0;
}
