#include "Initializer.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <glad/glad.h>
#include <filesystem>
#include <stl_reader.h>


int main()
{
	try 
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;

		


		std::vector<float> vertices_flat;
		std::vector<float> normals_flat;
		std::vector<unsigned int> indices;
		std::vector<unsigned int> solids;

		std::cout << "Reading STL..." << std::endl;
		
		if (stl_reader::ReadStlFile("./Assets/Dragon/stanford_dragon.stl", vertices_flat, normals_flat, indices, solids)) 
		{
			std::cout << "Done!" << std::endl;
		}
		else 
		{
			std::cout << "Couldnt read file!" << std::endl;
			return -1;
		}

		for (int i = 0; i < vertices_flat.size(); i += 3)
		{
			vertices.push_back(glm::vec3(vertices_flat[i], vertices_flat[i + 1], vertices_flat[i + 2]));
			normals.push_back(glm::vec3(normals_flat[i], normals_flat[i + 1], normals_flat[i + 2]));
		}
		

		gl::Initializer::Initialize();
		unsigned width = 640;
		unsigned height = 480;
		gl::Window window("window", width, height);
		window.Activate();
		gl::Buffer buffer(vertices,gl::AccessFrequency::STATIC,gl::AccessType::DRAW);
		gl::Buffer normalBuffer(normals, gl::AccessFrequency::STATIC, gl::AccessType::DRAW);

		gl::Buffer indexBuffer(indices, gl::AccessFrequency::STATIC, gl::AccessType::DRAW,gl::BufferType::INDEX);


		gl::ShaderProgram shader(std::filesystem::path("vertexShader.vert"), std::filesystem::path("fragmentShader.frag"));
		//shader.UseBufferForVertexAttribute(normalBuffer, "normalValue");

		shader.UseBufferForVertexAttribute(buffer, "vertex");
		auto eyePosition = glm::vec3(40.0f, 3.0f, 40.0f);
		auto lookatMat=glm::lookAt(eyePosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		auto perspectiveMat=glm::perspectiveFov(45.0f, static_cast<float>(width), static_cast<float>(height), 0.1f, 100.0f);
		
		glViewport(0, 0, width, height);
		float rotation = 0.0;
		window.Run([&]()
			{
				auto transformation = glm::rotate(rotation,0.0f,0.0f,1.0f);
				auto mvp = perspectiveMat * lookatMat * transformation;
				shader.UseForUniform(mvp, "MVP");
				glClear(GL_COLOR_BUFFER_BIT);
				shader.Activate();
				indexBuffer.Activate();
				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,(void*)0);

				rotation += 1.0;
			});
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
