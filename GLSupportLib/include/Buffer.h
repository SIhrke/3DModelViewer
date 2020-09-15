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

	enum BufferType
	{
		DATA=GL_ARRAY_BUFFER,
		INDEX=GL_ELEMENT_ARRAY_BUFFER
	};

	template <typename VecType>
	class Buffer 
	{
		using BufferData = std::vector<VecType>;

	public:
		unsigned GenerateGLEnumStatic(AccessType type)
		{
			unsigned glEnumValue = GL_STATIC_DRAW;
			switch (type)
			{
			case AccessType::READ:
				return GL_STATIC_READ;
			case AccessType::COPY:
				return GL_STATIC_COPY;
			case AccessType::DRAW:
				return GL_STATIC_DRAW;
			}
			return glEnumValue;
		}

		unsigned GenerateGLEnumDynamic(AccessType type)
		{
			unsigned glEnumValue = GL_DYNAMIC_DRAW;
			switch (type)
			{
			case AccessType::READ:
				return GL_DYNAMIC_READ;
			case AccessType::COPY:
				return GL_DYNAMIC_COPY;
			case AccessType::DRAW:
				return GL_DYNAMIC_DRAW;
			}
			return glEnumValue;
		}

		unsigned GenerateGLEnumStream(AccessType type)
		{
			unsigned glEnumValue = GL_STREAM_DRAW;
			switch (type)
			{
			case AccessType::READ:
				return GL_STREAM_READ;
			case AccessType::COPY:
				return GL_STREAM_COPY;
			case AccessType::DRAW:
				return GL_STREAM_DRAW;
			}
			return glEnumValue;
		}


		unsigned GenerateGLEnum(AccessFrequency frequency, AccessType type)
		{
			unsigned glEnumValue = GL_STATIC_DRAW;
			switch (frequency)
			{
			case AccessFrequency::STATIC:
				return GenerateGLEnumStatic(type);
			case AccessFrequency::DYNAMIC:
				return GenerateGLEnumDynamic(type);

			case AccessFrequency::STREAM:
				return GenerateGLEnumStream(type);
			}
			return glEnumValue;
		}

		Buffer::Buffer(BufferData& data, AccessFrequency frequency, AccessType type, BufferType bufferType = BufferType::DATA) :
			data(data),
			bufferType(bufferType)
		{
	
			glGenBuffers(1, &buffer);
			glBindBuffer(bufferType, buffer);
			glBufferData(bufferType, sizeof(VecType) * data.size(), data.data(), GenerateGLEnum(frequency, type));
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &buffer);
		}


		unsigned Buffer::ElementSizeInBytes() const
		{
			return sizeof(VecType);
		}

		void Buffer::Activate() const
		{
			glBindBuffer(bufferType, buffer);
		}
	private:
		unsigned buffer;
		BufferData data;
		BufferType bufferType=GL_ARRAY_BUFFER;
	};

}