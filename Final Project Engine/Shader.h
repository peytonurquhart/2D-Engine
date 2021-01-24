#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

using std::string;

/*COMPILES a Shader and returns its unique unsigned int ID*/
unsigned int CompileShader(unsigned int type, const string & source);

/*Creates a shader and returns its unique unsigned int ID*/
unsigned int CreateShadervf(const string & vertexShader, const string & fragmentShader);

/*Defines two different types of data, for colored shaders and textures to clean up code in the shader class*/
enum dataType { fourF, oneI };

enum direction { south, west, north, east };


class Shader
{
public:
	virtual ~Shader();

	Shader() { return; }

	/*Initializes a shader given a specifier string, dataType, and texture slot if applicable*/
	Shader(const string &InitFile, dataType u_Type, int textureSlot = 0);
	void Init(const string &InitFile, dataType u_Type, int textureSlot);

	/*Creates a uniform location*/
	void Create(const char *locationKey);

	/*Return ID*/
	virtual unsigned int ID();

	/*Returns uniform location*/
	int Location();

	/*Binds the shader*/
	virtual void Use();

	/*Updates the shaders uniform*/
	void UpdateUniform();

	/*Sets the shader to new rgb values*/
	void setRgb(float r, float g, float b);

	void setTextureSlot(int &slot) { this->textureSlot = slot; }

	virtual void unBind();

	string getVertexString();

	string getFragmentString();

private:

	int loc;

	unsigned int shaderID;

	string sVertex;

	string sFragment;

	dataType U_Type;

	float rgb[3];

	int textureSlot;
};
