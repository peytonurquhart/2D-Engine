#include "Human.h"

Human::Human(float speed, float size, Texture *headTex, Texture *torsoTex, Texture *armTex, Texture *legTex, float legSpeed, float legRadians, float armSpeed, float armRadians, int jumpDuration)
{
	this->headTex = headTex;
	this->torsoTex = torsoTex;
	this->armTex = armTex;
	this->legTex = legTex;
	this->speed = speed;
	this->size = size;
	this->legSpeed = legSpeed;
	this->legRadians = legRadians;
	this->armSpeed = armSpeed;
	this->armRadians = armRadians;
	this->isInJump = false;
	this->jumpDuration = jumpDuration;
	this->x = 0.0f;

	head.Init(size, size, 0);
	torso.Init(size * 1.5, size, 0);

	arm[0].Init(size * 1.5, size / 2, 0);
	arm[1].Init(size * 1.5, size / 2, 0);

	leg[0].Init(size * 1.5, size / 2, 0);
	leg[1].Init(size * 1.5, size / 2, 0);

	head.MoveToOrigin();
	torso.MoveToOrigin();
	arm[0].MoveToOrigin();
	arm[1].MoveToOrigin();
	leg[0].MoveToOrigin();
	leg[1].MoveToOrigin();

	torso.Translate(0, size * -1);
	arm[0].Translate(size * -1 * SQ_ASPECT_RATIO, size * -1);
	arm[1].Translate(size / 2 * SQ_ASPECT_RATIO, size * -1);
	leg[0].Translate(size / 2 * -1 * SQ_ASPECT_RATIO, size * -2.45);
	leg[1].Translate(0, size * -2.45);

	leg[0].Translate(size / 20 * -1, 0);
	leg[1].Translate(size / 20, 0);

	arm[0].FreeRotate(-0.1);
	arm[1].FreeRotate(0.1);

	leg[0].FreeRotate(-0.09);
	leg[1].FreeRotate(0.09);

	for (int i = 0; i < 3; i++)
	{
		hb[i].Init(size * 1.2);
		hb[i].MoveToOrigin();
		hb[i].Translate(-1 * size / 1.6, -2 * i * size);
	}
	
	hb[1].Translate(0, -1 * size);
	hb[0].Translate(0, -1 * size * 2.0f);
}

void Human::DrawHitBoxes(Shader *shad)
{
	shad->Use();
	for (int i = 0; i < 3; i++)
	{
		hb[i].Bind();
		hb[i].BufferVertex();
		hb[i].Draw();
		hb[i].Unbind();
	}
	shad->unBind();
}

void Human::DrawFrontProfile()
{
	GLenum slot = GL_TEXTURE0;

	armTex->Use();
	// or
	// armTex->Use();

	arm[0].Bind();
	arm[0].BufferVertex();
	arm[0].Draw();
	arm[0].Unbind();
	arm[1].Bind();
	arm[1].BufferVertex();
	arm[1].Draw();
	arm[1].Unbind();

	armTex->unBind();


	legTex->Use();
	// or
	// legTex->Use(); etc..

	leg[0].Bind();
	leg[0].BufferVertex();
	leg[0].Draw();
	leg[0].Unbind();
	leg[1].Bind();
	leg[1].BufferVertex();
	leg[1].Draw();
	leg[1].Unbind();

	legTex->unBind();



	torsoTex->Use();

	torso.Bind();
	torso.BufferVertex();
	torso.Draw();
	torso.Unbind();

	torsoTex->unBind();



	headTex->Use();

	head.Bind();
	head.BufferVertex();
	head.Draw();
	head.Unbind();

	headTex->unBind();
}

void Human::Translate(float x, float y)
{
	head.Translate(x, y);
	torso.Translate(x, y);
	leg[0].Translate(x, y);
	leg[1].Translate(x, y);
	arm[0].Translate(x, y);
	arm[1].Translate(x, y);
	for (int i = 0; i < 3; i++)
	{
		hb[i].Translate(x, y);
	}

	this->x += x;
}

void Human::FreeTranslate(float x, float y)
{
	head.Translate(x, y);
	torso.Translate(x, y);
	leg[0].Translate(x, y);
	leg[1].Translate(x, y);
	arm[0].Translate(x, y);
	arm[1].Translate(x, y);
	for (int i = 0; i < 3; i++)
	{
		hb[i].Translate(x, y);
	}
}

//1 = right, 2 = up, 3 = left, 4 = down
void Human::Fly(int direc, float ratio)
{
	if (direc == 2)
	{
		Translate(0, speed / ratio);
	}
	if (direc == 4)
	{
		Translate(0, -1 * speed / ratio);
	}
	if (direc == 3)
	{
		Translate(-1 * speed / ratio, 0);
	}
	if (direc == 1)
	{
		Translate(speed / ratio, 0);
	}
}

