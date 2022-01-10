#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <sstream>
#include <GL/glut.h>

#include "Camera.hpp"
#include "World.hpp"
#include "Ball.hpp"
#include "Light.hpp"

using namespace std;

// global variables

// display window size
GLsizei winWidth = 800, winHeight = 800;

Camera myCam;
World myWorld;
Ball gameBall;
Shape* sphere;
Shape* paddle;
Shape* target;
Shape* tracker;
Shape* walls[5];
Light light;

const int interval = 1000 / 60;

int gameState = 0; //0 -> mainMenu	1 -> readyToServe	2 -> playing
int gameOver = 0;
int lives = 3;
int score = 0;

float sideBound = 2.0;
float backBound = -2.5;
float frontBound = 2.5;

float paddleY = 0.0;
float paddleZ = 0.0;
float paddleMapFactor = 1.2;
float paddleRadius = 0.5;
float addVel = 0.02;

float targetY = 0.0;
float targetZ = 0.0;
float targetRadius = 0.75;

float trackerX = 0.0;

// lighting variables
GLfloat position[] = { 0.0, 0.0, 1.0, 0.0 };

GLfloat ambient[] = { 0.1, 0.1, 0.3, 1.0 };
GLfloat diffuse[] = { 0.6, 0.6, 1.0, 1.0 };
GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

//Material
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 1, 1, 1, 1 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 1, 1, 1, 1 };

//function declarations
void mouseMotion(int, int);
void mouseClick(int, int, int, int);
void collisionDetection(void);
void targetRandPos(void);
void drawText(void);
void updateObjects(void);
void display(void);
void update(int);
void init(void);


//maps mouse coordinates to world coordinates for paddle
void mouseMotion(int x, int y){
	paddleY = (x - 400) / 200.0 * paddleMapFactor;
	paddleZ = -(y - 400) / 200.0 * paddleMapFactor;
	//cout << "X: " << paddleY << "  Y: " << paddleZ << "\n";
}

void mouseClick(int button, int state, int x, int y){
	if(gameState == 0){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			lives = 3;
			score = 0;
			gameState = 1;
			gameOver = 0;
			gameBall.reset();
			targetY = 0.0;
			targetZ = 0.0;
		}
	}
	else if(gameState == 1){
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			gameState = 2;
		}
	}
}

void collisionDetection(){
	//collision with front boundary
	if(gameBall.posX + gameBall.radius > frontBound){

		//check if ball hit the paddle
		if((gameBall.posY < paddleY + paddleRadius && gameBall.posY > paddleY - paddleRadius)
			&& (gameBall.posZ < paddleZ + paddleRadius && gameBall.posZ > paddleZ - paddleRadius)){

			//adds speed from contacting the paddle
			gameBall.addVelocity((gameBall.posY - paddleY) * 2 * addVel,
								(gameBall.posZ - paddleZ) * 2 * addVel);

			//collision
			gameBall.xCollision();
			score += 50;

			cout << "paddle hit!\n";
		}
		else{
			//ball missed paddle -> reset ball and gamestate
			lives -= 1;
			if(lives <= 0){
				gameState = 0;
				gameOver = 1;
			}
			else{
				gameState = 1;
				gameBall.reset();
			}
			cout << "paddle miss!\n";
		}
	}

	//collision with back boundary
	if(gameBall.posX - gameBall.radius < backBound){

		//check if ball hit target
		if(sqrt(pow((gameBall.posY - targetY), 2.0) + pow((gameBall.posZ - targetZ), 2.0)) < targetRadius){
			cout << "hit target!\n";
			score += 1000;
			targetRandPos();
		}
		else{
			score += 50;
		}

		gameBall.xCollision();
	}

	//collision with horizontal boundaries
	if(gameBall.posY + gameBall.radius > sideBound || gameBall.posY - gameBall.radius < -sideBound){
		gameBall.yCollision();
		score += 50;
	}

	//collision with vertical boundaries
	if(gameBall.posZ + gameBall.radius > sideBound || gameBall.posZ - gameBall.radius < -sideBound){
		gameBall.zCollision();
		score += 50;
	}
}

