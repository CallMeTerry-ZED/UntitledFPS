/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "Core/Application/Application.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h"
#include "Core/Logger/Logger.h"
#include "Core/Time/Timestep.h"
#include "Core/Input/Input.h"
#include "Core/Input/KeyCodes.h"
#include "Core/Input/MouseButtonCodes.h"
#include "Events/KeyEvent.h"

// ---Renderer------------------------
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"

#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Buffer/VertexArray.h"

#include "Renderer/Camera/OrthographicCamera.h"
// -----------------------------------

// ---Entry Point---------------------
#include "Core/EntryPoint.h"
// -----------------------------------

// Thirdparty Includes
#include <imgui.h>

#endif
