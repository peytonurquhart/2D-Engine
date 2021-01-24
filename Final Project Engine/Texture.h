#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>


/*
		Texture Shader

		- VAO must be bound before the texture is bound since it binds to a VAO!


*/


class Texture : public Shader
{
public:
	~Texture() { /*glDeleteTextures(1, &ID);*/ return; }

	Texture(const string shaderFile, const string imageFile, bool flipVertically, GLenum textureSlot, GLenum minMaxFilterParam = GL_LINEAR_MIPMAP_LINEAR, GLenum textureWrapParam = GL_REPEAT);

	//1 call
	void Use();

	void Use(GLenum slot);

	void unBind();

	unsigned int texID() { return Shader::ID(); }

	void freeTexture() { glDeleteTextures(1, &ID); return; }

private:

	unsigned int ID;
	unsigned char *imageBuffer;

	GLenum textureSlot;

	int width;
	int height;
	int bpp;
};



