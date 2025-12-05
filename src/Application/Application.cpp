/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired By The Cherno
 * Referenced https://github.com/TheCherno/Hazel/blob/f9fbbd2bf3d870a6586c5c4f70a867d78e27b113/Hazel/src/Hazel/Application.cpp
 *
 */

#include "Application/Application.h"

namespace FPS
{
    Application::Application()
    {
        IsRunning = true;
    }

    Application::~Application()
    {
        IsRunning = false;
    }

    void Application::Run()
    {
        while (IsRunning)
        {
        }
    }
}
