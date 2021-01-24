#include "Init.h"

Enemy::Enemy()
{
	xSpeed = 0;
	ySpeed = 0;

	spawn[0] = 0;
	spawn[1] = 0;
}

Enemy::~Enemy(){}

Enemy::Enemy(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY)
{
	Rectangle::Init(ENEMY_SIZE, ENEMY_SIZE);


	this->xSpeed = xNewSpeed;
	this->ySpeed = yNewSpeed;

	this->spawn[0] = spawnX;
	this->spawn[1] = spawnY;

	box.Init(ENEMY_SIZE);
	border.Init(1, true, 0.005);

	box.Translate(spawn[0], spawn[1]);
	Rectangle::Translate(spawn[0], spawn[1]);
}



void Enemy::init(float xNewSpeed, float yNewSpeed, float spawnX, float spawnY)
{
	Rectangle::Init(ENEMY_SIZE, ENEMY_SIZE);


	this->xSpeed = xNewSpeed;
	this->ySpeed = yNewSpeed;

	this->spawn[0] = spawnX;
	this->spawn[1] = spawnY;

	box.Init(ENEMY_SIZE);
	border.Init(1, true, 0.005);

	box.Translate(spawn[0], spawn[1]);
	Rectangle::Translate(spawn[0], spawn[1]);
}

int Enemy::iterate()
{
	Boundlimit lim = Unbound;
	if (border.isInBounds(box) == Upper)
	{
		this->setMoveY((-1 * ySpeed));
		cout << "hit upper";
	}
	else if (border.isInBounds(box) == Lower)
	{
		this->setMoveY((-1 * ySpeed));
	}
	else if (border.isInBounds(box) == Left)
	{
		this->setMoveX((-1 * xSpeed));
	}
	else if (border.isInBounds(box) == Right)
	{
		this->setMoveX((-1 * xSpeed));
	}

	Rectangle::Translate(this->xSpeed, this->ySpeed);
	box.Translate(this->xSpeed, this->ySpeed);

	return 1;
}

void Enemy::setMoveX(const float &moveX)
{
	this->xSpeed = moveX;
}


void Enemy::setMoveY(const float &moveY)
{
	this->ySpeed = moveY;
}

void Enemy::draw()
{
	this->Rectangle::Bind();
	this->Rectangle::BufferVertex();
	this->Rectangle::Draw();
	this->Rectangle::Unbind();
}