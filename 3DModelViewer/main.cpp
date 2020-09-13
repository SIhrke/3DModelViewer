#include "Initializer.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <glad/glad.h>

static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vertex;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP*vec4(vertex, 1.0);\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(1.0,0.0,0.0, 1.0);\n"
"}\n";


int main()
{
	try 
	{
		std::vector<glm::vec3> vertices{ 
			glm::vec3{1,1,-1}, 
			glm::vec3{-1,1,-1},
			glm::vec3{-1,-1,-1},
			glm::vec3{1,-1,-1}
		};
		gl::Initializer::Initialize();
		unsigned width = 640;
		unsigned height = 480;
		gl::Window window("window", width, height);
		window.Activate();
		gl::Buffer buffer(std::move(vertices),gl::AccessFrequency::STATIC,gl::AccessType::DRAW);
		gl::ShaderProgram shader(vertex_shader_text, fragment_shader_text);
		shader.UseBufferForVertexAttribute(buffer, "vertex");

		auto eyePosition = glm::vec3(0.0f, 0.0f, 1.0f);
		auto lookatMat=glm::lookAt(eyePosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		auto perspectiveMat=glm::perspectiveFov(45.0f, static_cast<float>(width), static_cast<float>(height), 0.1f, 100.0f);
		auto mvp = perspectiveMat * lookatMat;
		shader.UseForUniform(mvp,"MVP");
		glViewport(0, 0, width, height);
		
		window.Run([&]()
			{
				glClear(GL_COLOR_BUFFER_BIT);
				shader.Activate();
				glDrawArrays(GL_QUADS, 0, 4);
			});
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
