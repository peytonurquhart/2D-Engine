#include "Init.h"
#include "Block.h"
#include "Chunk.h"
#include "Human.h"
#include "List.h"
#include "Tests.h"
#include "BatchRenderer.h"
#include "GameWorld.h"

void TranslateCursorPos(float pos[2], float height, float width)
{
	float xpix = width - (width * 0.5f);
	float ypix = height - (height * 0.5f);

	pos[0] = (pos[0] - xpix) / xpix;
	pos[1] = (pos[1] - ypix) / ypix * -1;

}

int main(void)
{

	string chunkDirectory;
	chunkDirectory = "C:/Users/Peyton/Documents/Visual Studio 2015/Projects/openGl/2D Engine/Release/ChunkData";


	/* Initialize the window */

	if (!glfwInit())
		return -1;

	gameWindow window;

	window.Create(2600, "Engine");


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
	steve.Translate(0, 1.2);



	/*Backround compilation*/
	Shader sky("Shading/basic.shader", fourF, 0);
	sky.Create("u_Color");
	sky.setRgb(0.171, 0.092, 0.219);
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



	int numTex = 4;
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

	Texture *texArray[MAXBLOCKTEXTURES];

	texArray[0] = &ttest;
	texArray[1] = &stoneTex;
	texArray[2] = &woodTex;
	texArray[3] = &leafTex;

	blockType typeArray[4] = { grassBlock, stoneBlock, woodBlock, leafBlock };










	Chunk **scene = nullptr;
	int numS = 0;


	GameWorld world(3, 0.08, 10, texArray, 4, typeArray, "flatworld", 4, 0.7, 0.8, &steve, chunkDirectory, 1.5f);



	Block stack[1000];
	int stackIndex = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack[i].Init(stoneBlock, &stoneTex, 0.08, 1, 10, false);
	}

	Block stack2[1000];
	int stack2Index = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack2[i].Init(leafBlock, &leafTex, 0.08, 1, 10, false);
	}

	Block stack3[1000];
	int stack3Index = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack3[i].Init(grassBlock, &ttest, 0.08, 1, 10, false);
	}

	Block stack4[1000];
	int stack4Index = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack4[i].Init(woodBlock, &woodTex, 0.08, 1, 10, false);
	}








	double xp, yp;
	float tpos[2];
	bool r = true;



	int i = 0;

	double previousTime = glfwGetTime();
	int frameCount = 0;

	Renderer renderer(4, typeArray, texArray);
	
	

	while (!glfwWindowShouldClose(window.get()))
	{




		//FPS COUNTER---------------------
		double currentTime = glfwGetTime();

		frameCount++;

		if (currentTime - previousTime >= 1.0)
		{
			system("cls");
			cout << "fps: " << frameCount << endl;
			cout << "chunks rendering: " << numS << endl;

			frameCount = 0;
			previousTime = currentTime;
		}
		//FPS COUNTER---------------------





		/* Loop counter */
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


		/*get cursor position in pixels*/
		glfwGetCursorPos(window.get(), &xp, &yp);

		tpos[0] = xp;
		tpos[1] = yp;

		/* translates the cursor positon to a 1 grid x/y coordinate*/
		TranslateCursorPos(tpos, window.getHeight(), window.getWidth());






		/* generate which chunks should be drawn and polled in the scene*/
		scene = world.getScene();
		numS = world.getNumS();

		if(i % 30 == 0)
		cout << numS << endl;










		//checks for a press and pushes a block from the block stack to one of the chunks
		if (glfwGetKey(window.get(), GLFW_KEY_K) == GLFW_PRESS)
		{
			for (int i = 0; i < numS; i++)
			{
				if (scene[i]->isPointInChunk(tpos) && stackIndex < 1000)
				{
					if (scene[i]->AttachBlock(&stack[stackIndex], tpos) == true)
					{
						stackIndex++;
					}
				}
			}

		}

		if (glfwGetKey(window.get(), GLFW_KEY_L) == GLFW_PRESS)
		{
			for (int i = 0; i < numS; i++)
			{
				if (scene[i]->isPointInChunk(tpos) && stack2Index < 1000)
				{
					if (scene[i]->AttachBlock(&stack2[stack2Index], tpos) == true)
					{
						stack2Index++;
					}
				}
			}

		}

		if (glfwGetKey(window.get(), GLFW_KEY_J) == GLFW_PRESS)
		{
			for (int i = 0; i < numS; i++)
			{
				if (scene[i]->isPointInChunk(tpos) && stack3Index < 1000)
				{
					if (scene[i]->AttachBlock(&stack3[stack3Index], tpos) == true)
					{
						stack3Index++;
					}
				}
			}

		}

		if (glfwGetKey(window.get(), GLFW_KEY_H) == GLFW_PRESS)
		{
			for (int i = 0; i < numS; i++)
			{
				if (scene[i]->isPointInChunk(tpos) && stack4Index < 1000)
				{
					if (scene[i]->AttachBlock(&stack4[stack4Index], tpos) == true)
					{
						stack4Index++;
					}
				}
			}

		}

		//at this point scene is the limit of what is rendering and updating in the world, It has been narrowed down to 16 - 24 chunks which is managable





		//poll for collision with an array of chunk pointers
		steve.pollForInput(1, scene, numS, window.get());




		/*must batch the objects after steve polls for input for completely weird and unknown reasons*/
		renderer.PushAll(scene, numS);
		renderer.DrawAll();
		renderer.FlushAll();





		world.QueueTranslations();


		/* generate chunks if steve moves to a position with no allocated chunks*/

		world.generateNewChunks();








		GLenum error = 1;

		while (error != GL_NO_ERROR)
		{
			error = glGetError();
			if (error == GL_OUT_OF_MEMORY)
			{
				cout << "out of memory" << endl;
			}
		}





		/* draw character hitboxes*/
		steve.DrawFrontProfile();

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

	QUESTION: How do you go about camera movement without translating every single object?
	ANSWER: A Queue

	IDEA: Have just three different depths, all represented by the same block with different light exposure. depth +1 the player walks behing, depth 0 the player hits, depth -1 the player walks in front. Key switch, Interesting Gameplay

	World generation and saved games are soon!



	0.) remove individual block buffers

	1.) Clean up chunk lists

*/

