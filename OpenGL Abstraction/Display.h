#pragma once
#include "glew.h"
#include "glfw3.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Template.h"
#include "Texture.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>

class Display
{
	
public:
	Display() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); 
		if (window == nullptr)
		{
			window = glfwCreateWindow(1000, 500, "GL_Lib", NULL, NULL);
		}
		glfwMakeContextCurrent(window); 
		glewInit(); 
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	};
	static GLFWwindow* window;


	static void Draw_Index_Buffer_Texture(Template& t, Texture& text)  
	{
		glBindBuffer(GL_ARRAY_BUFFER, *t.vb->ptr);
		text.Bind(); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *t.ib->ptr);
		glUseProgram(t.shader->id);
		glDrawElements(GL_TRIANGLES, t.ib->count, GL_UNSIGNED_INT, nullptr); 
		text.unBind();
	}
	
	static void Draw_Index_Buffer(Template& t)
	{
		glBindBuffer(GL_ARRAY_BUFFER, *t.vb->ptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *t.ib->ptr);
		glUseProgram(t.shader->id);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDrawElements(GL_TRIANGLES, t.ib->count, GL_UNSIGNED_INT, nullptr);
	}

	static void GLCheckError() {
		while (GLenum error = glGetError())
		{
			std::cout << "Error (" << error << ")" << std::endl;
		}

	}

	static void GLClearError()
	{
		while(glGetError() != GL_NO_ERROR); 
	}

	
};
