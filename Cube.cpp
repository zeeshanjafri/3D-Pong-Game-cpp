/*
 *  SimpleView : reference design
 *  Author: HBF
 *  Version: 2021-10-15 (update)
 */
#include "Cube.hpp"
#include "Camera.hpp"
#include <stdio.h>

Cube::Cube() {
	vertex[0][0] = -1;
	vertex[0][1] = -1;
	vertex[0][2] = -1;
	vertex[1][0] = -1;
	vertex[1][1] = 1;
	vertex[1][2] = -1;
	vertex[2][0] = 1;
	vertex[2][1] = 1;
	vertex[2][2] = -1;
	vertex[3][0] = 1;
	vertex[3][1] = -1;
	vertex[3][2] = -1;
	vertex[4][0] = -1;
	vertex[4][1] = -1;
	vertex[4][2] = 1;
	vertex[5][0] = -1;
	vertex[5][1] = 1;
	vertex[5][2] = 1;
	vertex[6][0] = 1;
	vertex[6][1] = 1;
	vertex[6][2] = 1;
	vertex[7][0] = 1;
	vertex[7][1] = -1;
	vertex[7][2] = 1;

	face[0][0] = 0;
	face[0][1] = 1;
	face[0][2] = 2;
	face[0][3] = 3;
	face[1][0] = 7;
	face[1][1] = 6;
	face[1][2] = 5;
	face[1][3] = 4;
	face[2][0] = 0;
	face[2][1] = 4;
	face[2][2] = 5;
	face[2][3] = 1;
	face[3][0] = 2;
	face[3][1] = 1;
	face[3][2] = 5;
	face[3][3] = 6;
	face[4][0] = 3;
	face[4][1] = 2;
	face[4][2] = 6;
	face[4][3] = 7;
	face[5][0] = 0;
	face[5][1] = 3;
	face[5][2] = 7;
	face[5][3] = 4;

	faceNormal[0][0] = 0.0, faceNormal[0][1] = 0.0, faceNormal[0][2] = -1.0, faceNormal[1][0] =
			0.0, faceNormal[1][1] = 0.0, faceNormal[1][2] = 1.0;
	faceNormal[2][0] = -1.0, faceNormal[2][1] = 0.0, faceNormal[2][2] = 0.0;
	faceNormal[3][0] = 0.0, faceNormal[3][1] = 1.0, faceNormal[3][2] = 0.0;
	faceNormal[4][0] = 1.0, faceNormal[4][1] = 0.0, faceNormal[4][2] = 0.0;
	faceNormal[5][0] = 0.0, faceNormal[5][1] = -1.0, faceNormal[5][2] = 0.0;

	faceColor[0][0] = 1.0, faceColor[0][1] = 0.0;
	faceColor[0][2] = 0.0;
	faceColor[1][0] = 0.0, faceColor[1][1] = 1.0;
	faceColor[1][2] = 0.0;
	faceColor[2][0] = 0.0, faceColor[2][1] = 0.0;
	faceColor[2][2] = 1.0;
	faceColor[3][0] = 1.0, faceColor[3][1] = 1.0;
	faceColor[3][2] = 0.0;
	faceColor[4][0] = 1.0, faceColor[4][1] = 0.0;
	faceColor[4][2] = 1.0;
	faceColor[5][0] = 0.0, faceColor[5][1] = 1.0;
	faceColor[5][2] = 1.0;

	vertexColor[0][0] = 1.0, vertexColor[0][1] = 0.0;
	vertexColor[0][2] = 0.0;
	vertexColor[1][0] = 0.0, vertexColor[1][1] = 1.0;
	vertexColor[1][2] = 0.0;
	vertexColor[2][0] = 0.0, vertexColor[2][1] = 0.0;
	vertexColor[2][2] = 1.0;
	vertexColor[3][0] = 1.0, vertexColor[3][1] = 1.0;
	vertexColor[3][2] = 0.0;
	vertexColor[4][0] = 1.0, vertexColor[4][1] = 0.0;
	vertexColor[4][2] = 1.0;
	vertexColor[5][0] = 0.0, vertexColor[5][1] = 1.0;
	vertexColor[5][2] = 1.0;
	vertexColor[6][0] = 0.5, vertexColor[6][1] = 0.5;
	vertexColor[6][2] = 0.5;
	vertexColor[7][0] = 0.0, vertexColor[7][1] = 0.0;
	vertexColor[7][2] = 0.0;

	vertexNormal[0][0] = -1;
	vertexNormal[0][1] = -1;
	vertexNormal[0][2] = -1;
	vertexNormal[1][0] = -1;
	vertexNormal[1][1] = 1;
	vertexNormal[1][2] = -1;
	vertexNormal[2][0] = 1;
	vertexNormal[2][1] = 1;
	vertexNormal[2][2] = -1;
	vertexNormal[3][0] = 1;
	vertexNormal[3][1] = -1;
	vertexNormal[3][2] = -1;
	vertexNormal[4][0] = -1;
	vertexNormal[4][1] = -1;
	vertexNormal[4][2] = 1;
	vertexNormal[5][0] = -1;
	vertexNormal[5][1] = 1;
	vertexNormal[5][2] = 1;
	vertexNormal[6][0] = 1;
	vertexNormal[6][1] = 1;
	vertexNormal[6][2] = 1;
	vertexNormal[7][0] = 1;
	vertexNormal[7][1] = -1;
	vertexNormal[7][2] = 1;
}

void Cube::drawFace(int i) {
	glColor3f(r, g, b);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertex[face[i][0]]);
	glVertex3fv(vertex[face[i][1]]);
	glVertex3fv(vertex[face[i][2]]);
	glVertex3fv(vertex[face[i][3]]);
	glEnd();
}

void Cube::draw() {
	glPushMatrix();
	this->ctmMultiply();
	glScalef(sx, sy, sz);

	for (int i = 0; i < 6; i++) {
		drawFace(i);
	}
	glPopMatrix();
}


