#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

/*
	4 by 4 Hitbox Array

	- Once a bool map has been chosen for the hitbox array It cannot be changed

	- Hit arrays and objects must be bound at their origins and then continue to follow all of the same translations and rotations

	- Hitarray[2][3] is allocated and translated no matter what because it contains midpoint data, but if it isnt specified on the bool map as true it wont register for hits
	
*/

class HitArray16
{
public:

	HitArray16() { return; }

	/* Initializes a 4 by 4 array of */
	HitArray16(float boxSize, bool newMap[4][4]);

	void Init(float boxSize, bool newMap[4][4]);

	/* returns true if the array has been generated*/
	bool getIsGenerated() { return isGenereated; }

	/* returns true if any box in the array overlaps the checkBox hitbox*/
	bool isOverlap(Hitbox &checkBox);

	/* returns true if any box in the array overlaps any box in the checkArray */
	bool isOverlap(HitArray16 &checkArray);

	/* returns the map t/f value at specified index*/
	bool indexMap(int j, int i) { return map[j][i]; }

	/*returns a pointer to the hitbox and specified index*/
	Hitbox *indexMatrix(int j, int i) { if (indexMap(j, i)) { return &matrix[j][i]; } }

	/* translates the hitarray x,y */
	void Translate(float xAmount, float yAmount);

	/* swings the hitarray theta degrees*/
	void Swing(float theta);

	/*rotates the hitarray theta degrees*/
	void Rotate(float theta);

	/*Swings without updating the hitarrays current rotation*/
	void FreeSwing(float theta);
	
	/*Rotates without updating the hitarrays current rotation*/
	void FreeRotate(float theta);

	/* translates array to its origin*/
	void TranslateToOrigin();

	/* Helper functions*/
	void DrawMap();

	/*calculates the origin of the array*/
	void CalcHitArrayMidpoint(float mids[2]);

	/*pairs a shape with an overloaded CalcMidPoint() function to the hitArray at the origin*/
	void Attach(Shape &s);

private:
	Hitbox matrix[4][4];

	float boxSize;

	bool map[4][4];

	bool isGenereated;
};
