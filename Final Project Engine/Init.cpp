#include "Init.h"


void Round(float buff, float *n)
{
	if (*n > 0)
	{
		if (*n < buff)
		{
			*n = 0;
			return;
		}
	}
	else if (*n < 0)
	{
		buff = buff * -1;
		if (*n > buff)
		{
			*n = 0;
			return;
		}
	}
}

gameWindow::gameWindow()
{
	this->window = nullptr;
}

gameWindow::gameWindow(int width, const char *windowName)
{
	window = glfwCreateWindow(width, width * SQ_ASPECT_RATIO, windowName, NULL, NULL);
	this->width = width;
	this->height = width * SQ_ASPECT_RATIO;
}

void gameWindow::Create(int width, const char *windowName)
{
	if (window == nullptr)
	{
		window = glfwCreateWindow(width, width * SQ_ASPECT_RATIO, windowName, NULL, NULL);
		this->width = width;
		this->height = width * SQ_ASPECT_RATIO;
	}
	else
	{
		cout << "Window.Create() called but the window was already created!" << endl;
	}
}

void gameWindow::makeCoreProfile(int versionMajor, int versionMinor)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool gameWindow::validateWindow()
{
	if (window == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void gameWindow::makeCurrentContext()
{
	glfwMakeContextCurrent(this->window);
}

void gameWindow::vSync(bool tf)
{
	switch (tf)
	{
	case true:
		glfwSwapInterval(1);
		break;
	case false:
		glfwSwapInterval(0);
		break;
	}

	return;
}

GLFWwindow * gameWindow::get()
{
	return this->window;
}
