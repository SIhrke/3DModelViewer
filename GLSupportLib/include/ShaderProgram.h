#pragma once
#include <string>
#include <filesystem>
#include "Buffer.h"

namespace gl
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader);
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		void UseBufferForVertexAttribute(const Buffer& buffer, const std::string& variableName);
		void UseForUniform(const glm::mat4x4& mat, const std::string& variableName);
		void Activate();
	private:
		void SetupShaders(const std::string& vertexShaderText, const std::string& fragmentShaderText);
		unsigned shaderProgram,vertexShader,fragmentShader;
	};

}