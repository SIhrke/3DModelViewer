#include "Initializer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>

namespace gl 
{
	void Initializer::Initialize()
	{
		static Initializer init;
	}
	Initializer::Initializer()
	{
		if (!glfwInit())
		{
			throw std::exception("Could not initialize Window System.");
		}
	}
	Initializer::~Initializer()
	{
		glfwTerminate();
	}
}

