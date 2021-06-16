/*
* Source: https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader_s.h
*/

#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <glad/glad.h>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

class Shader
{
private:
	unsigned int Id;

public:
	Shader(const char* filePath, GLenum type);
	~Shader();

	void use();

private:
	void checkCompilerErrors(unsigned int shaderId, std::string type);
};

#endif