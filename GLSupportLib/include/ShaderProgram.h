#pragma once
#include <string>

namespace gl
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		void Activate();
	private:
		unsigned shaderProgram,vertexShader,fragmentShader;
	};

}