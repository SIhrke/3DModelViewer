#include "Buffer.h"
#include <glad/glad.h>

namespace gl 
{
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
	
	Buffer::Buffer(BufferData&& data, AccessFrequency frequency, AccessType type):
	data(data)
	{
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VecType)*data.size(), data.data(), GenerateGLEnum(frequency,type));
	}
	unsigned Buffer::ElementSizeInBytes() const
	{
		return sizeof(VecType);
	}

	void Buffer::Activate() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
	}
}