bool Human::pollForInput(int mode, Chunk **nearChunks, int numChunks, GLFWwindow *activeWindowPointer)
{
	if (mode == 1)
	{
		if (!Fall(nearChunks, numChunks, activeWindowPointer))
		{
			Jump(nearChunks, numChunks, activeWindowPointer);
		}

		Walk(nearChunks, numChunks, activeWindowPointer);
	}
	else if (mode == 2)
	{
		return pollForFlyInput(nearChunks, numChunks, activeWindowPointer);
	}
	else
	{
		cout << "Invalid mode selected: Human::pollForInput: " << mode << endl;
	}
}


void Human::Jump(Chunk **nearChunks, int numChunks, GLFWwindow * activeWin)
{
	int ratio = 1;
	bool isMove = false;
	static int i = 0;

	if ((glfwGetKey(activeWin, GLFW_KEY_SPACE) == GLFW_PRESS || isInJump))
	{

		/*if they just jumped*/
		if (isInJump == false)
		{
			i = 0;
			isInJump = true;
		}
		i++;

		if (i < jumpDuration)
		{

			int val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 2, 1))
					val = true;
			}
			if (!val)
			{
				Fly(2, ratio);
				isMove = true;
			}
			else
			{
				val = false;
				for (int i = 0; i < numChunks; i++)
				{
					if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 2, 1))
						val = true;
				}
				if (!val)
				{
					Fly(2, 4);
					isMove = true;
				}
				else
				{
					//this cancels the jump immediatly if the user hits a ceiling
					isInJump = false;
				}

			}

		}
		else
		{
			isInJump = false;
		}

	}
}

bool Human::Fall(Chunk **nearChunks, int numChunks, GLFWwindow *activeWin)
{
	bool isMove = false;
	int val = false;

	if (!isInJump)
	{

		for (int i = 0; i < numChunks; i++)
		{
			if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() * 2, 4, 1))
				val = true;
		}
		if (!val)
		{
			Fly(4, 0.5);
			isMove = true;
		}
		else
		{
			val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 4, 1))
					val = true;
			}
			if (!val)
			{
				Fly(4, 4);
				isMove = true;
			}

		}

	}
	return isMove;
}



void Human::Walk(Chunk **nearChunks, int numChunks, GLFWwindow *activeWin)
{
	int ratio = 1;
	bool isMove = false;

	bool stance = false;

		if (glfwGetKey(activeWin, GLFW_KEY_A) == GLFW_PRESS)
		{
			int val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 3, 1))
					val = true;
			}
			if (!val)
			{
				Fly(3, ratio);
				isMove = true;
			}
			else
			{
				val = false;
				for (int i = 0; i < numChunks; i++)
				{
					if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 3, 1))
						val = true;
				}
				if (!val)
				{
					Fly(3, 4);
					isMove = true;
				}

			}

			iterateWalkAnimation();
			iterateArmSwingAnimation();
		}
		else
		{
			stance = true;
		}


		if (glfwGetKey(activeWin, GLFW_KEY_D) == GLFW_PRESS)
		{
			int val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 1, 1))
					val = true;
			}
			if (!val)
			{
				Fly(1, ratio);
				isMove = true;
			}
			else
			{
				val = false;
				for (int i = 0; i < numChunks; i++)
				{
					if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 1, 1))
						val = true;
				}
				if (!val)
				{
					Fly(1, 4);
					isMove = true;
				}

			}

			iterateWalkAnimation();
			iterateArmSwingAnimation();
		}
		else if (stance == true)
		{
			iterateReturnToStance();
		}

	
}





