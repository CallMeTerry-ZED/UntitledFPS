/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Core/Layer/Layer.h"

namespace FPS
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override; 
        void OnEvent(Event& event) override;
        void SetBlockEvents(bool block) { m_BlockEvents = block; }
        bool GetBlockEvents() const { return m_BlockEvents; }

        void Begin();
        void End(); 

    private:
        float m_Time = 0.0f;
        bool m_BlockEvents = true; 
    };
}

#endif