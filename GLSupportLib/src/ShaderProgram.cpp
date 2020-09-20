#include "ShaderProgram.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace gl 
{

	ShaderProgram::ShaderProgram(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader)
	{
		std::ifstream vertexStream(vertexShader.string());
		std::ifstream fragmentStream(fragmentShader.string());

		std::string vertexText((std::istreambuf_iterator<char>(vertexStream)),std::istreambuf_iterator<char>());
		std::string fragmentText((std::istreambuf_iterator<char>(fragmentStream)), std::istreambuf_iterator<char>());
		SetupShaders(vertexText, fragmentText);

	}

	ShaderProgram::ShaderProgram(const std::string& vertexShaderText, const std::string& fragmentShaderText)
	{
		SetupShaders(vertexShaderText, fragmentShaderText);
	}

	void ShaderProgram::SetupShaders(const std::string& vertexShaderText, const std::string& fragmentShaderText)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* vertexShaderTextBuffer = vertexShaderText.c_str();
		glShaderSource(vertexShader, 1, const_cast<const GLchar* const*>(&(vertexShaderTextBuffer)), NULL);
		glCompileShader(vertexShader);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char* fragmentShaderTextBuffer = fragmentShaderText.c_str();
		glShaderSource(fragmentShader, 1, const_cast<const GLchar* const*>(&(fragmentShaderTextBuffer)), NULL);
		glCompileShader(fragmentShader);

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
	}

	ShaderProgram::~ShaderProgram() 
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}



	void ShaderProgram::UseForUniform(const glm::mat4x4& mat, const std::string& variableName)
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniformMatrix4fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void ShaderProgram::UseForUniform(const glm::mat3x3& mat, const std::string& variableName)
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniformMatrix3fv(varLocation, 1, GL_FALSE, glm::value_ptr(mat));
	}


	void ShaderProgram::UseForUniform(const glm::vec4& vec, const std::string& variableName)
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniform4fv(varLocation, 1, glm::value_ptr(vec));
	}

	void ShaderProgram::UseForUniform(const glm::vec3& vec, const std::string& variableName) 
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniform3fv(varLocation, 1, glm::value_ptr(vec));
	}
	void ShaderProgram::UseForUniform(const glm::vec2& vec, const std::string& variableName) 
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniform2fv(varLocation, 1, glm::value_ptr(vec));
	}
	void ShaderProgram::UseForUniform(int value, const std::string& variableName)
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniform1i(varLocation, value);
	}
	void ShaderProgram::UseForUniform(float value, const std::string& variableName)
	{
		Activate();
		auto varLocation = glGetUniformLocation(shaderProgram, variableName.c_str());
		glUniform1f(varLocation, value);
	}

	void ShaderProgram::Activate() 
	{
		glUseProgram(shaderProgram);
	}

}