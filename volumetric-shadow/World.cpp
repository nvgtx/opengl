#include "OpenGL.h"
#include "World.h"

World::World()
{
	position[0]=0.0;
	position[1]=-3.0;
	position[2]=0.0;
}

World::~World()
{
}

void World::init()
{
}

void World::draw()
{
	const float size=20.0;
	
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);

	glBegin(GL_QUADS);	
	glColor3f(1, 1, 1);
	glNormal3f(0.0f, 1.0f, 0.0f);			// Normal Pointing Up
	glVertex3f(-size,0,-size);				// Back Left
	glVertex3f(-size,0, size);				// Front Left
	glVertex3f( size,0, size);				// Front Right
	glVertex3f( size,0,-size);				// Back 
	glEnd();

	glPopMatrix();
}


