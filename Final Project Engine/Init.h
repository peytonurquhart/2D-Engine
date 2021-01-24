#pragma once



#define GLEW_STATIC

#define RELEASE_MODE false

#define SQ_ASPECT_RATIO 0.5625
#define SQ_RATIO_RECIP 1 / SQ_ASPECT_RATIO

#define _CRT_SECURE_NO_WARNINGS

#define PI 3.1415926

#define ROUND_TO_ZERO 0.0000001




/* STD libs*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <time.h>
#include <thread>

/* Graphics */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

/* Audio */
#include <irrKlang.h>

/* Local */
#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Hitbox.h"
#include "HitArray.h"
#include "Bounds.h"
#include "Circle.h"
#include "GraphicNumber.h"
#include "ScoreBoard.h"
#include "FireTimer.h"
#include "Sound.h"
#include "Shader.h"
#include "Texture.h"

using std::string;
using std::fstream;
using std::getline;
using std::stringstream;
using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::queue;
using namespace irrklang;


/*Abstraction of GLFWwindow functions to clean up code*/
class gameWindow
{
public:
	gameWindow();
	gameWindow(int width, const char *windowName);

	void Create(int width, const char *windowName);

	void makeCoreProfile(int versionMajor = 3, int versionMinor = 3);

	bool validateWindow();

	void makeCurrentContext();

	void vSync(bool tf);

	void Clear() { glClear(GL_COLOR_BUFFER_BIT); }

	GLFWwindow * get();

	int getWidth() { return width; }
	int getHeight() { return height; }

private:
	GLFWwindow *window;
	int width;
	int height;
};
