#pragma once
#include <string>
#include <filesystem>
#include "Buffer.h"
#include "TypeTraits.h"

namespace gl
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader);
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();

		template<typename VecType>
		void UseBufferForVertexAttribute(const Buffer<VecType>& buffer, const std::string& variableName)
		{
			Activate();
			buffer.Activate();
			auto varLocation = glGetAttribLocation(shaderProgram, variableName.c_str());
			;
			glEnableVertexAttribArray(varLocation);

			//TODO: reflection must be handled here
			glVertexAttribPointer(varLocation, OpenGLTraits<VecType>::size, OpenGLTraits<VecType>::glType, GL_FALSE,
				buffer.ElementSizeInBytes(), (void*)0);

		}		
		void UseForUniform(const glm::mat4x4& mat, const std::string& variableName);
		void UseForUniform(const glm::mat3x3& mat, const std::string& variableName);
		void UseForUniform(const glm::vec4& vec, const std::string& variableName);
		void UseForUniform(const glm::vec3& vec, const std::string& variableName);
		void UseForUniform(const glm::vec2& vec, const std::string& variableName);
		void UseForUniform(int value, const std::string& variableName);
		void UseForUniform(float value, const std::string& variableName);

		void Activate();
	private:
		void SetupShaders(const std::string& vertexShaderText, const std::string& fragmentShaderText);
		unsigned shaderProgram,vertexShader,fragmentShader;
	};

}