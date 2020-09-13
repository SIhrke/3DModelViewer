#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace gl 
{
	enum class AccessFrequency 
	{
		STREAM, //modified once, used seldomly
		STATIC, //modified once, used often
		DYNAMIC //modified often, used often
	};

	enum class AccessType 
	{
		DRAW,
		READ,
		COPY
	};

	using VecType = glm::vec3;
	using BufferData = std::vector<VecType>;
	class Buffer 
	{
	public:
		Buffer(BufferData&& data, AccessFrequency frequency, AccessType type);
		void Activate();
	private:
		unsigned buffer;
		BufferData data;
	};

}