//randomly move target
void targetRandPos(){
	float r1 = ((float) rand() / RAND_MAX * (4.0 - (2.0 * targetRadius))) - (2.0 - targetRadius);
	float r2 = ((float) rand() / RAND_MAX * (4.0 - (2.0 * targetRadius))) - (2.0 - targetRadius);

	cout << "t1: " << r1 << "\nt2: " << r2 << "\n";

	targetY = r1;
	targetZ = r2;
}

void drawText(){
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);

	std::ostringstream s;

	if(gameState == 0){
		s.str("");
		s << "Click to Play";
		string strPlay = s.str();
		glRasterPos2f(340, 400);
		for (string::iterator i = strPlay.begin(); i != strPlay.end(); ++i) {
		char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		}
	}
	else if(gameState == 1){
		s.str("");
		s << "Serve!";
		string strServe = s.str();
		glRasterPos2f(375, 450);
		for (string::iterator i = strServe.begin(); i != strServe.end(); ++i) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		}
	}

	if(gameState != 0){
		s.str("");
		s << "Lives: " << lives;
		string strLives = s.str();
		glRasterPos2f(100, 760);
		for (string::iterator i = strLives.begin(); i != strLives.end(); i++) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		}
	}

	if(gameState != 0 || gameOver == 1){
		s.str("");
		s << "Score: " << score;
		string strScore = s.str();
		if(gameOver == 1){
			glRasterPos2f(350, 500);
		}
		else{
			glRasterPos2f(580, 760);
		}
		for (string::iterator i = strScore.begin(); i != strScore.end(); i++) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		}
	}

	if(gameOver == 1){
		s.str("");
		s << "Game Over";
		string strOver = s.str();
		glRasterPos2f(360, 550);
		for (string::iterator i = strOver.begin(); i != strOver.end(); i++) {
			char c = *i;
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
		}
	}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void updateObjects(){
	sphere->moveToPoint(gameBall.posX, gameBall.posY, gameBall.posZ);
	paddle->moveToPoint(2.6, paddleY, paddleZ);
	target->moveToPoint(-2.5, targetY, targetZ);
	tracker->moveToPoint(trackerX, 0.0, 0.0);
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	light.on(); //turn on light
	if (light.getOn()) {
		glEnable(GL_CULL_FACE);
		glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		position[0] = light.lx;
		position[1] = light.ly;
		position[2] = light.lz;
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	} else {
		glDisable(GL_LIGHTING);
	}

	myCam.setProjectionMatrix();
	if(gameState != 0){
		updateObjects();
		myWorld.draw();
	}
	drawText();

	glFlush();
	glutSwapBuffers();
}

void update(int value) {
	//cout << "yo angelo!\n";

	if(gameState == 2){
		collisionDetection();
		gameBall.move();
		trackerX = gameBall.posX * 1.1;
	}

	glutTimerFunc(interval, update, 0);
	glutPostRedisplay();
}

void ballMenu(GLint x){
	switch(x){
	case 1:
		sphere->setColour(1.0, 0.0, 0.0);
		break;
	case 2:
		sphere->setColour(0.0, 1.0, 0.0);
		break;
	case 3:
		sphere->setColour(0.0, 0.0, 1.0);
		break;
	case 4:
		sphere->setColour(1.0, 1.0, 0.0);
		break;
	case 5:
		sphere->setColour(1.0, 0.0, 1.0);
		break;
	case 6:
		sphere->setColour(0.0, 1.0, 1.0);
		break;
	case 7:
		sphere->setColour(1.0, 1.0, 1.0);
		break;
	}
}

void paddleMenu(GLint x){
	switch(x){
	case 1:
		paddle->setColour(1.0, 0.0, 0.0);
		break;
	case 2:
		paddle->setColour(0.0, 1.0, 0.0);
		break;
	case 3:
		paddle->setColour(0.0, 0.0, 1.0);
		break;
	case 4:
		paddle->setColour(1.0, 1.0, 0.0);
		break;
	case 5:
		paddle->setColour(1.0, 0.0, 1.0);
		break;
	case 6:
		paddle->setColour(0.0, 1.0, 1.0);
		break;
	case 7:
		paddle->setColour(1.0, 1.0, 1.0);
		break;
	}
}

