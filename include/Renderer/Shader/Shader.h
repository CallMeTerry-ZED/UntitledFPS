/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

namespace FPS
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};

}

#endif