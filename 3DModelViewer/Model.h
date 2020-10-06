#pragma once
#include <optional>
#include <filesystem>
#include <glm/glm.hpp>

namespace viewer 
{
	struct Model
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<unsigned int> indices;
	};

	std::optional<Model> LoadSTLModel(const std::filesystem::path& modelPath);
}
