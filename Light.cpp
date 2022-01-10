/*
 * Light.cpp
 *
 */

#include "Light.hpp"

Light::Light() {
	P = 1.0, B = 1.0, Ka = 1.0, Kd = 1.0;
	lx = 3.0, ly = 1.0, lz = 2.5;
	pointOff();

}

void Light::on() {
	P = 0.8, B = 0.3, Ka = 1.0, Kd = 1.0;
	isOn = true;
}

void Light::off() {
	P = 1.0, B = 1.0, Ka = 1.0, Kd = 1.0;
	isOn = false;
}
void Light::pointOn() {
	showPoint = true;
}

void Light::pointOff() {
	showPoint = false;
}

void Light::resetPosition() {
	lx = 1.8, ly = 1.8, lz = 1.5;
}

void Light::resetIllumination() {
	P = 0.8, B = 0.3, Ka = 1.0, Kd = 1.0;
}

void Light::resetAll() {
	resetPosition();
	resetIllumination();
}

void Light::draw() {
	if (showPoint && isOn) {
		glPushMatrix();
		glColor3f(P, P, P);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPointSize(100.0);

		glBegin(GL_POINTS);
		glVertex3f(lx, ly, lz);
		glEnd();
		glPopMatrix();
	}
}


bool Light::getOn() {
	return isOn;
}
