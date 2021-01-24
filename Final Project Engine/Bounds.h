#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <math.h>

enum Boundlimit { Unbound, Lower, Right, Upper, Left };

/*
		Bounds Class

	- A Closed enviornment which can check if a hitbox object or hitbox array has left it

	- Compares if objects have left in one step if shouldVerify is false and is usually accurate but if it is important on which axis the object has left then shouldVerify should be true

	- Checking functions return an enumerated bound limit, or Unbound (0)

*/

/*consider reworking this idea all together*/

class Bounds
{
public:
	Bounds() { return; }

	/* Constructs game bounds in Plus of Minus zone (zonepm) about a (0,0) point on the plane*/
	Bounds(float zonePM, bool shouldVerify, float bounceAmt);
	void Init(float zonePM, bool shouldVerify, float bounceAmt);

	/*Returns the boundlimit of the given hitBox referece (unbounds if its inbounds)*/
	Boundlimit isInBounds(Hitbox &h);

	/*returns the boundlimit of the given hitArray (unbounds if the whole array is inbounds)*/
	Boundlimit isInBounds(HitArray16 &hA);

	/*gets the quadrant of a given point*/
	int getQuadrant(float * x, float  * y);

	/* Bounce simply makes sure that things cant escape the corners by "going in the exact center" call after isinbounds with the returned limit*/
	void Bounce(Boundlimit lim, Hitbox &h, bool isAttached, Shape *s = nullptr);

	void Bounce(Boundlimit lim, HitArray16 &h, bool isAttached, Shape *s = nullptr);

private:

	Hitbox bounds[4];

	bool verify;

	float bounceAmt;

};