//1 = right, 2 = up, 3 = left, 4 = down
bool Human::pollForFlyInput(Chunk **nearChunks, int numChunks, GLFWwindow *activeWindowPointer)
{
	float ratio = 1;
	bool isMove = false;

	if (glfwGetKey(activeWindowPointer, GLFW_KEY_W) == GLFW_PRESS)
	{
		int val = false;
		for (int i = 0; i < numChunks; i++)
		{
			if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 2, 1))
				val = true;
		}
		if (!val)
		{
			Fly(2, ratio);
			isMove = true;
		}
		else
		{
			val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 2, 1))
					val = true;
			}
			if (!val)
			{
				Fly(2, 4);
				isMove = true;
			}

		}
		
	}
	if (glfwGetKey(activeWindowPointer, GLFW_KEY_A) == GLFW_PRESS)
	{
		int val = false;
		for (int i = 0; i < numChunks; i++)
		{
			if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 3, 1))
				val = true;
		}
		if (!val)
		{
			Fly(3, ratio);
			isMove = true;
		}
		else
		{
			val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 3, 1))
					val = true;
			}
			if (!val)
			{
				Fly(3, 4);
				isMove = true;
			}

		}
	}
	if (glfwGetKey(activeWindowPointer, GLFW_KEY_S) == GLFW_PRESS)
	{
		int val = false;
		for (int i = 0; i < numChunks; i++)
		{
			if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 4, 1))
				val = true;
		}
		if (!val)
		{
			Fly(4, ratio);
			isMove = true;
		}
		else
		{
			val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 4, 1))
					val = true;
			}
			if (!val)
			{
				Fly(4, 4);
				isMove = true;
			}

		}

	}
	if (glfwGetKey(activeWindowPointer, GLFW_KEY_D) == GLFW_PRESS)
	{
		int val = false;
		for (int i = 0; i < numChunks; i++)
		{
			if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed(), 1, 1))
				val = true;
		}
		if (!val)
		{
			Fly(1, ratio);
			isMove = true;
		}
		else
		{
			val = false;
			for (int i = 0; i < numChunks; i++)
			{
				if (nearChunks[i]->willBeTouchingChunk(getHitboxes(), getNumHitboxes(), getSpeed() / 4, 1, 1))
					val = true;
			}
			if (!val)
			{
				Fly(1, 4);
				isMove = true;
			}

		}
	}


	return isMove;
}

void Human::iterateWalkAnimation()
{
	float l1[2];
	float l2[2];

	float rcomp1[2];
	float rcomp2[2];

	float rcomp11[2];
	float rcomp22[2];

	static int i;

	float rpoint = size / 8;

	static bool l1Last = false, l2Last = true;

	i++;

	//save the origins
	leg[0].getOrigin(l1);
	leg[1].getOrigin(l2);

	//move to screen origin for rotation
	leg[0].MoveToOrigin();
	leg[1].MoveToOrigin();

	leg[0].Translate(rpoint, 0);
	leg[1].Translate(rpoint, 0);
	

	leg[0].getOrigin(rcomp1);
	leg[1].getOrigin(rcomp2);

	if (l1Last == false)
	{
		leg[0].Swing(legSpeed);
		if (leg[0].getCurrentRotation() > legRadians)
		{
			l1Last = true;
		}
	}
	else if (l1Last == true)
	{
		leg[0].Swing(-1 * legSpeed);
		if (leg[0].getCurrentRotation() < -1 * legRadians)
		{
			l1Last = false;
		}
	}

	if (l2Last == false)
	{
		leg[1].Swing(legSpeed);
		if (leg[1].getCurrentRotation() > legRadians)
		{
			l2Last = true;
		}
	}
	else if (l2Last == true)
	{
		leg[1].Swing(-1 * legSpeed);
		if (leg[1].getCurrentRotation() < -1 * legRadians)
		{
			l2Last = false;
		}
	}

	leg[0].getOrigin(rcomp11);
	leg[1].getOrigin(rcomp22);

	leg[0].Translate(rcomp1[0] - rcomp11[0], rcomp1[1] - rcomp11[1]);
	leg[1].Translate(rcomp2[0] - rcomp22[0], rcomp22[1] - rcomp22[1]);


	leg[0].Translate(-1 * rpoint, 0);
	leg[1].Translate(-1 * rpoint, 0);

	leg[0].Translate(l1[0], l1[1]);
	leg[1].Translate(l2[0], l2[1]);
}

void Human::iterateArmSwingAnimation()
{
	float l1[2];
	float l2[2];

	float rcomp1[2];
	float rcomp2[2];

	float rcomp11[2];
	float rcomp22[2];

	static int i;

	float rpoint = size / 8;

	static bool l1Last = false, l2Last = true;

	i++;

	//save the origins
	arm[0].getOrigin(l1);
	arm[1].getOrigin(l2);

	//move to screen origin for rotation
	arm[0].MoveToOrigin();
	arm[1].MoveToOrigin();

	arm[0].Translate(rpoint, 0);
	arm[1].Translate(rpoint, 0);


	arm[0].getOrigin(rcomp1);
	arm[1].getOrigin(rcomp2);

	if (l1Last == false)
	{
		arm[0].Swing(armSpeed);
		if (arm[0].getCurrentRotation() > armRadians)
		{
			l1Last = true;
		}
	}
	else if (l1Last == true)
	{
		arm[0].Swing(-1 * armSpeed);
		if (arm[0].getCurrentRotation() < -1 * armRadians)
		{
			l1Last = false;
		}
	}

	if (l2Last == false)
	{
		arm[1].Swing(armSpeed);
		if (arm[1].getCurrentRotation() > armRadians)
		{
			l2Last = true;
		}
	}
	else if (l2Last == true)
	{
		arm[1].Swing(-1 * armSpeed);
		if (arm[1].getCurrentRotation() < -1 * armRadians)
		{
			l2Last = false;
		}
	}

	arm[0].getOrigin(rcomp11);
	arm[1].getOrigin(rcomp22);

	arm[0].Translate(rcomp1[0] - rcomp11[0], rcomp1[1] - rcomp11[1]);
	arm[1].Translate(rcomp2[0] - rcomp22[0], rcomp22[1] - rcomp22[1]);


	arm[0].Translate(-1 * rpoint, 0);
	arm[1].Translate(-1 * rpoint, 0);

	arm[0].Translate(l1[0], l1[1]);
	arm[1].Translate(l2[0], l2[1]);
}

