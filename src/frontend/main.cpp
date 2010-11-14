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
	BACKGROUND[0] = new GLTexture("frontend/images/XN.bmp");
	BACKGROUND[1] = new GLTexture("frontend/images/XP.bmp");
	BACKGROUND[2] = new GLTexture("frontend/images/YN.bmp");
	BACKGROUND[3] = new GLTexture("frontend/images/YP.bmp");
	BACKGROUND[4] = new GLTexture("frontend/images/ZN.bmp");
	BACKGROUND[5] = new GLTexture("frontend/images/ZP.bmp");
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
	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	Bird *bird = (*boids)[0];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

	gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, -4.0, 0.0, 0.0, -1.0);
	//gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, -4.0, 0.0, 0.0, -1.0);
//	gluLookAt(bird->getPos()->getX(), bird->getPos()->getY(), bird->getPos()->getZ(),
//			bird->getPos()->getX()+bird->getDir()->getX(), bird->getPos()->getY()+bird->getDir()->getY(), bird->getPos()->getZ()+bird->getDir()->getZ(), 1.0, 1.0, 1.0);
//	gluLookAt(bird->getPos()->getX(), bird->getPos()->getY(), bird->getPos()->getZ()+1.0,
//				bird->getPos()->getX(), bird->getPos()->getY(), bird->getPos()->getZ()-1.0, 5.0,1.0,-1.0);
//	gluLookAt(0.0, 1.0, 0.0, xrot, yrot, zrot, 1.0, 1.0, 1.0);

   glEnable(GL_TEXTURE_2D);


	Vector<float> *camPos = new Vector<float>(0.0, 0.0, 0.0);
	Vector<float> *size = new Vector<float>(60, 60, 60);
	renderSkybox(camPos, size);

	glDisable(GL_TEXTURE_2D);
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
//	glBindTexture(GL_TEXTURE_2D, BACKGROUND[1]->getTex());	// Select the sky texture

/*
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, BACKGROUND[0]->getTex());	// Select the sky texture
	glBegin(GL_QUADS);
	glColor3f (1.0,1.0,1.0);
		glTexCoord2f(0.0f,0.0f-roll); glVertex3f( -10.0f,10.0f,-50.0f);	// Top right
		glTexCoord2f(1.0f,0.0f-roll); glVertex3f(10.0f,10.0f,-50.0f);	// Top left
		glTexCoord2f(1.0f,1.0f-roll); glVertex3f(10.0f,-10.0f,-50.0f);	// Bottom left
		glTexCoord2f(0.0f,1.0f-roll); glVertex3f( -10.0f,-10.0f,-50.0f);	// Bottom right
	glEnd();

	glBindTexture(GL_TEXTURE_2D, BACKGROUND[1]->getTex());	// Select the sky texture
	glBegin(GL_QUADS);
	glColor3f (1.0,1.0,1.0);
		glTexCoord2f(0.0f,0.0f); glVertex3f( -20.0f,0.0f,-20.0f);	// Top right
		glTexCoord2f(1.0f,0.0f); glVertex3f(20.0f,0.0f,-20.0f);	// Top left
		glTexCoord2f(1.0f,1.0f); glVertex3f(20.0f,0.0f,20.0f);	// Bottom left
		glTexCoord2f(0.0f,1.0f); glVertex3f( -20.0f,0.0f,20.0f);	// Bottom right
	glEnd();


	glDisable(GL_TEXTURE_2D);
*/
/*
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
*/
	glPushMatrix();

	glColor3f(0.2, 0.2, 0.2);
	glTranslatef(0.0f,-0.2f,-2.0f);
	glRotatef(270, 1.0, 0.0, 0.0);
	glutWireCone(0.6,1.8,50,50);

	glPopMatrix();

	//glRotatef(mouseX, 0.0, 1.0, 0.0);
//	glTranslatef(0.0f,0.0f,-vel);
//	glTranslatef(0.0f,vel,0.0f);
	//glRotatef(mouseX, 0.0, 1.0, -(mouseX/100)*1.0);
	//glRotatef(mouseX, 0.0, 1.0, 0.0);
	//glRotatef(-mouseY, 1.0, 0.0, 0.0);

	glPushMatrix();

//	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
//	Bird *bird = (*boids)[0];
	bird->updateMatrix();
	// Translate to our new position.
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

//	roll += 0.015;
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


