#include "Shader.h"

Shader::Shader(const char* filePath, GLenum type)
{
	std::ifstream shaderSourceFile;
	shaderSourceFile.open(filePath, std::fstream::in);
	if (!shaderSourceFile.good() || shaderSourceFile.bad()) { throw ((new std::string("Can't open file on path: "))->append(*(new std::string(filePath)))); }

	std::stringstream shaderString;
	shaderString << shaderSourceFile.rdbuf();
	const char* shaderCode = shaderString.str().c_str();
	shaderSourceFile.close();

	unsigned int shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &shaderCode, 0);
	glCompileShader(shaderId);
	checkCompilerErrors(shaderId, "SHADER");

	unsigned int programId = glCreateProgram();
	glAttachShader(programId, shaderId);
	glLinkProgram(programId);
	checkCompilerErrors(programId, "PROGRAM");

	glDeleteShader(shaderId);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(Id);
}

void Shader::checkCompilerErrors(unsigned int shaderId, std::string type)
{
	int sucess;
	char message[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(shaderId, 1024, 0, message);
			std::cout << "Compilation error. Type: " + type + "\r\nMessage: " << message << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shaderId, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			glGetProgramInfoLog(shaderId, 1024, 0, message);
			std::cout << "Linking error. Type: " + type + "\r\nMessage: " << message << std::endl;
		}
	}
}
