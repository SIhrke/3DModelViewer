#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

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

	enum class BufferType
	{
		DATA=GL_ARRAY_BUFFER,
		INDEX=GL_ELEMENT_ARRAY_BUFFER
	};

	unsigned GenerateGLEnumStatic(AccessType type);
	unsigned GenerateGLEnumDynamic(AccessType type);
	unsigned GenerateGLEnumStream(AccessType type);
	unsigned GenerateGLEnum(AccessFrequency frequency, AccessType type);

	template <typename VecType>
	class Buffer 
	{
		using BufferData = std::vector<VecType>;

	public:

		Buffer(const BufferData& data, AccessFrequency frequency, AccessType type, BufferType bufferType = BufferType::DATA) :
			bufferType(bufferType)
		{
	
			glGenBuffers(1, &buffer);
			glBindBuffer(bufferType, buffer);
			glBufferData(bufferType, sizeof(VecType) * data.size(), data.data(), GenerateGLEnum(frequency, type));
		}

		Buffer(const Buffer& rhs) = delete;
		Buffer(Buffer&& rhs) = delete;
		Buffer& operator=(const Buffer& rhs) = delete;
		Buffer& operator=(Buffer&& rhs) = delete;

		~Buffer()
		{
			glDeleteBuffers(1, &buffer);
		}


		unsigned ElementSizeInBytes() const
		{
			return sizeof(VecType);
		}

		void Activate() const
		{
			glBindBuffer(bufferType, buffer);
		}
	private:
		unsigned buffer;
		BufferType bufferType=GL_ARRAY_BUFFER;
	};

}