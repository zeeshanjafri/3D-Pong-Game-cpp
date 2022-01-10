#ifndef CBALL_H
#define CBALL_H

//#include <GL/glut.h>
//#include "Sphere.hpp"

class Ball{
public:
	//Sphere* sphere;
	float radius;
	float posX, posY, posZ;
	float velX, velY, velZ;
	float initSpeed;

	Ball();
	void move();
	void reset();
	void addVelocity(float y, float z);
	void xCollision();
	void yCollision();
	void zCollision();
};

#endif
