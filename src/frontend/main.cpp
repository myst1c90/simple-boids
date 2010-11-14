/**
*   breakout.cpp
*/

#include "main.h"

                   
int main(int argc, char** argv) {
    // openGL initialization
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	// window configuration
    glutInitWindowPosition(WINDOW_INIT_POSITION_X, WINDOW_INIT_POSITION_Y);
    glutInitWindowSize(WINDOW_INIT_WIDTH, WINDOW_INIT_HEIGHT);
    glutInit(&argc, argv);
    glutCreateWindow(WINDOW_TITLE);

    // set draw function
    glutDisplayFunc(renderScene);
    glutTimerFunc(TIMER_MSECS, drawScene, 1);

    // set reshap function
    glutReshapeFunc(changeSize);

    // set input proccessing functions
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouse);
   	glutPassiveMotionFunc(processMousePassiveMotion);
   	glutEntryFunc(processMouseEntry);

    // main loop
    init();
    glutMainLoop();
}

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// initialize entities
	ENTITIES = new GLEntities();

	// load textures
	TEXTURES[0] = new GLTexture("frontend/images/XN.bmp");
	TEXTURES[1] = new GLTexture("frontend/images/XP.bmp");
	TEXTURES[2] = new GLTexture("frontend/images/YN.bmp");
	TEXTURES[3] = new GLTexture("frontend/images/YP.bmp");
	TEXTURES[4] = new GLTexture("frontend/images/ZN.bmp");
	TEXTURES[5] = new GLTexture("frontend/images/ZP.bmp");
}

void changeSize(GLsizei w, GLsizei h) {
	if (h == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 *  draw funcions
 */
void drawScene(int i) {
	renderScene();
	glutTimerFunc(TIMER_MSECS, drawScene, 1);
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

	Camera *camera = ENTITIES->getCamera();
	gluLookAt(camera->getEyeX(), camera->getEyeY(), camera->getEyeZ(),
			camera->getCenterX(), camera->getCenterY(), camera->getCenterZ(),
			camera->getUpX(), camera->getUpY(), camera->getUpZ());

	// Draw world
	Vector<float> *camPos = new Vector<float>(0.0, 0.0, 0.0);
	Vector<float> *size = new Vector<float>(60, 60, 60);
	renderSkybox(camPos, size);

	// Draw Tower
	ENTITIES->drawTower();

	glPushMatrix();

	Bird *bird = ENTITIES->getMainBird();
	bird->updateMatrix();
	bird->updatePosition();
	if(-bird->getPos()->getY() < 0.0) {
		bird->getPos()->setY(0.0);
	}
	glTranslatef(-bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());

	glMultMatrixf(bird->getMatrix());

	printf("pos: (%f, %f, %f)\n", -bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());
	printf("dir: (%f, %f, %f)\n", bird->getDir()->getX(), -bird->getDir()->getY(), bird->getDir()->getZ());
	printf("degree: (%f, %f)\n\n", bird->getDegreesX(), bird->getDegreesY());

	// draw bird
	bird->updateWingPos();
	ENTITIES->drawBird(bird);

	glPopMatrix();

///////////////////////
	glPushMatrix();
	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	Bird *bird2 = (*boids)[0];
	bird2->updateMatrix();
	bird2->updatePosition();
	if(-bird2->getPos()->getY() < 0.0) {
		bird2->getPos()->setY(0.0);
	}
	glTranslatef(-bird2->getPos()->getX(), -bird2->getPos()->getY(), bird2->getPos()->getZ());
	glMultMatrixf(bird2->getMatrix());
	bird2->updateWingPos();
	ENTITIES->drawBird(bird2);
	glPopMatrix();

///////////////////////


	glPopMatrix();
	glutSwapBuffers();
}


void drawText(float x, float y, char *string, void *font)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

void renderSkybox(Vector<float> *position, Vector<float> *size)
{
	glEnable(GL_TEXTURE_2D);

	// begin DrawSkybox
	glColor4f(1.0, 1.0, 1.0,1.0f);

	// save Current Matrix
	glPushMatrix();

	// second Move the render space to the correct position (Translate)
	glTranslatef(position->getX(),position->getY(),position->getZ());

	// first apply scale matrix
	glScalef(size->getX(),size->getY(),size->getZ());
	float cz = -0.0f,cx = 1.0f;
	float r = 1.0f;

	glBindTexture(GL_TEXTURE_2D, TEXTURES[3]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f(cx, cz); glVertex3f(-r ,1.0f,-r);
		glTexCoord2f(cx,  cx); glVertex3f(-r,1.0f,r);
		glTexCoord2f(cz,  cx); glVertex3f( r,1.0f,r);
		glTexCoord2f(cz, cz); glVertex3f( r ,1.0f,-r);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURES[2]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f(cx,cz);  glVertex3f(-r,-1.0f,-r);
		glTexCoord2f(cx,cx);  glVertex3f(-r,-1.0f, r);
		glTexCoord2f(cz,cx);  glVertex3f( r,-1.0f, r);
		glTexCoord2f(cz,cz);  glVertex3f( r,-1.0f,-r);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURES[5]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f(cx,cx); glVertex3f(-1.0f, -r, r);
		glTexCoord2f(cz,cx); glVertex3f(-1.0f,  r, r);
		glTexCoord2f(cz,cz); glVertex3f(-1.0f,  r,-r);
		glTexCoord2f(cx,cz); glVertex3f(-1.0f, -r,-r);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURES[4]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f( cx,cx); glVertex3f(1.0f, -r, r);
		glTexCoord2f(cz, cx); glVertex3f(1.0f,  r, r);
		glTexCoord2f(cz, cz); glVertex3f(1.0f,  r,-r);
		glTexCoord2f(cx, cz); glVertex3f(1.0f, -r,-r);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURES[1]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f(cz, cz); glVertex3f( r, -r,1.0f);
		glTexCoord2f(cx, cz); glVertex3f( r,  r,1.0f);
		glTexCoord2f(cx, cx); glVertex3f(-r,  r,1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURES[0]->getTex());
	glBegin(GL_QUADS);
		glTexCoord2f(cz,cz);  glVertex3f( r, -r,-1.0f);
		glTexCoord2f( cx,cz); glVertex3f( r,  r,-1.0f);
		glTexCoord2f( cx,cx); glVertex3f(-r,  r,-1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,-1.0f);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
};

/**
 * Process Input
 */

void processSpecialKeys(int key, int x, int y) {
	Bird *bird = ENTITIES->getMainBird();

	switch (key) {
	case GLUT_KEY_LEFT:
		bird->rotateY(5.0);
		break;
	case GLUT_KEY_RIGHT:
		bird->rotateY(-5.0);
		break;
	case GLUT_KEY_UP:
		bird->rotateX(5.0);
		break;
	case GLUT_KEY_DOWN:
		bird->rotateX(-5.0);
		break;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	Bird *bird = ENTITIES->getMainBird();

	switch(key) {
		case 'Q':
		case 'q':
			exit(0);
		case 'E':
		case 'e':
			bird->updateVelocity(0.001);
			break;
		case 'W':
		case 'w':
			bird->updateVelocity(-0.001);
			break;
	}
}

void processMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {

		}
	} else if (button == GLUT_MIDDLE_BUTTON) {
	} else {

	}
}

void processMousePassiveMotion(int x, int y) {
}

void processMouseEntry(int state) {
	//MOUSE_IN = (state == GLUT_LEFT) ? false : true;
}


