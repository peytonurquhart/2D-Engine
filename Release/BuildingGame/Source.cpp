#include "Init.h"
#include "Block.h"
#include "Chunk.h"
#include "Human.h"

void TranslateCursorPos(float pos[2], float height, float width)
{
	float xpix = width - (width * 0.5f);
	float ypix = height - (height * 0.5f);

	pos[0] = (pos[0] - xpix) / xpix;
	pos[1] = (pos[1] - ypix) / ypix * -1;

}

int main(void)
{

	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(1920, "Engine");


	if (window.validateWindow() == false)
	{
		glfwTerminate();
		return 0;
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
		return -1;
	}



	/* Sound Engine */
	ISoundEngine* Sengine = createIrrKlangDevice();
	system("cls");





	Texture head1("Shading/texture.shader", "BuildingGame/Png/Character/Head1.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	head1.Create("u_Texture");
	head1.Use();
	head1.UpdateUniform();
	head1.unBind();

	Texture torso1("Shading/texture.shader", "BuildingGame/Png/Character/Torso1.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	torso1.Create("u_Texture");
	torso1.Use();
	torso1.UpdateUniform();
	torso1.unBind();

	Texture arm1("Shading/texture.shader", "BuildingGame/Png/Character/Arm1.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	arm1.Create("u_Texture");
	arm1.Use();
	arm1.UpdateUniform();
	arm1.unBind();

	Texture leg1("Shading/texture.shader", "BuildingGame/Png/Character/Leg1.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	leg1.Create("u_Texture");
	leg1.Use();
	leg1.UpdateUniform();
	leg1.unBind();

	Human steve(0.01f, 0.04f, &head1, &torso1, &arm1, &leg1);
	steve.Translate(0, 0.3);



	/*Backround compilation*/
	Shader sky("Shading/basic.shader", fourF, 0);
	sky.Create("u_Color");
	sky.setRgb(0.3, 0.1, 0.8);
	sky.Use();
	sky.UpdateUniform();
	sky.unBind();

	Shader hbtemp("Shading/basic.shader", fourF, 0);
	hbtemp.Create("u_Color");
	hbtemp.setRgb(0.95, 0.0, 0.0);
	hbtemp.Use();
	hbtemp.UpdateUniform();
	hbtemp.unBind();

	Rectangle backround;
	backround.Init(5, 5);


	/* Texture Shader Compilation */
	Texture ttest("Shading/texture.shader", "BuildingGame/Png/Blocks/GrassBlock.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	ttest.Create("u_Texture");
	ttest.Use();
	ttest.UpdateUniform();
	ttest.unBind();


	Texture stoneTex("Shading/texture.shader", "BuildingGame/Png/Blocks/StoneBlock.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	stoneTex.Create("u_Texture");
	stoneTex.Use();
	stoneTex.UpdateUniform();
	stoneTex.unBind();


	Texture woodTex("Shading/texture.shader", "BuildingGame/Png/Blocks/WoodBlock.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	woodTex.Create("u_Texture");
	woodTex.Use();
	woodTex.UpdateUniform();
	woodTex.unBind();

	Texture leafTex("Shading/texture.shader", "BuildingGame/Png/Blocks/LeafBlock.png", true, GL_TEXTURE0, GL_NEAREST, GL_REPEAT);
	leafTex.Create("u_Texture");
	leafTex.Use();
	leafTex.UpdateUniform();
	leafTex.unBind();

	Block *b1 = nullptr;
	Block *t = nullptr;

	Block stack[1000];
	int stackIndex = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack[i].Init(woodBlock, &woodTex, 0.08, 1, 10, false);
	}

	Block stack2[1000];
	int stack2Index = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack2[i].Init(leafBlock, &leafTex, 0.08, 1, 10, false);
	}



	Chunk scene[16];

	int sceneSize = 16;





	/*create chunk matrix*/
	for (int i = 0, chunksx = -2 ,chunksy = 1; i < sceneSize; i++, chunksx++)
	{
		if (i % (int)sqrt(sceneSize) == 0)
		{
			chunksx = -2;
			chunksy -= 1;
		}

		if (i >= (sceneSize / 2))
		{
			if(i == 8)
			scene[i].Init(10, grassBlock, &ttest, 0.08, 1);
			else
			scene[i].Init(10, stoneBlock, &stoneTex, 0.08, 1);
		}
		else
		{
			scene[i].Init("nullchunk", 10, 0.08, 1);
		}

		scene[i].TranslateChunkSize(chunksx, chunksy);

		scene[i].Translate(0.1, 0.5);
	}





	double xp, yp;
	float tpos[2];
	bool r = true;

	t = scene[8].UnAttachBlock(9, 9);

	int i = 0;







	double previousTime = glfwGetTime();
	int frameCount = 0;

	while (!glfwWindowShouldClose(window.get()))
	{







		//FPS COUNTER---------------------
		double currentTime = glfwGetTime();
		frameCount++;
		// If a second has passed.
		if (currentTime - previousTime >= 1.0)
		{
			// Display the frame count here any way you want.
			cout << frameCount << endl;

			frameCount = 0;
			previousTime = currentTime;
		}
		//FPS COUNTER---------------------













		i++;

		/* Render here */
		window.Clear();



		/*Draw the background*/
		sky.Use();

		backround.Bind();
		backround.BufferVertex();
		backround.Draw();
		backround.Unbind();

		sky.unBind();



		/* Draw all chunks in the scene*/
		for (int i = 0; i < 16; i++)
		{
			scene[i].Draw();
		}

		/*get cursor position in pixels*/
		glfwGetCursorPos(window.get(), &xp, &yp);

		tpos[0] = xp;
		tpos[1] = yp;

		/* translates the cursor positon to a 1 grid x/y coordinate*/
		TranslateCursorPos(tpos, window.getHeight(), window.getWidth());


		//checks for a press and pushes a block from the block stack to one of the chunks
		if (glfwGetKey(window.get(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			for (int i = 0; i < 16; i++)
			{
				if (scene[i].isPointInChunk(tpos) && stackIndex < 1000)
				{
					if (scene[i].AttachBlock(&stack[stackIndex], tpos) == true)
					{
						stackIndex++;
					}
				}
			}

		}


		if (glfwGetKey(window.get(), GLFW_KEY_L) == GLFW_PRESS)
		{
			for (int i = 0; i < 16; i++)
			{
				if (scene[i].isPointInChunk(tpos) && stack2Index < 1000)
				{
					if (scene[i].AttachBlock(&stack2[stack2Index], tpos) == true)
					{
						stack2Index++;
					}
				}
			}

		}

		/* not working */
			

		float ratio = 1;
			if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
			{
				int val = false;
				for (int i = 0; i < sceneSize; i++)
				{
					if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed(), "up", 1))
						val = true;
				}
				if (!val)
				{
					steve.Fly("up", ratio);
				}
				else
				{
					val = false;
					for (int i = 0; i < sceneSize; i++)
					{
						if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed() / 4, "up", 1))
							val = true;
					}
					if (!val)
					{
						steve.Fly("up", 4);
					}

				}



			}
			if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
			{

				int val = false;
				for (int i = 0; i < sceneSize; i++)
				{
					if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed(), "left", 1))
						val = true;
				}
				if (!val)
				{
					steve.Fly("left", 1);
				}
				else
				{
					val = false;
					for (int i = 0; i < sceneSize; i++)
					{
						if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed() / 4, "left", 1))
							val = true;
					}
					if (!val)
					{
						steve.Fly("left", 4);
					}

				}

			}
			if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
			{
				int val = false;
				for (int i = 0; i < sceneSize; i++)
				{
					if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed(), "down", 1))
						val = true;
				}
				if (!val)
				{
					steve.Fly("down", ratio);
				}
				else
				{
					val = false;
					for (int i = 0; i < sceneSize; i++)
					{
						if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed() / 4, "down", 1))
							val = true;
					}
					if (!val)
					{
						steve.Fly("down", 4);
					}

				}

			}
			if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
			{
				int val = false;
				for (int i = 0; i < sceneSize; i++)
				{
					if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed(), "right", 1))
						val = true;
				}
				if (!val)
				{
					steve.Fly("right", 1);
				}
				else
				{
					val = false;
					for (int i = 0; i < sceneSize; i++)
					{
						if (scene[i].willBeTouchingChunk(steve.getHitboxes(), steve.getNumHitboxes(), steve.getSpeed() / 4, "right", 1))
							val = true;
					}
					if (!val)
					{
						steve.Fly("right", 4);
					}

				}
			}




		/* draw character hitboxes*/
		steve.DrawFrontProfile();

		steve.DrawHitBoxes(&hbtemp);

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */

		glfwPollEvents();
	}





	glfwTerminate();



	return 0;
}

/*
	TO DO:


	- Complete all deep copy contructors on the Engine

	- Change single to double index transferring to the pattern you can see in the console
*/