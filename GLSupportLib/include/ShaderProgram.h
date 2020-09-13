#pragma once
#include <string>
#include "Buffer.h"

namespace gl
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		void UseBufferForVertexAttribute(const Buffer& buffer, const std::string& variableName);
		void UseForUniform(const glm::mat4x4& mat, const std::string& variableName);
		void Activate();
	private:
		unsigned shaderProgram,vertexShader,fragmentShader;
	};

}