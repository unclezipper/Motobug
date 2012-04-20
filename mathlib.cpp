#include "mathlib.h"

int sign(double x) {
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int sign(int x) {
	return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

double clamp(double x, double minvalue, double maxvalue) {
	return x-((maxvalue-minvalue)*floor((x-minvalue)/(maxvalue-minvalue)));
}

Vector::Vector() {}

Vector::Vector(double x1, double y1, double x2, double y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	if (x1==x2 && y1==y2) {
		angle = 0;
	} else {
		angle = (double)(atan2((double)(y2-y1), (double)(x2-x1)) * RAD_TO_DEG);
	}
	type = TYPE_SOLID;
}

Vector::Vector(double x1, double y1, double x2, double y2, int type) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	if (x1==x2 && y1==y2) {
		angle = 0;
	} else {
		angle = (double)(atan2((double)(y2-y1), (double)(x2-x1)) * RAD_TO_DEG);
	}
	this->type = type;
}

double Vector::getAngle() {
	return angle;
}

double Vector::getInwardNormal() {
	return clamp(angle+90, 0, 360);
}

int Vector::getType() {
	return type;
}

double Vector::getLength() {
	return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

double Vector::getLengthX() {
	return x2-x1;
}

double Vector::getLengthY() {
	return y2-y1;
}
	
void Vector::setType(int type) {
	this->type = type;
}

void Vector::setVector(double x1, double y1, double x2, double y2) {
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	if (x1==x2 && y1==y2) {
		angle = 0;
	} else {
		angle = (double)(atan2((double)(y2-y1), (double)(x2-x1)) * RAD_TO_DEG);
	}
}

bool Vector::intersects(Vector other) {
	return (this->getIntersectionTValue(other) != -1);
}

Point Vector::getIntersectionPoint(Vector other) {
	Point p;
	p.x = -1;
	p.y = -1;
	double t = this->getIntersectionTValue(other);
	if (t != -1) {
		p.x = this->x1 + t * (this->x2 - this->x1);
		p.y = this->y1 + t * (this->y2 - this->y1);
	}
	return p;
}

double Vector::getIntersectionTValue(Vector other) {
	float tNumerSelf, tNumerOther, tDenom;
	tNumerSelf = (other.x2 - other.x1)*(this->y1 - other.y1) - (other.y2 - other.y1)*(this->x1 - other.x1);
	tNumerOther = (this->x2 - this->x1)*(this->y1 - other.y1) - (this->y2 - this->y1)*(this->x1 - other.x1);
	tDenom = (other.y2 - other.y1)*(this->x2 - this->x1) - (other.x2 - other.x1)*(this->y2 - this->y1);

	if (tDenom == 0) {
		if (tNumerSelf == 0 && tNumerOther == 0) {
			return -1; // Vectors coincide
		} else {
			return -1; // Vectors are parallel
		}
	}

	if ((tNumerSelf/tDenom >= 0 && tNumerSelf/tDenom <= 1) &&
	    (tNumerOther/tDenom >= 0 && tNumerOther/tDenom <= 1))
		return tNumerSelf/tDenom; // Vectors intersect

	return -1; // Vectors do not intersect
}
	