#pragma once

#include <GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION

#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "stb_image.h"

class Texture
{
private:
GLuint textureID;

public:

GLenum section;
	
	Texture():
	section(GL_TEXTURE0)
	{}
	void Load(const char* path)
	{
		stbi_set_flip_vertically_on_load(false);
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		 
		int width, height, channels;
		unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
		
		if(!data)
		{
			std::cerr << "failed to load image: " << path << std::endl;
			return;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, channels+0x1904, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		
		stbi_image_free(data);
	}
	
	inline void Use() const
	{
		glActiveTexture(section);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	
	inline GLuint GetTexture() const
	{
		return textureID;
	}
};

GLuint LoadImage(const char* path)
{
	stbi_set_flip_vertically_on_load(false);
	
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	
	if(!data)
	{
		std::cerr << "failed to load image: " << path << std::endl;
		return -1;
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, channels+0x1904, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	
	return textureID;
}
