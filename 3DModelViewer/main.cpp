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
		}
		for (int i = 0; i < normals_flat.size(); i += 3)
		{
			normals.push_back(glm::vec3(normals_flat[i], normals_flat[i + 1], normals_flat[i + 2]));
		}

		std::vector<glm::vec3> averagedNormals(vertices.size());
		for (int i = 0,j=0; i < indices.size(); i += 3,j++)
		{
			averagedNormals[indices[i]] += normals[j];
			averagedNormals[indices[i+1]] += normals[j];
			averagedNormals[indices[i+2]] += normals[j];
		}
		for (auto& normal : averagedNormals)
		{
			normal = glm::normalize(normal);
		}
		
		glm::vec3 center;
		float maxX = 0;
		float maxY = 0;
		float maxZ = 0;
		for (auto& vertex : vertices)
		{
			if (vertex.x > maxX)
				maxX = vertex.x;
			if (vertex.y > maxY)
				maxY = vertex.y;
			if (vertex.z > maxZ)
				maxZ = vertex.z;
			center += vertex;
		}
		center /= vertices.size();

		gl::Initializer::Initialize();
		
		gl::Window window("window", 640, 480);
		window.Activate();
		gl::Buffer buffer(vertices,gl::AccessFrequency::STATIC,gl::AccessType::DRAW);
		gl::Buffer normalBuffer(averagedNormals, gl::AccessFrequency::STATIC, gl::AccessType::DRAW);

		gl::Buffer indexBuffer(indices, gl::AccessFrequency::STATIC, gl::AccessType::DRAW,gl::BufferType::INDEX);


		gl::ShaderProgram shader(std::filesystem::path("vertexShader.vert"), std::filesystem::path("fragmentShader.frag"));
		shader.UseBufferForVertexAttribute(normalBuffer, "normal");

		shader.UseBufferForVertexAttribute(buffer, "vertex");
		
		
		float rotation = 0.0;
		float rotationLight = 0.0;
		glEnable(GL_DEPTH_TEST);  
		window.Run([&]()
			{
				glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

				auto windowSize = window.GetSize();
				glViewport(0, 0, windowSize.width, windowSize.height);

				auto eyePosition = glm::vec3(maxX * 2, maxY * 2, maxZ * 2);
				auto lookatMat = glm::lookAt(eyePosition, center, glm::vec3(0.0f, 0.0f, 1.0f));
				auto perspectiveMat = glm::perspectiveFov(45.0f, static_cast<float>(windowSize.width), static_cast<float>(windowSize.height), 0.1f, 100.0f);


				auto transformation = glm::rotate(rotation,0.0f,0.0f,1.0f);
				auto mvp = perspectiveMat * lookatMat * transformation;
				auto mvpNormal = glm::transpose(glm::inverse(mvp));

				glm::vec4 lightDirection(1, 1, 1, 1);
				lightDirection = glm::rotate(rotationLight, 0.0f, 0.0f, 1.0f) * lightDirection;
				shader.UseForUniform(mvp, "MVP");
				shader.UseForUniform(mvpNormal, "mvpNormal");
				shader.UseForUniform(lightDirection,"lightDirection");

				shader.Activate();
				indexBuffer.Activate();
				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,(void*)0);

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
