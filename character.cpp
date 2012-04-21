#include "character.h"

std::vector<Character> Character::CharacterList;

Sensor::Sensor() {}

Sensor::Sensor(double x1, double y1, double x2, double y2) {
	sensorVector = Vector(x1, y1, x2, y2);
	tClosest = -1;
	activated = false;
}

bool Sensor::isActivated() {
	return activated;
}

double Sensor::getTClosest() {
	return tClosest;
}

double Sensor::setTClosest(double t) {
	tClosest = t;
}

void Sensor::resetTClosest() {
	tClosest = -1;
}

void Sensor::activate() {
	activated = true;
}

void Sensor::deactivate() {
	activated = false;
}

Character::Character() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	
	maxSlideAngle = 30;
	maxSwitchAngle = 45;
	
	modeAngle = MODE_DOWN;
	gravityAngle = MODE_DOWN;
	
	state = STATE_STANDING;
	
	speedX = 0;
	speedY = 0;
	speedGround = 0;
	speedAir = 0;
	angle = 0;
	
	sensorGroundL = Sensor(0,0,0,0);
	sensorGroundR = Sensor(0,0,0,0);
	sensorGroundLength = 17;
	sensorGroundSpacing = 9;
	
	sensorCeilingL = Sensor(0,0,0,0);
	sensorCeilingR = Sensor(0,0,0,0);
	sensorCeilingLength = 17;
	sensorCeilingSpacing = 9;
	
	sensorWallL = Sensor(0,0,0,0);
	sensorWallR = Sensor(0,0,0,0);
	sensorWallLength = 10;
	
	inputQueueLength = 8;
	
	for(int i = 0; i < inputQueueLength; i++) {
		inputQueue.push_back(0);
	}
}

bool Character::pressedButton(int button) {
	return (inputQueue[0]&button && !(inputQueue[1]&button));
}

bool Character::holdingButton(int button) {
	return (inputQueue[0]&button);
}

bool Character::releasedButton(int button) {
	return (!(inputQueue[0]&button) && inputQueue[1]&button);
}

void Character::calculateMovement() {
	// Try to roll
	if (pressedButton(BUTTON_DOWN)) {
		roll();
	}
	
	// Use correct constants
	//updateConstants();
	
	// If character is no longer on the ground, convert his momentum to the default gravity at the time.
	// If not, make him hug the ground.
	//if(!Grounded) {
	//	ConvertMomentum((float)GravityAngle*90);
	//	Angle = GravityAngle*90.0f;
	//} else {
	//	TouchGround();
	//}
	
	// Add slope factor
	if(speedGround != 0 || abs(getGroundAngle()) > maxSlideAngle)
		speedGround -= slopeFactor * sin(getGroundAngle() * DEG_TO_RAD);
		
	//updateSensors();
	
	// Horizontal motion
	if(holdingButton(BUTTON_LEFT)) {
		if (speedGround > 0) {
			if(speedGround - decel < 0) {
				speedGround = -decel;
			} else {
				speedGround += -decel;
			}
		} else if (speedGround > -maxSpeed && state != STATE_ROLLING) {
			speedGround += -accel;
			if (speedGround < -maxSpeed) speedGround = -maxSpeed;
		}
	} else if(holdingButton(BUTTON_RIGHT)) {
		if (speedGround < 0) {
			if(speedGround - decel > 0) {
				speedGround = decel;
			} else {
				speedGround += decel;
			}
		} else if (speedGround < maxSpeed && state != STATE_ROLLING) {
			speedGround += accel;
			if (speedGround > maxSpeed) speedGround = maxSpeed;
		}
	}

	// Friction
	if(state == STATE_ROLLING || (!holdingButton(BUTTON_LEFT) && !holdingButton(BUTTON_RIGHT))) {
		speedGround -= min(abs(speedGround), friction) * sign(speedGround);
	}

	// Unroll
	if(state == STATE_ROLLING && speedGround == 0) {
		state = holdingButton(BUTTON_DOWN) ? STATE_CROUCHING : STATE_STANDING;
	}


	// Air drag
	if(speedAir < 0 && speedAir > -4) {
		if(abs(speedGround) >= 0.125) speedGround *= drg;
	}

	// Check if walked off a platform
	if(!sensorGroundL.isActivated() && !sensorGroundR.isActivated()) {
		grounded = false;
	}

	// Vertical motion
	if(!grounded) {
		speedAir += gravity;
		if(speedAir > amx) speedAir = amx;
	}

	// Variable jump height
	if(state == STATE_JUMPING && releasedButton(BUTTON_JUMP) && speedAir < -4) {
		state = STATE_FALLING;
		speedAir = -4;
	}
}

float Character::getGroundAngle() {
	double theta = (angle - modeAngle);
	return clamp(theta, -180, 180);
}
	
	