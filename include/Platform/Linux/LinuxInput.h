/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef LINUX_INPUT_H
#define LINUX_INPUT_H

#include "Core/Input/Input.h"

namespace FPS
{
    class LinuxInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}

#endif