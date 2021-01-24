#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>



class Enemy : public Rectangle
{
public:
	Enemy();
	Enemy(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY);

	~Enemy();

	void init(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY);

	//Hitbox getHitBox();

	//void setHitBox(Hitbox newBox);

	void setMoveX(const float &moveX);
	void setMoveY(const float &moveY);

	void draw();

	// move
	int iterate();

private:
	float xSpeed;
	float ySpeed;
	float spawn[2];
	Bounds border;
	Hitbox box;
};

