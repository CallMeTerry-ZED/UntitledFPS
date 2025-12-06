/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

namespace FPS
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}

#endif