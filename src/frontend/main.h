/*
 * main.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <time.h>
#include <stdlib.h>

#include "glEntities.h"
#include "glTexture.h"


// constants
#define COORD_RANGE		1.0f
#define TIMER_MSECS		10
#define WINDOW_TITLE	"Boids"
#define WINDOW_INIT_POSITION_X      200
#define WINDOW_INIT_POSITION_Y      200
#define WINDOW_INIT_WIDTH           820
#define WINDOW_INIT_HEIGHT          640

// variables
GLEntities *ENTITIES;
bool	KEYS[256];
bool	ACTIVE = true;
GLTexture *BACKGROUND[2];
float WING_POS;
bool WING_DIR;
GLfloat roll;			// Rolling clouds
GLfloat		rtri = 0.0;						// Angle For The Triangle
GLfloat		rquad = 0.0;						// Angle For The Quad
GLfloat		xrot;								// X Rotation ( NEW )
GLfloat		yrot;								// Y Rotation ( NEW )
GLfloat		zrot;								// Z Rotation ( NEW )
GLfloat 	mouseX, mouseY;
float		vel;

// prototypes
int main(int argc, char** argv);
void init(void);
void changeSize(GLsizei w, GLsizei h);

void drawScene(int i);
void renderScene();
void processNormalKeys(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouseEntry(int state);

void drawBackground();

#endif /* MAIN_H_ */
