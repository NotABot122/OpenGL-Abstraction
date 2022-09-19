#pragma once
#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
#include <vector>

class Shader
{
public:
	Shader(std::string& file) {
		uniforms = std::vector<int>{};
		std::ifstream stream(file);
		std::string line;
		bool vertex = false;
		bool fragment = false;
		std::stringstream ss[2];
		while (std::getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					vertex = true;
					fragment = false;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					vertex = false;
					fragment = true;
				}

			}
			else {
				if (vertex)
					ss[0] << line << "\n";
				if (fragment)
					ss[1] << line << "\n";
			}
		}
		const std::string vertex_shader = ss[0].str();
		const std::string fragment_shader = ss[1].str();
		//std::cout << vertex_shader << std::endl; error handling
		//std::cout << fragment_shader << std::endl; error handling
		id = Create_Shader(vertex_shader, fragment_shader); 
	}

	unsigned int id;


	int Get_Uniform(const char* var_name)
	{
		glUseProgram(this->id);
		int location = glGetUniformLocation(this->id, var_name);

		uniforms.push_back(location);
		auto w = std::find(uniforms.begin(), uniforms.end(), location);
		if (w != uniforms.end()) {
			for (unsigned int i = 0; i < uniforms.size(); i++)
			{
				if (uniforms[i] == location) return uniforms[i]; 
			}
		}
		return uniforms[uniforms.size() - 1];
	}
	void Set_Uniform4f(int uniform, float red, float blue, float green)
	{
		glUseProgram(this->id); 
		glUniform4f(uniform, red, blue, green, 1.0f);
	}


	void SetUniform1i(const char* name, int value)
	{
		glUseProgram(this->id);
		glUniform1i(Get_Uniform(name), value);
	}


	std::vector<int> uniforms;

private:

	static unsigned int Create_Shader(const std::string& VertexShader, const std::string& FragmentShader) {
		unsigned int program = glCreateProgram();
		unsigned int vs = Compile_Shader(VertexShader, GL_VERTEX_SHADER);
		unsigned int fs = Compile_Shader(FragmentShader, GL_FRAGMENT_SHADER);
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);
		int status;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
		std::cout << status;
		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}
	static unsigned int Compile_Shader(const std::string& source, unsigned int type)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();

		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);
		//TODO: Error Handling
		return id;
	} 


};

