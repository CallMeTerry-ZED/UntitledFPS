/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#include "Core/Core.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Core/Logger/Logger.h"
#include "glad.h"
#include <GLFW/glfw3.h>

namespace FPS
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		FPS_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FPS_CORE_ASSERT(status, "Failed to initialize Glad!"); 

		LOG_INFO("OpenGL Info:");
		LOG_INFO("Vendor: {}", 	GlString(glGetString(GL_VENDOR)));
		LOG_INFO("Renderer: {}", GlString(glGetString(GL_RENDERER)));
		LOG_INFO("Version: {}", 	GlString(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}