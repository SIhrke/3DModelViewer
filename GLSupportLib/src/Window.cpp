#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gl 
{
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
		}

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