/************************************************************************/
/*	Render a skybox with center point position and dimension sizes size */
/************************************************************************/
void renderSkybox(Vector<float> *position, Vector<float> *size)
{
// djoubert187 _at_ hotmail.com
	// Begin DrawSkybox
	glColor4f(1.0, 1.0, 1.0,1.0f);

	// Save Current Matrix
	glPushMatrix();

	// Second Move the render space to the correct position (Translate)
	glTranslatef(position->getX(),position->getY(),position->getZ());
	//glRotatef( position->getX(), 1.0f, 0.0f, 0.0f );

	// First apply scale matrix
	glScalef(size->getX(),size->getY(),size->getZ());

	float cz = -0.0f,cx = 1.0f;
	float r = 1.0f; // If you have border issues change this to 1.005f
	// Common Axis Z - FRONT Side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[4]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[3]->getTex());	// Select the sky texture // OK
	glBegin(GL_QUADS);
		glTexCoord2f(cx, cz); glVertex3f(-r ,1.0f,-r);
		glTexCoord2f(cx,  cx); glVertex3f(-r,1.0f,r);
		glTexCoord2f(cz,  cx); glVertex3f( r,1.0f,r);
		glTexCoord2f(cz, cz); glVertex3f( r ,1.0f,-r);
	glEnd();

	// Common Axis Z - BACK side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[5]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[2]->getTex());	// Select the sky texture // OK
	glBegin(GL_QUADS);
		glTexCoord2f(cx,cz);  glVertex3f(-r,-1.0f,-r);
		glTexCoord2f(cx,cx);  glVertex3f(-r,-1.0f, r);
		glTexCoord2f(cz,cx);  glVertex3f( r,-1.0f, r);
		glTexCoord2f(cz,cz);  glVertex3f( r,-1.0f,-r);
	glEnd();

	// Common Axis X - Left side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[2]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[5]->getTex());	// Select the sky texture // OK
	glBegin(GL_QUADS);
		glTexCoord2f(cx,cx); glVertex3f(-1.0f, -r, r);
		glTexCoord2f(cz,cx); glVertex3f(-1.0f,  r, r);
		glTexCoord2f(cz,cz); glVertex3f(-1.0f,  r,-r);
		glTexCoord2f(cx,cz); glVertex3f(-1.0f, -r,-r);
	glEnd();

	// Common Axis X - Right side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[2]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[4]->getTex());	// Select the sky texture
	glBegin(GL_QUADS);
		glTexCoord2f( cx,cx); glVertex3f(1.0f, -r, r);
		glTexCoord2f(cz, cx); glVertex3f(1.0f,  r, r);
		glTexCoord2f(cz, cz); glVertex3f(1.0f,  r,-r);
		glTexCoord2f(cx, cz); glVertex3f(1.0f, -r,-r);
	glEnd();

	// Common Axis Y - Draw Up side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[2]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[1]->getTex());	// Select the sky texture
	glBegin(GL_QUADS);
		glTexCoord2f(cz, cz); glVertex3f( r, -r,1.0f);
		glTexCoord2f(cx, cz); glVertex3f( r,  r,1.0f);
		glTexCoord2f(cx, cx); glVertex3f(-r,  r,1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,1.0f);
	glEnd();

	// Common Axis Y - Down side
	//glBindTexture(GL_TEXTURE_2D,SkyBox[1]);
	glBindTexture(GL_TEXTURE_2D, BACKGROUND[0]->getTex());	// Select the sky texture // OK
	glBegin(GL_QUADS);
		glTexCoord2f(cz,cz);  glVertex3f( r, -r,-1.0f);
		glTexCoord2f( cx,cz); glVertex3f( r,  r,-1.0f);
		glTexCoord2f( cx,cx); glVertex3f(-r,  r,-1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,-1.0f);
	glEnd();

	// Load Saved Matrix
	glPopMatrix();

};

/**
 * Process Input
 */

/*void processSpecialKeys(int key, int x, int y)
{
    switch(key) {
       case GLUT_KEY_LEFT :  bird->rotateX(-5.0); break;
       case GLUT_KEY_RIGHT:  bird->rotateX(-5.0); break;
       case GLUT_KEY_UP   :  bird->rotateX(-5.0); break;
       case GLUT_KEY_DOWN :  bird->rotateX(-5.0); break;

       default: printf ("   Special key %c == %d\n", key, key);
    }

    glutPostRedisplay();
}*/


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
			xrot++;
			break;
		case 'S':
		case 's':
			bird->rotateX(5.0);
			xrot--;
			break;
		case 'A':
		case 'a':
			bird->rotateY(5.0);
			yrot++;
			break;
		case 'D':
		case 'd':
			bird->rotateY(-5.0);
			yrot--;
			break;
		case 'p':
		case 'P':
			bird->updateVelocity(0.001);
			zrot++;
			break;
		case 'O':
		case 'o':
			bird->updateVelocity(-0.001);
			zrot--;
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


