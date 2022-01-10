#include "Ball.hpp"

Ball::Ball(){

	radius = 0.3;
	initSpeed = 0.05;

	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;

	velX = -initSpeed;
	velY = 0.0;
	velZ = 0.0;
}

void Ball::reset(){
	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;

	velX = -initSpeed;
	velY = 0.0;
	velZ = 0.0;
}

void Ball::move(){
	posX += velX;
	posY += velY;
	posZ += velZ;
}

void Ball::addVelocity(float y, float z){
	velY += y;
	velZ += z;
}

void Ball::xCollision(){
	velX = -velX;
}

void Ball::yCollision(){
	velY = -velY;
}

void Ball::zCollision(){
	velZ = -velZ;
}
