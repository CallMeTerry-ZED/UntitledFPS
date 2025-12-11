/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

namespace Sandbox
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& filepath);
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}

#endif