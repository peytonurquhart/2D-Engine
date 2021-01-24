#include "Init.h"

Texture::Texture(const string shaderFile, const string imageFile, bool flipVertically, GLenum textureSlot, GLenum minMaxFilterParam, GLenum textureWrapParam)
{
	this->textureSlot = textureSlot;

	stbi_set_flip_vertically_on_load(flipVertically);

	imageBuffer = stbi_load(imageFile.c_str(), &width, &height, &bpp, 4);

	if (!imageBuffer)
	{
		cout << "Failed to create image buffer / texture failed" << endl;
		return;
	}
	glActiveTexture(textureSlot); //specify slot

	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);

	// ->

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMaxFilterParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMaxFilterParam);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrapParam);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrapParam);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageBuffer);

	Shader::Init(shaderFile, oneI, textureSlot);

}

void Texture::Use()
{
	glActiveTexture(textureSlot); 
	glBindTexture(GL_TEXTURE_2D, ID);

	glUseProgram(Shader::ID());
}

void Texture::Use(GLenum slot)
{
	this->textureSlot = slot;
	Shader::UpdateUniform();

	glActiveTexture(slot); 
	glBindTexture(GL_TEXTURE_2D, ID);

	glUseProgram(Shader::ID());
}


void Texture::unBind()
{
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
