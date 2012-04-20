#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <vector>

#include "mathlib.h"

enum CharacterStates {
	STATE_STANDING,
	STATE_WAITING,
	STATE_WALKING,
	STATE_RUNNING,
	STATE_LOOKINGUP,
	STATE_CROUCHING,
	STATE_ROLLING,
	STATE_SPINDASHING,
	STATE_JUMPING,
	STATE_FALLING,
	STATE_HURT,
	STATE_DEAD
};

enum InputButtons {
	BUTTON_UP    = 1 << 0,
	BUTTON_DOWN  = 1 << 1,
	BUTTON_LEFT  = 1 << 2,
	BUTTON_RIGHT = 1 << 3,
	BUTTON_A     = 1 << 4,
	BUTTON_B     = 1 << 5,
	BUTTON_C     = 1 << 6,
	BUTTON_START = 1 << 7
};

class Sensor{
private:
	Vector sensorVector;
	double tClosest;
	bool activated;
	double detectedAngle
	
public:
	Sensor();
	Sensor(double x1, double y1, double x2, double y2);
	bool isActivated();
	double getTClosest();
	double setTClosest(double t);
	void resetTClosest();
	void activate();
	void deactivate();
	double getDetectedAngle();
	void setDetectedAngle();
};

class Character {
public:
	static vector<Character*> CharacterList;
	
public:
	Character();
	virtual ~Character();
	
public:
	double x;
	double y;
	int width;
	int height;
	double speedGround;		// Speed parallel to ground
	double speedAir;		// Speed perpendicular to ground
	double angle;			// Angle of momentum
	
	double accel;			// Current Acceleration
	double decel;			// Current Deceleration
	double friction;		// Current Friction
	double maxSpeed;		// Current Maximum X Speed
	double gravity;			// Current Gravity
	double jumpStrength;	// Current Jump Strength
	double jumpRelease;		// Current Jump Release Strength
	double slopeFactor;		// Current Slope Factor
	double modeAngle;		// Current Mode Angle
	double gravityAngle;	// Current Gravity Angle
	
	double maxSlideAngle;	// Maximum angle at which a character must slide down a slope
	double minSwitchAngle;	// Minimum angle at which character switches modes
	
	int state;				// Current state of character.

protected:
	double speedX;			// Speed in x direction
	double speedY;			// Speed in y direction
	vector<int> inputQueue;	// Keeps track of button status
	int inputQueueLength;	// How many frames to keep track of button status for
	
public:
	// Flags
	bool grounded;			// Is character on the ground?
	bool underwater;		// Is character underwater?
	bool pressedButton(int button);
	bool holdingButton(int button);
	bool releasedButton(int button);
	
	// Methods
	void calculateMovement();
	double getGroundAngle();
	
	// Actions
	void roll();
	void jump();
	
	
};

#endif