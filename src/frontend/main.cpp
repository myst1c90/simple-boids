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
	BACKGROUND[0] = new GLTexture("frontend/images/Sky.tga");
	//BACKGROUND[1] = new GLTexture("images/Ground.tga");
	BACKGROUND[1] = new GLTexture("frontend/images/Ground.tga");
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

	//TODO fazer plano do ceu e da terra e conseguir guiar a camera por ele
	//TODO usar transf ou rot para fazer isso.
	//TODO camera deve rodar pra baixo e pra cima
	/*glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, BACKGROUND[0]->getTex());	// Select the sky texture
		glBegin(GL_QUADS);					// Begin drawing quads
			glTexCoord2f(1.0f,roll/1.5f+1.0f); glVertex3f( 28.0f,+7.0f,-50.0f);	// Top right
			glTexCoord2f(0.0f,roll/1.5f+1.0f); glVertex3f(-28.0f,+7.0f,-50.0f);	// Top left
			glTexCoord2f(0.0f,roll/1.5f+0.0f); glVertex3f(-28.0f,-3.0f,-50.0f);	// Bottom left
			glTexCoord2f(1.0f,roll/1.5f+0.0f); glVertex3f( 28.0f,-3.0f,-50.0f);	// Bottom right

			glTexCoord2f(1.5f,roll+1.0f); glVertex3f( 28.0f,+7.0f,-50.0f);		// Top right
			glTexCoord2f(0.5f,roll+1.0f); glVertex3f(-28.0f,+7.0f,-50.0f);		// Top left
			glTexCoord2f(0.5f,roll+0.0f); glVertex3f(-28.0f,-3.0f,-50.0f);		// Bottom left
			glTexCoord2f(1.5f,roll+0.0f); glVertex3f( 28.0f,-3.0f,-50.0f);		// Bottom right

			glTexCoord2f(1.0f,roll/1.5f+1.0f); glVertex3f( 28.0f,+7.0f,0.0f);	// Top right
			glTexCoord2f(0.0f,roll/1.5f+1.0f); glVertex3f(-28.0f,+7.0f,0.0f);	// Top left
			glTexCoord2f(0.0f,roll/1.5f+0.0f); glVertex3f(-28.0f,+7.0f,-50.0f);	// Bottom left
			glTexCoord2f(1.0f,roll/1.5f+0.0f); glVertex3f( 28.0f,+7.0f,-50.0f);	// Bottom right

			glTexCoord2f(1.5f,roll+1.0f); glVertex3f( 28.0f,+7.0f,0.0f);		// Top right
			glTexCoord2f(0.5f,roll+1.0f); glVertex3f(-28.0f,+7.0f,0.0f);		// Top left
			glTexCoord2f(0.5f,roll+0.0f); glVertex3f(-28.0f,+7.0f,-50.0f);		// Bottom left
			glTexCoord2f(1.5f,roll+0.0f); glVertex3f( 28.0f,+7.0f,-50.0f);		// Bottom right
		glEnd();								// Done drawing quads

		glBindTexture(GL_TEXTURE_2D, BACKGROUND[1]->getTex());	// Select the sky texture
		glBegin(GL_QUADS);							// Draw a quad
			glTexCoord2f(0.0f,0.0f+roll); glVertex3f( 5.0f,0.0f,-5.0f);	// Top right
			glTexCoord2f(1.0f,0.0f+roll); glVertex3f(-5.0f,0.0f,-5.0f);	// Top left
			glTexCoord2f(1.0f,1.0f+roll); glVertex3f(-5.0f,-2.0f,0.0f);	// Bottom left
			glTexCoord2f(0.0f,1.0f+roll); glVertex3f( 5.0f,-2.0f,0.0f);	// Bottom right

			glTexCoord2f(0.0f,0.0f+roll); glVertex3f( 27.0f,-5.0f,-50.0f);	// Top right
			glTexCoord2f(1.0f,0.0f+roll); glVertex3f(-27.0f,-5.0f,-50.0f);	// Top left
			glTexCoord2f(1.0f,1.0f+roll); glVertex3f(-27.0f,-5.0f,0.0f);	// Bottom left
			glTexCoord2f(0.0f,1.0f+roll); glVertex3f( 27.0f,-5.0f,0.0f);	// Bottom right

		glEnd();								// Done drawing quad
	//glDisable(GL_TEXTURE_2D);
*/

	double eyeX = 2*(mouseX - WINDOW_INIT_WIDTH/2)/WINDOW_INIT_WIDTH;
	double eyeY = 2*(mouseY - WINDOW_INIT_HEIGHT/2)/WINDOW_INIT_HEIGHT;
	printf("eyeX: %f, eyeY: %f\n", eyeX, eyeY);
