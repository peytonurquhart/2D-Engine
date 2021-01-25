#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

void Round(float buff, float *n);


/* Triangle Shape */

/*
- Must specify 3 sides of a triangle which will be drawn with relative angles

- Impossible triangles result in undefined behavior

- Side + Angle letters:

       A
	    
		|\
		| \
	c	|  \  b
	        |   \
		|    \
		|     \
	B	```````   C
		   a

	Warning:

- sin() and cos() decimal truncation issue fixed

*/



class Triangle : public Shape
{
public:
	Triangle() { return; }

	/* Instatiates a triangle with side lengths a b and c, impossible triangles result in undefined behavior */
	Triangle(float a, float b, float c);

	void Init(float a, float b, float c);

	/* Returns each side length*/
	float getSidea() { if (getIsAlloced()) { return a; } return 0.0f; }
	float getSideb() { if (getIsAlloced()) { return b; } return 0.0f; }
	float getSidec() { if (getIsAlloced()) { return c; } return 0.0f; }

	/* Returns the angle of each vertex in radians */
	float getAngleA();
	float getAngleB();
	float getAngleC();

	/* Returns the shapes current offset from its origin*/
	float getCurrentRotation() { return this->currentRotation; }

	/* Calculates the midpoint of the triangle nesecarry for trig operations and rotations */
	void CalcMidPoint(float mids[2]);

	/* Translates the specified vertex given amounts x and y while keeping other verticies intact, impossible translations result in undefined behavior */
	void EditVertex(unsigned int vertex, float xOffset, float yOffset);

	/* Translates the triangle by the given amounts x and y */
	void Translate(float xAmount, float yAmount);

	/* Multiplies the triangle by the given factor */
	void Resize(float factor);

	/* Rotates a single vertex about the origin (weird behavior) */
	/* Warning: Invalidates angle member data! */
	void RotateVertex(int vertex, float theta);

	/* Translates the shape to have a midpoint of 0*/
	void TranslateToOrigin();

	/* Swings the shape around the origin theta radians */
	void Swing(float theta);

	/* Rotates the shape around its midpoint */
	void Rotate(float theta);

	/* Rotates the shape around its midpoint and does not update it current rotation (for spawning) */
	void FreeRotate(float theta);

	/* Swings the shape and does not update it current rotation (for spawning) */
	void FreeSwing(float theta);

	/* Helper Functions*/

	/* Return the angles of each vertex in degrees */
	float getAngleA_D();
	float getAngleB_D();
	float getAngleC_D();

	/* Prints all side lengths and angles*/
	void printSidesAngles();

	/* Indirectly returns the coordinates of the specified vertex*/
	void getVertex(int vertex, float vert[2]);

	void setCurRotation(float theta) { this->currentRotation = theta; }

private:
	float *newMatrix;

	float a;
	float b;
	float c;

	float A;
	float B;
	float C;

	float currentRotation;
};



class TriangleT : public Shape
{
public:
	TriangleT() { return; }

	/* Instatiates a triangle with side lengths a b and c, impossible triangles result in undefined behavior */
	TriangleT(float a, float b, float c);

	void Init(float a, float b, float c);

	/* Returns each side length*/
	float getSidea() { if (getIsAlloced()) { return a; } return 0.0f; }
	float getSideb() { if (getIsAlloced()) { return b; } return 0.0f; }
	float getSidec() { if (getIsAlloced()) { return c; } return 0.0f; }

	/* Returns the angle of each vertex in radians */
	float getAngleA();
	float getAngleB();
	float getAngleC();

	/* Returns the shapes current offset from its origin*/
	float getCurrentRotation() { return this->currentRotation; }

	/* Calculates the midpoint of the triangle nesecarry for trig operations and rotations */
	void CalcMidPoint(float mids[2]);

	/* Translates the specified vertex given amounts x and y while keeping other verticies intact, impossible translations result in undefined behavior */
	void EditVertex(unsigned int vertex, float xOffset, float yOffset);

	/* Translates the triangle by the given amounts x and y */
	void Translate(float xAmount, float yAmount);

	/* Multiplies the triangle by the given factor */
	void Resize(float factor);

	/* Rotates a single vertex about the origin (weird behavior) */
	/* Warning: Invalidates angle member data! */
	void RotateVertex(int vertex, float theta);

	/* Translates the shape to have a midpoint of 0*/
	void TranslateToOrigin();

	/* Swings the shape around the origin theta radians */
	void Swing(float theta);

	/* Rotates the shape around its midpoint */
	void Rotate(float theta);

	/* Rotates the shape around its midpoint and does not update it current rotation (for spawning) */
	void FreeRotate(float theta);

	/* Swings the shape and does not update it current rotation (for spawning) */
	void FreeSwing(float theta);

	/* Helper Functions*/

	/* Return the angles of each vertex in degrees */
	float getAngleA_D();
	float getAngleB_D();
	float getAngleC_D();


	/* Indirectly returns the coordinates of the specified vertex*/
	void getVertex(int vertex, float vert[2]);

	void setCurRotation(float theta) { this->currentRotation = theta; }

	void Bind();

private:
	float *newMatrix;

	float a;
	float b;
	float c;

	float A;
	float B;
	float C;

	float currentRotation;
};
