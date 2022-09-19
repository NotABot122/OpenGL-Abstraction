#pragma once
#include "glew.h"
#include "glfw3.h"

class IndexBuffer
{
public:
	IndexBuffer(unsigned int* temp, int size) 
	{
		ptr = new unsigned int;
		buffer = temp;
		glGenBuffers(1, ptr); 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ptr);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), temp, GL_STATIC_DRAW);
		count = size; 
		return;
	}

	int count;
	unsigned int* ptr;
	unsigned int* buffer;

};
