#include "Initializer.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <glad/glad.h>
#include <filesystem>
#include <stl_reader.h>
#include "Model.h"

namespace viewer 
{
	glm::vec3 ComputeCenter(const std::vector<glm::vec3>& vertices)
	{
		glm::vec3 center;
		for (const auto& vertex : vertices)
		{
			center += vertex;
		}
		center /= vertices.size();
		return center;
	}



	glm::vec3 ComputeMax(const std::vector<glm::vec3>& vertices)
	{
		glm::vec3 max{-std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity(),-std::numeric_limits<float>::infinity() };
		for (const auto& vertex : vertices)
		{
			max.x = std::max(vertex.x, max.x);
			max.y = std::max(vertex.y, max.y);
			max.z = std::max(vertex.z, max.z);
		}
		return max;
	}
}



int main()
{
	try 
	{
		auto modelPath = std::filesystem::path("./Assets/Teapot/utahteapot.stl");
		auto modelOptional = viewer::LoadSTLModel(modelPath);
		if (!modelOptional)
			return -1;
		auto& model = modelOptional.value();
		auto center = viewer::ComputeCenter(model.vertices);
		auto maxModelPoint = viewer::ComputeMax(model.vertices);
		gl::Initializer::Initialize();
		
		gl::Window window("window", 640, 480);
		window.Activate();
		gl::Buffer vertexBuffer(model.vertices, gl::AccessFrequency::STATIC, gl::AccessType::DRAW);
		gl::Buffer normalBuffer(model.normals, gl::AccessFrequency::STATIC, gl::AccessType::DRAW);
		gl::Buffer indexBuffer(model.indices, gl::AccessFrequency::STATIC, gl::AccessType::DRAW,gl::BufferType::INDEX);


		gl::ShaderProgram shader(std::filesystem::path("vertexShader.vert"), std::filesystem::path("fragmentShader.frag"));
		shader.UseBufferForVertexAttribute(normalBuffer, "normal");
		shader.UseBufferForVertexAttribute(vertexBuffer, "vertex");
		
		float rotationX = 0.0f;
		float rotationLight = 0.0;
		int windowX = 0;
		window.RegisterMouseMove(
			[&](int x, int y, gl::MouseMode mode)
			{
				if (mode == gl::MouseMode::Pressed)
				{
					int diffX = windowX - x;

					rotationX = static_cast<float>(diffX);
				}
			}
		);
		glEnable(GL_DEPTH_TEST);  
		window.Run([&]()
			{
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

				auto windowSize = window.GetSize();
				glViewport(0, 0, windowSize.width, windowSize.height);

				auto eyePosition = 2.0f*glm::length(maxModelPoint)*glm::vec3(1,0,0.5);
				auto lookatMat = glm::lookAt(eyePosition, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				auto perspectiveMat = glm::perspectiveFov(45.0f, static_cast<float>(windowSize.width), static_cast<float>(windowSize.height), 0.1f, 100.0f);


				auto transformation = glm::rotate(rotationX,0.0f,0.0f,1.0f) * glm::translate(-center);
				auto mvp = perspectiveMat * lookatMat * transformation;

				glm::vec4 lightDirection(1, 1, 1, 1);
				lightDirection = glm::rotate(rotationLight, 0.0f, 0.0f, 1.0f) * lightDirection;
				shader.UseForUniform(eyePosition, "eyePosition");
				shader.UseForUniform(mvp, "MVP");
				shader.UseForUniform(lightDirection,"lightDirection");

				shader.Activate();
				indexBuffer.Activate();
				glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT,(void*)0);

				//rotation += 1.0;
				rotationLight -= 2.0;
			});
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return 0;
}
