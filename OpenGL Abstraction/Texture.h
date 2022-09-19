#pragma once
#include "glew.h"
#include "glfw3.h"
#include <string> 
#include "Dependencies/vendor/stb_image/stb_image.h"

class Texture {
public:
	Texture(const std::string path) 
		: m_Renderer_ID(0), filepath(path), local_buffer(nullptr), height(0), width(0), m_BPP(0)
	{
		stbi_set_flip_vertically_on_load(1); 
		local_buffer = stbi_load(path.c_str(), &width, &height, &m_BPP, 4);

		glGenTextures(1, &m_Renderer_ID);
		glBindTexture(GL_TEXTURE_2D, m_Renderer_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer); 
		glBindTexture(GL_TEXTURE_2D, 0);

		if (local_buffer)
		{
			stbi_image_free(local_buffer); 
		}
	}

	~Texture()
	{
		glDeleteTextures(1, &m_Renderer_ID);
	}

	void Bind(unsigned int slot = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + slot); 
		glBindTexture(GL_TEXTURE_2D, m_Renderer_ID);
	}
	void unBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0); 
	}

private:
	unsigned int m_Renderer_ID;
	std::string filepath;
	unsigned char* local_buffer;
	int height, width, m_BPP;

};