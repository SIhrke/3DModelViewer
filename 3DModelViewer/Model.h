#pragma once
#include <optional>
#include <filesystem>

namespace viewer 
{
	class Model
	{
	public:
		Model(std::vector<float> verticesFlat,
			std::vector<float> normalsFlat,
			std::vector<unsigned int> indices,
			std::vector<unsigned int> solids)
		{

		}
	private:

	};

	std::optional<Model> LoadSTLModel(const std::filesystem::path& modelPath);
}
