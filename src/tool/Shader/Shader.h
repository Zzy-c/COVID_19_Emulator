#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string.h>
#include <SysConfig.h>

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	void Use();
	template<typename T>
	void Set(const std::string& name, T value) const;
private:
	void CheckCompileErrors(unsigned int shader, std::string type);
};
