#include "Initializer.h"
#include "Window.h"

int main()
{
	gl::Initializer::Initialize();
	gl::Window window("window", 640, 480);
	window.Run([]() {});
	return 0;
}
