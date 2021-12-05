#pragma once
#include <string>
#include <functional>
struct GLFWwindow;

namespace gl 
{
	struct Size 
	{
		int width; 
		int height;
	};

	enum MouseMode 
	{
		Pressed,
		Released

	}; 

	class Window 
	{
	public:
		Window(const std::string& title, unsigned width, unsigned height);
		Window(const Window& rhs) = delete;
		Window(Window&& rhs) = delete;
		Window& operator=(const Window& rhs) = delete;
		Window& operator=(Window&& rhs) = delete;
		~Window();
		void Activate();
		void Run(const std::function<void()>& renderFunction);
		void RegisterMouseMove(const std::function<void(int, int, MouseMode)>& mouseMoveFunction);
		Size GetSize() const;
	private:
		static bool glLoaded;
		GLFWwindow* window=nullptr;
	};
}