#include "Init.h"
#include "BuildingGame\Block.h"
#include "BuildingGame\Chunk.h"
#include "Human.h"
#include "List.h"
#include "Tests.h"

void Tests::BatchTest()
{
	string chunkDirectory;
	chunkDirectory = "C:/Users/Peyton/Documents/Visual Studio 2015/Projects/openGl/2D Engine/Release/ChunkData";


	/* Initialize the window */

	if (!glfwInit())
		cout << "glfwinit() failure" << endl;

	gameWindow window;

	window.Create(1920, "Engine");


	if (window.validateWindow() == false)
	{
		glfwTerminate();
	}

	window.makeCoreProfile(3, 3);

	window.makeCurrentContext();

	window.vSync(true);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Error" << std::endl;
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


















	Block stack[1000];
	int stackIndex = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack[i].Init(woodBlock, &woodTex, 0.12, 1, 10, false);
	}

	Block stack2[1000];
	int stack2Index = 0;

	for (int i = 0; i < 1000; i++)
	{
		stack2[i].Init(leafBlock, &leafTex, 0.12, 1, 10, false);
	}


	/*chunk pointer for the scene*/
	Chunk *scene[3];
	int numS = 1;



	Chunk *bTest = new Chunk;

	bTest->Init("nullchunk", 10, 0.08, 1);

	bTest->Translate(-0.5, -0.5);

	scene[0] = bTest;



	float mesh[3200];
	unsigned int indeces[600];

	/*get the block from the chunk*/
	Block *blx = bTest->getBlocks();
	float *mtx = nullptr;
	unsigned int *ind = nullptr;

	int numFloats = 0, numIndeces = 0;
	


	int k = 0;
	int g = 0;

	for (int i = 0; i < 100; i++)
	{

		mtx = blx[i].getMatrix();
		ind = blx[i].getIndeces();
		numFloats = blx[i].getNumFloats();
		numIndeces = blx[i].getNumIndeces();
		for (int j = 0; j < numFloats; j++, k++)
		{
			//push all vertices
			mesh[k] = mtx[j];
		}
		for (int j = 0; j < numIndeces; j++, g++)
		{
			indeces[g] = ind[j] + (i * 4);
		}
	}





	Shape largeShape;

	largeShape.ReInit(400, 2, sizeof(float), 3200, mesh, true, 600, indeces, 8, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, 2);

	largeShape.Bind();
	glVertexAttribPointer(largeShape.getVaPointerIndex(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(largeShape.getVaPointerIndex());



	largeShape.DispAllAttributes();







	float tpos[2];
	bool r = true;
	double xp, yp;


	int i = 0;

	double previousTime = glfwGetTime();
	int frameCount = 0;


	while (!glfwWindowShouldClose(window.get()))
	{




		////FPS COUNTER---------------------
		//double currentTime = glfwGetTime();

		//frameCount++;

		//if (currentTime - previousTime >= 1.0)
		//{
		//	system("cls");
		//	cout << "fps: " << frameCount << endl;
		//	cout << "chunks rendering: " << numS << endl;
		//	cout << "per strip - ";
		//	n1lvl.printCurrentNumTranslationsMade();

		//	frameCount = 0;
		//	previousTime = currentTime;
		//}
		////FPS COUNTER---------------------





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

		//at this point scene is the limit of what is rendering and updating in the world, It has been narrowed down to 16 - 24 chunks which is managable









		//poll for collision with an array of chunk pointers
		steve.pollForInput(2, scene, numS, window.get());

		leafTex.Use();

		largeShape.Bind();
		glVertexAttribPointer(largeShape.getVaPointerIndex(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(largeShape.getVaPointerIndex());

		largeShape.BufferVertex();

		largeShape.Draw();






		/* draw character hitboxes*/
		steve.DrawFrontProfile();

		/* Swap front and back buffers */
		glfwSwapBuffers(window.get());

		/* Poll for and process events */
		glfwPollEvents();
	}





	glfwTerminate();

}

/*
	Batch Rendering

	- Objects should be sorted by Texture

	- Each Renderer Object will be for a specific texture

	- Each Renderer will take the current updateArray as a paramater as well as what texture to batch

	- Shapes will be created from the update array, pushed to the gpu, drawn, and maybe flushed

*/
