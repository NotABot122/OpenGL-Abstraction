#pragma once
#include "Display.h"
#include <iostream>
#include <vector>


struct Elements {
public:
	unsigned int count;
	unsigned int type;
	bool normalized;
	Elements(unsigned int lay, unsigned int typ) : count(lay), type(typ), normalized(false) {}
	const unsigned int GetSize() const
	{
		switch (type) 
		{
		case(GL_FLOAT): return 4;
		case(GL_UNSIGNED_INT): return 4; 
		case(GL_UNSIGNED_BYTE): return 1; 
		}
		return 0;
	} 
};

class BufferLayout {

public:

	BufferLayout(std::vector<unsigned int>& count, std::vector<unsigned int> type) : m_Stride(0) {
		if (count.size() != type.size()) std::cout << "Error in Buffer Layout" << std::endl;

		for (unsigned int i = 0; i < count.size(); i++)
		{
			m_Elements.push_back({ count[i], type[i] });
		}

		for (unsigned int i = 0; i < m_Elements.size(); i++)
		{
			m_Stride += m_Elements[i].count * m_Elements[i].GetSize(); 

		}
	}

	const std::vector<Elements> GetElements() const { return m_Elements; };
	const unsigned int GetStride() const { return m_Stride; }
private:
	std::vector<Elements> m_Elements;
	unsigned int m_Stride;
};