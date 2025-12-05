/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 * Inspired by TheCherno's Hazel Engine
 * Referenced: https://github.com/TheCherno/Hazel/commit/5bd809312a266c23d13d84dcd08a833a526aa264
 */

#include "Core/Layer/Layer.h"

namespace FPS
{
    Layer::Layer(const std::string& name)
    : m_DebugName(name)
    {
    }

    Layer::~Layer()
    {
    }
}
