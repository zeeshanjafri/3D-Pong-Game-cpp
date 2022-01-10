#ifndef CCIRCLE_H
#define CCIRCLE_H

#include "Shape.hpp"

class Circle : public Shape{
public:

	GLfloat radius;

	Circle();
	void draw();
};

#endif
