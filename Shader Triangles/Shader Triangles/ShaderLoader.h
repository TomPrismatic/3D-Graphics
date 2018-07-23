#pragma once

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include <iostream>


class ShaderLoader
{
	private:

		std::string ReadShader(const char *filename);
		GLuint CreateShader(GLenum shaderType,
			std::string source,
			const char* shaderName);

	public:
		ShaderLoader(void);
		~ShaderLoader(void);
		GLuint CreateProgram(const char* VertexShaderFilename,
			const char* FragmentShaderFilename);

};
