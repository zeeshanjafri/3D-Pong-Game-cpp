#include <stdio.h>
#include "Camera.hpp"
#include <math.h>

Camera::Camera(){
	reset();
}

void Camera::reset(void) { // make default camera
	//eye.set(2.5, 5.0, 0.0);
	//ref.set(2.5, 0.0, 0.0);

	eye.set(5.0, 0.0, 0.0);
	ref.set(0, 0, 0);
	viewup.set(0, 0, 1);
	aspect = 1.0, vangle = 90.0, dnear = 1.0, dfar = 50.0;
}

void Camera::set(Point Eye, Point Look, Vector Up) {
	eye.set(Eye);
	ref.set(Look);
	viewup.set(Up);
}

void Camera::set(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz) {
	eye.set(ex, ey, ez);
	ref.set(lx, ly, lz);
	viewup.set(upx, upy, upz);
}

void Camera::setProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(vangle, aspect, dnear, dfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, ref.x, ref.y, ref.z, viewup.x, viewup.y, viewup.z);
}

