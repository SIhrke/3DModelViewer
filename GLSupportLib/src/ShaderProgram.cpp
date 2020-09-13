#include "ShaderProgram.h"
#include <glad/glad.h>

namespace gl 
{
	ShaderProgram::ShaderProgram(const std::string& vertexShaderText, const std::string& fragmentShaderText)
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		
		const char* vertexShaderTextBuffer= vertexShaderText.c_str();
		glShaderSource(vertexShader, 1, const_cast<const GLchar* const *>(&(vertexShaderTextBuffer)), NULL);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not set shader source for vertex shader");
		}
		glCompileShader(vertexShader);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not compile vertex shader");
		}
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not create fragment Shader");
		}
		const char* fragmentShaderTextBuffer = fragmentShaderText.c_str();
		glShaderSource(fragmentShader, 1, const_cast<const GLchar* const*>(&(fragmentShaderTextBuffer)), NULL);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not set shader source for fragment shader");
		}

		glCompileShader(fragmentShader);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not compile fragment shader");
		}
		shaderProgram = glCreateProgram();
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not create program");
		}
		glAttachShader(shaderProgram, vertexShader);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not attach vertex shader");
		}
		glAttachShader(shaderProgram, fragmentShader);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not attach fragment shader");
		}
		glLinkProgram(shaderProgram);
		if (glGetError() != GL_NO_ERROR)
		{
			throw std::exception("could not attach fragment shader");
		}
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