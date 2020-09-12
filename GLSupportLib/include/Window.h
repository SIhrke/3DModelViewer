#pragma once

namespace gl 
{
	class Window 
	{
	public:
		Window(unsigned width, unsigned height);
		~Window();
		void Activate();
	private:
		static bool glLoaded;
	};
}