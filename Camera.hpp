#ifndef CCAMERA_H
#define CCAMERA_H

#include <GL/glut.h>
#include "Point.hpp"
#include "Vector.hpp"

class Camera {
 public:
	Point eye; 			/* camera position */
	Point ref; 			/* look at point  */
	Vector viewup; 		/* view up vector */
	GLfloat aspect, dnear, dfar, vangle;

	Camera();
	void set(Point Eye, Point look, Vector up);
	void set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz);
	void reset();
	void setProjectionMatrix();
};

#endif