void trackerMenu(GLint x){
	switch(x){
	case 1:
		tracker->setColour(1.0, 0.0, 0.0);
		break;
	case 2:
		tracker->setColour(0.0, 1.0, 0.0);
		break;
	case 3:
		tracker->setColour(0.0, 0.0, 1.0);
		break;
	case 4:
		tracker->setColour(1.0, 1.0, 0.0);
		break;
	case 5:
		tracker->setColour(1.0, 0.0, 1.0);
		break;
	case 6:
		tracker->setColour(0.0, 1.0, 1.0);
		break;
	case 7:
		tracker->setColour(1.0, 1.0, 1.0);
		break;
	}
}

void wallMenu(GLint x){
	switch(x){
	case 1:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(1.0, 0.0, 0.0);
		}
		break;
	case 2:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(0.0, 1.0, 0.0);
		}
		break;
	case 3:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(0.0, 0.0, 1.0);
		}
		break;
	case 4:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(1.0, 1.0, 0.0);
		}
		break;
	case 5:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(1.0, 0.0, 1.0);
		}
		break;
	case 6:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(0.0, 1.0, 1.0);
		}
		break;
	case 7:
		for(int i = 1; i <= 5; i++){
			walls[i]->setColour(1.0, 1.0, 1.0);
		}
		break;
	}
}

void mainMenu(GLint x){}

void menu() {
GLint ball_menu, paddle_menu, tracker_menu, wall_menu;

ball_menu = glutCreateMenu(ballMenu);
glutAddMenuEntry("Red", 1);
glutAddMenuEntry("Green", 2);
glutAddMenuEntry("Blue", 3);
glutAddMenuEntry("Yellow", 4);
glutAddMenuEntry("Magenta", 5);
glutAddMenuEntry("Cyan", 6);
glutAddMenuEntry("White", 7);

paddle_menu = glutCreateMenu(paddleMenu);
glutAddMenuEntry("Red", 1);
glutAddMenuEntry("Green", 2);
glutAddMenuEntry("Blue", 3);
glutAddMenuEntry("Yellow", 4);
glutAddMenuEntry("Magenta", 5);
glutAddMenuEntry("Cyan", 6);
glutAddMenuEntry("White", 7);

tracker_menu = glutCreateMenu(trackerMenu);
glutAddMenuEntry("Red", 1);
glutAddMenuEntry("Green", 2);
glutAddMenuEntry("Blue", 3);
glutAddMenuEntry("Yellow", 4);
glutAddMenuEntry("Magenta", 5);
glutAddMenuEntry("Cyan", 6);
glutAddMenuEntry("White", 7);

wall_menu = glutCreateMenu(wallMenu);
glutAddMenuEntry("Red", 1);
glutAddMenuEntry("Green", 2);
glutAddMenuEntry("Blue", 3);
glutAddMenuEntry("Yellow", 4);
glutAddMenuEntry("Magenta", 5);
glutAddMenuEntry("Cyan", 6);
glutAddMenuEntry("White", 7);

glutCreateMenu(mainMenu);


glutAddSubMenu("Ball Colour", ball_menu);
glutAddSubMenu("Paddle Colour", paddle_menu);
glutAddSubMenu("Tracker Colour", tracker_menu);
glutAddSubMenu("Wall Colour", wall_menu);
}

void init(void) {
	glutInitDisplayMode(GLUT_DOUBLE);  // GLUT_DOUBLE for double frame buffer
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("final");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);

	// define some colors
	GLfloat amb0[ ] = {0.2, 0.4, 0.6, 1.0};
	GLfloat diff0[ ] = {0.8, 0.9, 0.5, 1.0};
	GLfloat spec0[ ] = {1.0, 0.8, 1.0, 1.0};

	// attach them to LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	for(int i = 1; i <= 5; i++){
		walls[i] = myWorld.searchById(i);
	}

	tracker = myWorld.searchById(8);
	target = myWorld.searchById(9);
	sphere = myWorld.searchById(10);
	paddle = myWorld.searchById(11);
}

int main(int argc, char** argv) {
	setvbuf(stdout, NULL, _IONBF, 0); // For Eclipse stdout debugging
	setvbuf(stderr, NULL, _IONBF, 0);

	glutInit(&argc, argv);
	init();
	menu();

	glutDisplayFunc(display);
	glutPassiveMotionFunc(mouseMotion);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClick);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutTimerFunc(interval, update, 0);
	glutMainLoop();
	return 0;
}
