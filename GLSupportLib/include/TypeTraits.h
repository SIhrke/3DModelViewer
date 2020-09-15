#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
template <typename T>
struct OpenGLTraits;


template <>
struct OpenGLTraits<float> 
{
	static const int size = 1;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<double>
{
	static const int size = 1;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<int>
{
	static const int size = 1;
	static const unsigned glType = GL_INT;
};
template <>
struct OpenGLTraits<unsigned int>
{
	static const int size = 1;
	static const unsigned glType = GL_UNSIGNED_INT;
};

template <>
struct OpenGLTraits<glm::vec2>
{
	static const int size = 2;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<glm::vec3>
{
	static const int size = 3;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<glm::vec4>
{
	static const int size = 4;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<glm::mat3x3>
{
	static const int size = 9;
	static const unsigned glType = GL_FLOAT;
};

template <>
struct OpenGLTraits<glm::mat4x4>
{
	static const int size = 16;
	static const unsigned glType = GL_FLOAT;
};