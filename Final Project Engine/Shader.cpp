#include "Init.h"




unsigned int CompileShader(unsigned int type, const string & source)
{
	unsigned int id = glCreateShader(type);

	const char *src = &source[0];

	glShaderSource(id, 1, &src, nullptr);

	glCompileShader(id);

	//do: error handling here


	//ERROR CHECK
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char *)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader" << std::endl;
		std::cout << message << std::endl;
		//glDeleteShader(id);
		return 0;
	}

	return id;

}


unsigned int CreateShadervf(const string & vertexShader, const string & fragmentShader)
{
	unsigned int program = glCreateProgram();

	unsigned int vertexShad = CompileShader(GL_VERTEX_SHADER, vertexShader);
	//creating an id for the vertex shader (called per vertex)

	unsigned int fragmentShad = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	//creating an id for a fragment shader (called per pixel in the shape)

	glAttachShader(program, vertexShad);
	glAttachShader(program, fragmentShad);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShad);
	glDeleteShader(fragmentShad);
	//the shaders are linked to the program which has been created now, so now they can be freed

	return program;
}



void Shader::Init(const string &InitFile, dataType u_Type, int textureSlot)
{
	string temp;
	stringstream vertexString;
	stringstream fragmentString;

	this->U_Type = u_Type;
	this->textureSlot = textureSlot;

	for (int i = 0; i < 3; i++)
	{
		rgb[i] = 1.0f;
	}

	fstream infile;
	infile.open(InitFile);

	if (!infile.is_open())
	{
		std::cout << "Error opening file " << InitFile << std::endl;
	}

	enum ShaderType
	{
		none, vertex, frag
	};

	ShaderType currentType = none;

	while (getline(infile, temp))
	{
		if (temp.find("#shader") != string::npos)
		{
			if (temp.find("vertex") != string::npos)
			{
				currentType = vertex;
			}
			else if (temp.find("fragment") != string::npos)
			{
				currentType = frag;
			}
			else
			{
				std::cout << "#shader define found with invalid type in ParseFile" << std::endl;
			}
		}
		else
		{
			switch (currentType)
			{
			case vertex:
				vertexString << temp << '\n';
				break;
			case frag:
				fragmentString << temp << '\n';
				break;
			default:
				break;
			}
		}
	}

	infile.close();

	this->sVertex = vertexString.str();
	this->sFragment = fragmentString.str();
}


Shader::Shader(const string &InitFile, dataType u_Type, int textureSlot)
{
	string temp;
	stringstream vertexString;
	stringstream fragmentString;

	this->U_Type = u_Type;
	this->textureSlot = textureSlot;

	for (int i = 0; i < 3; i++)
	{
		rgb[i] = 1.0f;
	}

	fstream infile;
	infile.open(InitFile);

	if (!infile.is_open())
	{
		std::cout << "Error opening file " << InitFile << std::endl;
	}

	enum ShaderType
	{
		none, vertex, frag
	};

	ShaderType currentType = none;

	while (getline(infile, temp))
	{
		if (temp.find("#shader") != string::npos)
		{
			if (temp.find("vertex") != string::npos)
			{
				currentType = vertex;
			}
			else if (temp.find("fragment") != string::npos)
			{
				currentType = frag;
			}
			else
			{
				std::cout << "#shader define found with invalid type in ParseFile" << std::endl;
			}
		}
		else
		{
			switch (currentType)
			{
			case vertex:
				vertexString << temp << '\n';
				break;
			case frag:
				fragmentString << temp << '\n';
				break;
			default:
				break;
			}
		}
	}

	infile.close();

	this->sVertex = vertexString.str();
	this->sFragment = fragmentString.str();
}

void Shader::unBind()
{
	glUseProgram(0);
}

void Shader::setRgb(float r, float g, float b)
{
	rgb[0] = r;

	rgb[1] = g;

	rgb[2] = b;
}

int Shader::Location()
{
	return this->loc;
}

unsigned int Shader::ID()
{
	return this->shaderID;
}


void Shader::Create(const char *locationKey)
{
	unsigned int temp = CreateShadervf(sVertex, sFragment);

	int location = 0;

	location = glGetUniformLocation(temp, locationKey);

	if (location == -1)
		cout << "uniform " << locationKey << " failed" << endl;

	this->loc = location;
	this->shaderID = temp;
}

void Shader::Use()
{
	glUseProgram(shaderID);
}


void Shader::UpdateUniform()
{
	//the uniform name that we created the location out of must match! (u_Color or u_Texture)

	switch (this->U_Type)
	{
	case fourF:
		glUniform4f(loc, rgb[0], rgb[1], rgb[2], 1.0f);
		break;
	case oneI:
		glUniform1i(loc, textureSlot);
		break;
	default:
		cout << "Update Uniform enum Datatype Not Recognized" << endl;
	}
}


Shader::~Shader()
{
	glDeleteProgram(this->shaderID);
}


string Shader::getVertexString()
{
	return this->sVertex;
}

string Shader::getFragmentString()
{
	return this->sFragment;
}
