#pragma once

#include "Init.h"
#include "BuildingGame\Chunk.h"

class Human
{
public:
	/* initializes a new player into the game world*/
	Human(float speed, float size, Texture *headTex, Texture *torsoTex, Texture *armTex, Texture *legTex, float legSpeed = 0.065f, float legRadians = 0.52f, float armSpeed = 0.015f, float armRadians = 0.18f, int jumpDuration = 18);

	/* draws the players front profile*/
	void DrawFrontProfile();

	/* draws the player hitboxes for testing purposes*/
	void DrawHitBoxes(Shader *shad);

	/* translate with updating the players gameworld position*/
	void Translate(float x, float y);

	/* translates the player without updating the players gameworld position*/
	void FreeTranslate(float x, float y);

	//1 = right, 2 = up, 3 = left, 4 = down, flys the user around the map
	void Fly(int direc, float ratio = 1.0f);

	/*return true if the character is / should be falling, checks collision with the given chunks*/
	bool Fall(Chunk **nearChunks, int numChunks, GLFWwindow *activeWin);

	/*allows the character to walk side to side if the correct keys are pressed, checks collision with the given chunks*/
	void Walk(Chunk **nearChunks, int numChunks, GLFWwindow *activeWin);

	/*allows the user to jump, and if the user is in a jump iterates that jump, checks collison with the given chunks*/
	void Jump(Chunk **nearChunks, int numChunks, GLFWwindow * activeWin);

	/* iterate one frame of the players walking animation*/
	void iterateWalkAnimation();

	/* iterates one frame of the player swinging his arms*/
	void iterateArmSwingAnimation();

	/*iterates on frame of returning the player to his natural stance before animation*/
	void iterateReturnToStance();

	/*returns a pointer to the players array of hitboxes*/
	Hitbox * getHitboxes() { return &hb[0]; }

	/* returns the number of hitboxes the player has*/
	int getNumHitboxes() { return (int)sizeof(hb) / sizeof(Hitbox); }

	/* get the static speed of the player*/
	float getSpeed() { return speed; }

	/* PLAYER CONTROLLER: mode 1 = walk, mode 2 = fly: pass in a pointer to the chunks which should be polled for and the number of chunks in the scene*/
	bool pollForInput(int mode, Chunk **nearChunks, int numChunks, GLFWwindow *activeWindowPointer);

	/* approximate x value in the game world, perspective translations aside*/
	float getGameX() { return x; }

	/* gets the players approximate xPosition on the screen (not for the players position in the game world)*/
	float getX() { float o[2]; hb[1].getOrigin(o); return o[0]; }

	/*return true if the player has moved further in either direction than they ever have by a factor of distance*/
	bool pollForFurthestDistance(float distance);

private:

	float x;

	float size;
	float speed;
	
	float legSpeed;
	float armSpeed;
	float legRadians;
	float armRadians;

	int jumpDuration;
	bool isInJump;

	RectangleT head;
	RectangleT torso;
	RectangleT arm[2];
	RectangleT leg[2];

	Hitbox hb[3];

	Texture *headTex;
	Texture *torsoTex;
	Texture *legTex;
	Texture *armTex;

	bool pollForFlyInput(Chunk **nearChunks, int numChunks, GLFWwindow *activeWindowPointer);
};