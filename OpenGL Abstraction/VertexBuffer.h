#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "BufferLayout.h"

class VertexBuffer
{
public:
	VertexBuffer(std::vector<float>& buf) : layout(nullptr) {
		ptr = new unsigned int;
		const int size = buf.size();
		buffer = &buf;
		glGenBuffers(1, ptr);
		glBindBuffer(GL_ARRAY_BUFFER, *ptr);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), &buf[0], GL_STATIC_DRAW);  
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		count = size; 
		layout = nullptr; 
	}

	const void Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, *ptr);
	}
	
	void Transform(float x, float y)
	{
		for (unsigned int i = 0; i < count; i += layout->GetStride() / sizeof(float))
		{
			(*buffer)[i] += x;
			(*buffer)[i + 1] += y;								// Finsh function
		}

		glBindBuffer(GL_ARRAY_BUFFER, *ptr);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), &(*buffer)[0], GL_STATIC_DRAW);
	}

	void BindLayout(BufferLayout& lay) 
	{
		layout = &lay;
	}

	unsigned int count;
	std::vector<float>* buffer;
	unsigned int* ptr;

	BufferLayout* layout;
	
};