void Human::iterateReturnToStance()
{
	float l1[2];
	float l2[2];

	float rcomp1[2];
	float rcomp2[2];

	float rcomp11[2];
	float rcomp22[2];

	float rpoint = size / 8;

	//save the origins
	leg[0].getOrigin(l1);
	leg[1].getOrigin(l2);

	//move to screen origin for rotation
	leg[0].MoveToOrigin();
	leg[1].MoveToOrigin();

	leg[0].Translate(rpoint, 0);
	leg[1].Translate(rpoint, 0);


	leg[0].getOrigin(rcomp1);
	leg[1].getOrigin(rcomp2);

	if (leg[0].getCurrentRotation() < (-1 * legRadians / 10))
	{
		leg[0].Swing(legSpeed);
	}
	else if (leg[0].getCurrentRotation() > (legRadians / 10))
	{
		leg[0].Swing(-1 * legSpeed);
	}


	if (leg[1].getCurrentRotation() < (-1 * legRadians / 10))
	{
		leg[1].Swing(legSpeed);
	}
	else if (leg[1].getCurrentRotation() > (legRadians / 10))
	{
		leg[1].Swing(-1 * legSpeed);
	}


	leg[0].getOrigin(rcomp11);
	leg[1].getOrigin(rcomp22);

	leg[0].Translate(rcomp1[0] - rcomp11[0], rcomp1[1] - rcomp11[1]);
	leg[1].Translate(rcomp2[0] - rcomp22[0], rcomp22[1] - rcomp22[1]);


	leg[0].Translate(-1 * rpoint, 0);
	leg[1].Translate(-1 * rpoint, 0);

	leg[0].Translate(l1[0], l1[1]);
	leg[1].Translate(l2[0], l2[1]);

	//

	for (int i = 0; i < 2; i++)
	{
		l1[i] = 0.0f;
		l2[i] = 0.0f;
		rcomp1[i] = 0.0f;
		rcomp2[i] = 0.0f;
		rcomp11[i] = 0.0f;
		rcomp22[i] = 0.0f;
	}

	//save the origins
	arm[0].getOrigin(l1);
	arm[1].getOrigin(l2);

	//move to screen origin for rotation
	arm[0].MoveToOrigin();
	arm[1].MoveToOrigin();

	arm[0].Translate(rpoint, 0);
	arm[1].Translate(rpoint, 0);


	arm[0].getOrigin(rcomp1);
	arm[1].getOrigin(rcomp2);

	if (arm[0].getCurrentRotation() < (-1 * armRadians / 10))
	{
		arm[0].Swing(armSpeed);
	}
	else if (arm[0].getCurrentRotation() > (armRadians / 10))
	{
		arm[0].Swing(-1 * armSpeed);
	}


	if (arm[1].getCurrentRotation() <  (-1 * armRadians / 10))
	{
		arm[1].Swing(armSpeed);
	}
	else if (arm[1].getCurrentRotation() > (armRadians / 10))
	{
		arm[1].Swing(-1 * armSpeed);
	}


	arm[0].getOrigin(rcomp11);
	arm[1].getOrigin(rcomp22);

	arm[0].Translate(rcomp1[0] - rcomp11[0], rcomp1[1] - rcomp11[1]);
	arm[1].Translate(rcomp2[0] - rcomp22[0], rcomp22[1] - rcomp22[1]);


	arm[0].Translate(-1 * rpoint, 0);
	arm[1].Translate(-1 * rpoint, 0);

	arm[0].Translate(l1[0], l1[1]);
	arm[1].Translate(l2[0], l2[1]);
}


bool Human::pollForFurthestDistance(float distance)
{
	static int factor = 1;

	if (getGameX() > factor * distance)
	{
		factor += 1;
		return true;
	}
	else if (getGameX() < factor * distance * -1)
	{
		factor += 1;
		return true;
	}
	else
	{
		return false;
	}

}
