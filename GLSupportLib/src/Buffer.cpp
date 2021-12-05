#include "Buffer.h"

using namespace gl;


unsigned gl::GenerateGLEnumStatic(AccessType type)
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

unsigned gl::GenerateGLEnumDynamic(AccessType type)
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

unsigned gl::GenerateGLEnumStream(AccessType type)
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


unsigned gl::GenerateGLEnum(AccessFrequency frequency, AccessType type)
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
