#include "Circle.hpp"
//#include <stdio.h>
#define DEG2RAD (M_PI/180.0)

Circle::Circle(){
	radius = 0.75;
}

void Circle::draw(){
	glColor3f(r, g, b);
	glBegin (GL_LINE_LOOP);
	for (int i = 0; i < 360; i++) {
		float degrees = i * DEG2RAD;
		glVertex3f(x, sin(degrees) * radius + y, cos(degrees) * radius + z);
	}
	glEnd();
}
