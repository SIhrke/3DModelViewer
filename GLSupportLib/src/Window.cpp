#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>

namespace gl 
{

	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		std::stringstream ss;
		ss<< "OpenGL Error type: " << type << " severity: " << severity << " message: " << message << std::endl;
		throw std::exception(ss.str().c_str());
	}

	bool Window::glLoaded = false;
	Window::Window(const std::string& title, unsigned width, unsigned height):
		window(glfwCreateWindow(width,height,title.c_str(),nullptr,nullptr))
	{
	
	}

	Window::~Window()
	{
		if (window)
			glfwDestroyWindow(window);
	}

	void Window::Activate()
	{
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		if (!glLoaded)
		{
			if (!gladLoadGL()) 
			{
				throw std::exception("Could not initialize OpenGL. Maybe no Context is Current.");
			}
			//enable debug output for opengl
			glEnable(GL_DEBUG_OUTPUT);
			glDebugMessageCallback(MessageCallback, 0);

		}

	}
	Size Window::GetSize() const
	{
		Size size;
		glfwGetFramebufferSize(window, &size.width, &size.height);
		return size;
	}

	void Window::Run(const std::function<void()>& renderFunction)
	{
		Activate();
		while (!glfwWindowShouldClose(window)) 
		{
			renderFunction();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

}