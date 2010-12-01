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


enum State {
	RUNNING,
	PAUSED,
};


// variables
bool DEBUGGING;
float CAM_DIST;
CameraType CAM_TYPE;
enum State STATE;
GLEntities *ENTITIES;
GLTexture *TEXTURES[6];


// prototypes
int main(int argc, char** argv);
void init(void);
void changeSize(GLsizei w, GLsizei h);

void drawScene(int i);
void renderScene();
void renderSkybox(Vector<float> *position, Vector<float> *size);

void processNormalKeys(unsigned char key, int x, int y);
void processMouse(int button, int state, int x, int y);
void processMousePassiveMotion(int x, int y);
void processMouseEntry(int state);
void processSpecialKeys(int key, int x, int y);
void drawText(float x, float y, float z, char *string, void *font);
void debug();
void updateCamera();

void processMenuEvents(int option);
void loadMenu();


#endif /* MAIN_H_ */
