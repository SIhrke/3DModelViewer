#include "ShaderProgram.h"
#include <glad/glad.h>

namespace gl 
{
	ShaderProgram::ShaderProgram(const std::string& vertexShaderText, const std::string& fragmentShaderText)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		const char* vertexShaderTextBuffer= vertexShaderText.c_str();
		glShaderSource(vertexShader, 1, const_cast<const GLchar* const *>(&(vertexShaderTextBuffer)), NULL);
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


	void ShaderProgram::Activate() 
	{
		glUseProgram(shaderProgram);
	}

}