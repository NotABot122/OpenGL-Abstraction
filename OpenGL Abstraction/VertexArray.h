#pragma once
#include <glew.h>
#include <glfw3.h>
#include "VertexBuffer.h"

class VertexArray {
public:
	VertexArray() {
		glGenVertexArrays(1, &m_rendererID);
		glBindVertexArray(m_rendererID);
	}

	void AddBuffer(VertexBuffer& vb) {
		Bind(); 
		vb.Bind(); 
		auto& elements = vb.layout->GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			auto& element = elements[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, element.count , element.type, element.normalized ? GL_TRUE : GL_FALSE, vb.layout->GetStride(), (const void*)offset); 
			offset += element.count * element.GetSize(); 
		}
		
	}

	const void Bind() const
	{
		glBindVertexArray(m_rendererID); 
	}
private:
	unsigned int m_rendererID; 
};