//	gluLookAt(eyeX, eyeY, 0.0, 0.0, -1.0, -1.0, 0.0, 0.0, 1.0);
	//gluLookAt(eyeX, eyeY, 3.0, 0.0, 0.0, -4.0, 0.0, 0.0, 1.0);
	gluLookAt(-0.0, -0.2, 1.0, 0.0, 0.0, -4.0, 0.0, 0.0, 1.0);

	glBegin(GL_QUADS);							// Draw a quad
		glColor3f(0.5, 0.0, 0.0);
		glVertex3f( 2.0f,1.0f,-7.0f);	// Top right
		glVertex3f(-2.0f,1.0f,-7.0f);	// Top left
		glVertex3f(-2.0f,-1.0f,0.0f);	// Bottom left
		glVertex3f( 2.0f,-1.0f,0.0f);	// Bottom right

		glColor3f(0.0, 0.0, 1.0);
		glVertex3f( 2.0f,2.0f,-7.0f);	// Top right
		glVertex3f(-2.0f,2.0f,-7.0f);	// Top left
		glVertex3f(-2.0f,-0.0f,-7.0f);	// Bottom left
		glVertex3f( 2.0f,-0.0f,-7.0f);	// Bottom right
	glEnd();

	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.0f,0.0f,-2.0f);
	glRotatef(270, 1.0, 0.0, 0.0);
	glutWireCone(0.5,1.0,20,20);

	glPopMatrix();

	//glRotatef(mouseX, 0.0, 1.0, 0.0);
//	glTranslatef(0.0f,0.0f,-vel);
//	glTranslatef(0.0f,vel,0.0f);
	//glRotatef(mouseX, 0.0, 1.0, -(mouseX/100)*1.0);
	//glRotatef(mouseX, 0.0, 1.0, 0.0);
	//glRotatef(-mouseY, 1.0, 0.0, 0.0);

	glPushMatrix();

	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	Bird *bird = (*boids)[0];
	bird->updateMatrix();
	// Translate to our new position.
	bird->updatePosition();
	glTranslatef(-bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());

	glMultMatrixf(bird->getMatrix());

	printf("pos: (%f, %f, %f)\n", -bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());
	printf("dir: (%f, %f, %f)\n", bird->getDir()->getX(), -bird->getDir()->getY(), bird->getDir()->getZ());
	printf("degree: (%f, %f)\n\n", bird->getDegreesX(), bird->getDegreesY());

	// draw bird
	ENTITIES->drawBird(WING_POS);

	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();

	rtri+=2.0;
	rquad=rquad-0.9f;

	if(WING_POS <= -0.015) {
		WING_POS = -0.015;
		WING_DIR = true;
	}
	if(WING_POS >= 0.015) {
		WING_POS = 0.015;
		WING_DIR = false;
	}
	if(WING_DIR) {
		WING_POS += 0.002;
	}
	else {
		WING_POS -= 0.002;
	}
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

void drawBackground() {
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	BACKGROUND[0]->drawEntire(-1.5, 1.5, 1.5, -1.5);
	glDisable(GL_TEXTURE_2D);
}

/**
 * Process Input
 */

void processNormalKeys(unsigned char key, int x, int y) {
	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	Bird *bird = (*boids)[0];

	switch(key) {
		case 'Q':
		case 'q':
			exit(0);
		case 'W':
		case 'w':
			bird->rotateX(-5.0);
			break;
		case 'S':
		case 's':
			bird->rotateX(5.0);
			break;
		case 'A':
		case 'a':
			bird->rotateY(5.0);
			break;
		case 'D':
		case 'd':
			bird->rotateY(-5.0);
			break;
		case 'p':
		case 'P':
			bird->updateVelocity(0.001);
			break;
		case 'O':
		case 'o':
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
	mouseX = x;
	mouseY = y;
	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	Bird *bird = (*boids)[0];
}

void processMouseEntry(int state) {
	//MOUSE_IN = (state == GLUT_LEFT) ? false : true;
}


