#ifndef _MATHLIB_H_
#define _MATHLIB_H_

#define PI 3.14159265358
#define RAD_TO_DEG 57.29577951308
#define DEG_TO_RAD 0.01745329251

#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

enum VectorTypes {
	TYPE_NONSOLID = 0,
	TYPE_SEMISOLID = 1,
	TYPE_SOLID = 2
};

enum Modes {
	MODE_DOWN = 0,
	MODE_LEFT = 90,
	MODE_UP = 180,
	MODE_RIGHT = 270
};

// Useful mathematical functions

int sign(double x);
int sign(int x);
double clamp(double x, double minvalue, double maxvalue);

// Point struct

typedef struct point{
	float x;
	float y;
} Point;

// Vector class

class Vector;

class Vector {
public:
	double x1, y1; // Starting position of vector
	double x2, y2; // Ending point of vector

private:
	double angle; // Stores the angle at which the vector points
	int type; // Stores the solidity type of the vector (for terrain collisions)
	
public:
	Vector();
	Vector(double x1, double y1, double x2, double y2);
	Vector(double x1, double y1, double x2, double y2, int type);
	double getAngle(); // 0 is straight forward, 90 is down, etc
	double getInwardNormal(); // Gives vector pointing inside a platform.
	int getType();
	double getLength();
	double getLengthX();
	double getLengthY();
	void setType(int type);
	void setVector(double x1, double y1, double x2, double y2);
	bool intersects(Vector other);
	Point getIntersectionPoint(Vector other);
	double getIntersectionTValue(Vector other); // Gives value between 0 and 1 if there is a collision
	                                            // and -1 if there is no collision
};

#endif