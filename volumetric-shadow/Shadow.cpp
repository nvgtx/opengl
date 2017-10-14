#include "OpenGL.h"

#include "Light.h"
#include "Object.h"
#include "Shadow.h"

Object::ObjectStructure obj;

Shadow::Shadow(void)
{
}

Shadow::~Shadow(void)
{
}

void Shadow::init(Light* light)
{	
	this->light=light;
}

void Shadow::draw(Object* object)
{
	this->object=object;

	glClear(GL_STENCIL_BUFFER_BIT);
	object->init(&obj);

	glPushMatrix();
	object->draw();
	drawShadow();
	glPopMatrix();
}

void Shadow::drawShadow()
{	
	float side;

	//for all planes
	for(unsigned int i=0; i<obj.numberPlanes; i++)
	{
		// is the light in front or behind the plane
		side=obj.planes[i].planeEquation.a * light->getPosX() +
			obj.planes[i].planeEquation.b * light->getPosY() +
			obj.planes[i].planeEquation.c * light->getPosZ() +
			obj.planes[i].planeEquation.d * light->getPositioned();
		if(side > 0) 
		{
			//in light
			obj.planes[i].visible=true;
		}
		else 
		{
			//not in light
			obj.planes[i].visible=false;
		}
	}

	//disable light
	glDisable(GL_LIGHTING);
	//disable depth-buffer
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	//enable test of stencil-buffer
	glEnable(GL_STENCIL_TEST);
	//disable color-buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	// first pass
	glFrontFace(GL_CCW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);//increase value of z
	testShadow();

	// second pass
	glFrontFace(GL_CW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);//decrease value of z
	testShadow();

	//enable color-buffer
	glFrontFace(GL_CCW);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	
	//color of shadow (0,0,0 = black)
	glColor4f(0.0, 0.0, 0.0, 0.4);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//draw a rectangle for shadow
	glPushMatrix();
	glLoadIdentity();
	
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-0.1, 0.1, -0.10);
	glVertex3f(-0.1, -0.1, -0.10);
	glVertex3f( 0.1, 0.1, -0.10);
	glVertex3f( 0.1, -0.1, -0.10);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glDisable(GL_STENCIL_TEST);
	glShadeModel(GL_SMOOTH);
}

void Shadow::testShadow()
{
	unsigned int k;
	unsigned int p1, p2;
	Object::Vertex v1, v2;

	unsigned int maxdistance=100;

	//for all planes
	for(unsigned int i=0; i<obj.numberPlanes; i++)
	{
		//which are in light
		if(obj.planes[i].visible)
		{
			//for all points of a plane
			for(unsigned int j=0; j<3; j++)
			{
				//get neighbours of current plane
				k=obj.planes[i].neighbours[j];

				if((!k) || (obj.planes[k-1].visible==false))
				{
					// get points
					p1=obj.planes[i].p[j];
					p2=obj.planes[i].p[(j+1)%3];

					//calculate the length of the vector
					v1.x=(obj.points[p1].x - light->getPosX())*maxdistance;
					v1.y=(obj.points[p1].y - light->getPosY())*maxdistance;
					v1.z=(obj.points[p1].z - light->getPosZ())*maxdistance;

					v2.x=(obj.points[p2].x - light->getPosX())*maxdistance;
					v2.y=(obj.points[p2].y - light->getPosY())*maxdistance;
					v2.z=(obj.points[p2].z - light->getPosZ())*maxdistance;

					//draw the polygon
					glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(obj.points[p1].x, 
						obj.points[p1].y, 
						obj.points[p1].z);
					glVertex3f(obj.points[p1].x + v1.x, 
						obj.points[p1].y + v1.y, 
						obj.points[p1].z + v1.z);

					glVertex3f(obj.points[p2].x, 
						obj.points[p2].y, 
						obj.points[p2].z);
					glVertex3f(obj.points[p2].x + v2.x, 
						obj.points[p2].y + v2.y, 
						obj.points[p2].z + v2.z);
					glEnd();
				}
			}
		}
	}
}
