#include "Initializer.h"
#include "Window.h"
#include "ShaderProgram.h"

#include "glm/glm.hpp"

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


int main()
{
	gl::Initializer::Initialize();
	gl::Window window("window", 640, 480);
	window.Activate();
	gl::ShaderProgram shader(vertex_shader_text, fragment_shader_text);
	window.Run([](){});
	return 0;
}
