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

    // enable light
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable ( GL_COLOR_MATERIAL );
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
	Bird *bird = ENTITIES->getMainBird();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

	Camera *camera = ENTITIES->getCamera();
	if(!CAM) {
		camera->set(0.0, 1.0, 8.0, -bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ(), 0.0, 1.0, 0.0);
	}
	else {
	camera->set(ENTITIES->getTower()->getPos()->getX(), ENTITIES->getTower()->getVol()->getY(), ENTITIES->getTower()->getPos()->getZ(),
			-bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ(), 0.0, 1.0, 0.0);
	}

	/*camera->set(-bird->getPos()->getX() - bird->getDir()->getX() * 10,
			-bird->getPos()->getY() - bird->getDir()->getY() * 10,
			bird->getPos()->getZ() - bird->getDir()->getZ() * 10,
			-bird->getPos()->getX(), -bird->getPos()->getY(),
			bird->getPos()->getZ(), 0.0, 1.0, 0.0);*/
	gluLookAt(camera->getEyeX(), camera->getEyeY(), camera->getEyeZ(),
			camera->getCenterX(), camera->getCenterY(), camera->getCenterZ(),
			camera->getUpX(), camera->getUpY(), camera->getUpZ());

	// Draw world
	Vector<float> *camPos = new Vector<float>(0.0, 0.0, 0.0);
	Vector<float> *size = new Vector<float>(50, 50, 50);
	renderSkybox(camPos, size);

	// Draw Tower
	ENTITIES->drawTower();

	glPushMatrix();

	bird->updateMatrix();
	bird->updatePosition();
	if(-bird->getPos()->getY() < 0.0) {
		bird->getPos()->setY(0.0);
	}
	glTranslatef(-bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());

	glMultMatrixf(bird->getMatrix());

//	printf("pos: (%f, %f, %f)\n", -bird->getPos()->getX(), -bird->getPos()->getY(), bird->getPos()->getZ());
//	printf("dir: (%f, %f, %f)\n", bird->getDir()->getX(), -bird->getDir()->getY(), bird->getDir()->getZ());
//	printf("degree: (%f, %f)\n\n", bird->getDegreesX(), bird->getDegreesY());

	// draw bird
	bird->updateWingPos();
	ENTITIES->drawBird(bird);

	glPopMatrix();

///////////////////////
	std::vector<Bird *> *boids = ENTITIES->getBoids()->getBoids();
	for(int i=1; i<(*boids).size(); i++) {
		Bird *bird2 = (*boids)[i];
		glPushMatrix();
		ENTITIES->getBoids()->updateBoidsPosition();
	//	bird2->updateMatrix();
	//	bird2->updatePosition();
	//	if(-bird2->getPos()->getY() < 0.0) {
	//		bird2->getPos()->setY(0.0);
	//	}

				//printf("rotate angle: %f\n",90 - angle);
		glTranslatef(-bird2->getPos()->getX(), -bird2->getPos()->getY(), bird2->getPos()->getZ());
	//	glMultMatrixf(bird2->getMatrix());
		bird2->updateWingPos();
		ENTITIES->drawBird(bird2);
		glPopMatrix();
	}
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
	glDisable(GL_LIGHTING);
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
	glEnable(GL_LIGHTING);
};

/**
 * Process Input
 */

void processSpecialKeys(int key, int x, int y) {
	Bird *bird = ENTITIES->getMainBird();
	Camera *camera = ENTITIES->getCamera();

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
	case GLUT_KEY_F2:
		CAM = 1;
		break;
	case GLUT_KEY_F1:
		CAM = 0;
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	Bird *bird = ENTITIES->getMainBird();

	switch (key) {
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
	case 'P':
	case 'p':
		bird->setVel(0.0f);
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


