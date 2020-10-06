#include "Model.h"
#include <iostream>
#include <stl_reader.h>

std::optional<viewer::Model> viewer::LoadSTLModel(const std::filesystem::path& modelPath)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;

	std::vector<float> vertices_flat;
	std::vector<float> normals_flat;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> solids;

	std::cout << "Reading STL..." << std::endl;

	if (stl_reader::ReadStlFile(modelPath.string().c_str(), vertices_flat, normals_flat, indices, solids))
	{
		std::cout << "Done!" << std::endl;
	}
	else
	{
		std::cout << "Couldnt read file!" << std::endl;
		return {};
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
	for (int i = 0, j = 0; i < indices.size(); i += 3, j++)
	{
		averagedNormals[indices[i]] += normals[j];
		averagedNormals[indices[i + 1]] += normals[j];
		averagedNormals[indices[i + 2]] += normals[j];
	}
	for (auto& normal : averagedNormals)
	{
		normal = glm::normalize(normal);
	}


	return Model{ vertices,averagedNormals, indices };
}