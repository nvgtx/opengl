#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "OpenGL.h"
#include "Object.h"
#include "World.h"
#include "Light.h"
#include "Shadow.h"

World* world;
Light* light;
Shadow* shadow;
Object* object;

int winIDglut=0;
int windowWidth=1024;
int windowHeight=768;

float rotateX = 20.0;
float rotateY = 30.0;
float zoom = 25.0;
float maxzoom=30.0;

void init()
{
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glClearStencil(0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	light->init();
	world->init();
	object->init();

	shadow->init(light);
}

void resize(int x, int y)
{
	windowWidth=x;
	windowHeight=y;

	glViewport(0, 0, windowWidth, windowHeight);

	init();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (double)windowWidth/(double)windowWidth, 0.001f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//camera-distance to objects
	glTranslatef(0.0, 0.0, -zoom);

	glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
	glRotatef(rotateY, 0.0f, 1.0f, 0.0f);

	light->draw();
	world->draw();
	shadow->draw(object);

	glutSwapBuffers();
	GLenum error=glGetError();
	assert(error == GL_NO_ERROR);
}

GLFWAPI void timer(int millis)
{
	render();
	glutTimerFunc(millis, timer, millis);
}

void quit()
{
	glutDestroyWindow(winIDglut);
	exit(0);
}

void specialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if(rotateX<90.0)
		{	
			rotateX += 1.0;
		}
		break;

	case GLUT_KEY_DOWN:
		if(rotateX>1.0)
		{
			rotateX -= 1.0;
		}
		break;

	case GLUT_KEY_RIGHT:
		rotateY -= 1.0;
		break;

	case GLUT_KEY_LEFT:
		rotateY += 1.0;
		break;

	default:
		return;
	}

	if(rotateX >= 360.0)
	{
		rotateX=0.0;
	}
	if(rotateX < 0)
	{
		rotateX=359.0;
	}
	if(rotateY >= 360.0)
	{
		rotateY=0.0;
	}
	if(rotateY < 0)
	{
		rotateY=359.0;
	}

	render();
}

void keyPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		//links
	case '4':
	case 'a':
	case 'A':
		light->setPosX(light->getPosX()-1);
		break;
	case '6':
	case 'd':
	case 'D':
		//rechts
		light->setPosX(light->getPosX()+1);
		break;
	case '2':
	case 'y':
	case 'Y':
		//unten
		if(light->getPosY()>0)
		{
			light->setPosY(light->getPosY()-1);	
		}
		break;
	case '8':
	case 'w':
	case 'W':
		//oben
		light->setPosY(light->getPosY()+1);
		break;
	case '9':
	case 'e':
	case 'E':
		//hinten
		light->setPosZ(light->getPosZ()-1);
		break;
	case '3':
	case 'x':
	case 'X':
		//vorne
		light->setPosZ(light->getPosZ()+1);
		break;
	case '+':
		//zoom +
		if(zoom>1)
		{
			zoom--;
		}
		break;
	case '-':
		//zoom -
		if(zoom<maxzoom)
		{
			zoom++;
		}
		break;
		// enter
	case 13:
		break;
		// ESC/Q/q=quit
	case 27:
	case 'q':
	case 'Q':
		quit();
		return;
	}

	render();
}

int main(int argc, char* argv[])
{
	world=new World();
	light=new Light();
	shadow=new Shadow();
	object=new Object();

	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA | GLUT_STENCIL);

	glutInitWindowSize(windowWidth, windowHeight);

	winIDglut=glutCreateWindow("Volumetric Shadows");

	GLenum err=glewInit();
	if(GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyPress);
	glutSpecialFunc(specialKeyPress);
	glutTimerFunc(1000, timer, 1000);

	resize(windowWidth, windowHeight);

	init();

	glutMainLoop();

	return 0;
}
