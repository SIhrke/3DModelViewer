#include "Initializer.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <glad/glad.h>
#include <filesystem>

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
		gl::ShaderProgram shader(std::filesystem::path("vertexShader.vert"), std::filesystem::path("fragmentShader.frag"));
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
