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
	class Window 
	{
	public:
		Window(const std::string& title, unsigned width, unsigned height);
		~Window();
		void Activate();
		void Run(const std::function<void()>& renderFunction);
		Size GetSize() const;
	private:
		static bool glLoaded;
		GLFWwindow* window=nullptr;
	};
}