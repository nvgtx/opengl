#include "OpenGL.h"

#include "Light.h"

Light::Light(void)
{
	maxPosition=20.0;

	lightColor[0]=1.0;// R
	lightColor[1]=1.0;// G
	lightColor[2]=1.0;// B
	lightColor[3]=1.0;// A

	position[0]=3.0;// X
	position[1]=8.0;// Y
	position[2]=-4.0;// Z
	position[3]=1.0;// positioned / directional
}

Light::~Light(void)
{
}

void Light::init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void Light::setPosX(float pos)
{
	if(pos >= -maxPosition && pos <= maxPosition)
	{
		position[0]=pos;
	}
}

void Light::setPosY(float pos)
{
	if(pos >= -maxPosition && pos <= maxPosition)
	{
		position[1]=pos;
	}
}

void Light::setPosZ(float pos)
{
	if(pos >= -maxPosition && pos <= maxPosition)
	{
		position[2]=pos;
	}
}

float Light::getPosX()
{
	return position[0];
}
float Light::getPosY()
{
	return position[1];
}
float Light::getPosZ()
{
	return position[2];
}
float Light::getPositioned()
{
	return position[3];
}

float Light::getColorR()
{
	return lightColor[0];
}
float Light::getColorG()
{
	return lightColor[1];
}
float Light::getColorB()
{
	return lightColor[2];
}
float Light::getColorA()
{
	return lightColor[3];
}


void Light::draw()
{
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	
	//Draw sphere
	glColor3f(lightColor[0], lightColor[1], lightColor[2]);

	glDisable(GL_LIGHTING);
	glutSolidSphere(0.2, 32, 32);
	glEnable(GL_LIGHTING);

	//Add positioned light
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glPopMatrix();
}
