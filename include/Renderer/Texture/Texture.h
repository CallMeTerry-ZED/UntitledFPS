/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "Core/Core.h"

namespace Sandbox
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}

#endif