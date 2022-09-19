#pragma once
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Template
{
public:
	Template(Shader& s, IndexBuffer& i, VertexBuffer& v)
		: shader(&s), ib(&i), vb(&v) 
	{}

	Shader* shader;
	IndexBuffer* ib;
	VertexBuffer* vb;
	
};

