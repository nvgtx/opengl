#include <stdlib.h>
#include <stdio.h>

#include "OpenGL.h"

#include "Object.h"

Object::Object(void)
{
}

Object::~Object(void)
{
}

void Object::init()
{
	translatex=0;
	translatey=0;
	translatez=0;
	d=0.1;
	l=2;
	dots=false;
}

bool Object::init(ObjectStructure* obj)
{
	this->obj=obj;
	obj->numberPoints=0;
	obj->numberPlanes=0;

	createXObject(0, -l, -l);
	createXObject(0, +l, -l);
	createXObject(0, -l, +l);
	createXObject(0, +l, +l);

	createYObject(-l, 0, -l);
	createYObject(+l, 0, -l);
	createYObject(-l, 0, +l);
	createYObject(+l, 0, +l);

	createZObject(-l, -l, 0);
	createZObject(-l, +l, 0);
	createZObject(+l, -l, 0);
	createZObject(+l, +l, 0);

	translate(translatex, translatey, translatez);

	calculateNeighbours();
	for(unsigned int i=0; i<obj->numberPlanes; i++)
	{
		calculatePlane(i);
	}
	return true;
}


void Object::createXObject(int x, int y, int z)
{	
	float l=this->l+d;
	unsigned int p=obj->numberPoints;

	obj->points[p].x=-l;
	obj->points[p].y=d;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=l;
	obj->points[p].y=d;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=l;
	obj->points[p].y=d;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-l;
	obj->points[p].y=d;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-l;
	obj->points[p].y=-d;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=l;
	obj->points[p].y=-d;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=l;
	obj->points[p].y=-d;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-l;
	obj->points[p].y=-d;
	obj->points[p].z=d;
	p++;

	for(unsigned int i=obj->numberPoints; i<p; i++)
	{
		obj->points[i].x+=x; 
		obj->points[i].y+=y;
		obj->points[i].z+=z;
	}

	createPObject();
	obj->numberPoints=p;
}

void Object::createYObject(int x, int y, int z)
{	
	float l=this->l+d;
	unsigned int p=obj->numberPoints;

	obj->points[p].x=-d;
	obj->points[p].y=l;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=l;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=l;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=l;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=-l;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=-l;
	obj->points[p].z=-d;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=-l;
	obj->points[p].z=d;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=-l;
	obj->points[p].z=d;
	p++;

	for(unsigned int i=obj->numberPoints; i<p; i++)
	{
		obj->points[i].x+=x; 
		obj->points[i].y+=y;
		obj->points[i].z+=z;
	}

	createPObject();
	obj->numberPoints=p;
}

void Object::createZObject(int x, int y, int z)
{
	float l=this->l+d;
	unsigned int p=obj->numberPoints;

	obj->points[p].x=-d;
	obj->points[p].y=d;
	obj->points[p].z=-l;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=d;
	obj->points[p].z=-l;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=d;
	obj->points[p].z=l;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=d;
	obj->points[p].z=l;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=-d;
	obj->points[p].z=-l;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=-d;
	obj->points[p].z=-l;
	p++;
	obj->points[p].x=d;
	obj->points[p].y=-d;
	obj->points[p].z=l;
	p++;
	obj->points[p].x=-d;
	obj->points[p].y=-d;
	obj->points[p].z=l;
	p++;

	for(unsigned int i=obj->numberPoints; i<p; i++)
	{
		obj->points[i].x+=x; 
		obj->points[i].y+=y;
		obj->points[i].z+=z;
	}

	createPObject();
	obj->numberPoints=p;
}



void Object::createPObject()
{
	unsigned int orgp=obj->numberPoints;
	unsigned int n=obj->numberPlanes;
	orgp-=1;

	obj->planes[n].p[0]=orgp+1;
	obj->planes[n].p[1]=orgp+3;
	obj->planes[n].p[2]=orgp+2;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=1;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=1;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=1;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+1;
	obj->planes[n].p[1]=orgp+4;
	obj->planes[n].p[2]=orgp+3;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=1;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=1;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=1;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+6;
	obj->planes[n].p[2]=orgp+7;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=-1;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=-1;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=-1;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+7;
	obj->planes[n].p[2]=orgp+8;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=-1;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=-1;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=-1;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+4;
	obj->planes[n].p[2]=orgp+1;
	obj->planes[n].normals[0].x=-1;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=-1;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=-1;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+8;
	obj->planes[n].p[2]=orgp+4;
	obj->planes[n].normals[0].x=-1;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=-1;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=-1;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+3;
	obj->planes[n].p[1]=orgp+6;
	obj->planes[n].p[2]=orgp+2;
	obj->planes[n].normals[0].x=1;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=1;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=1;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+3;
	obj->planes[n].p[1]=orgp+7;
	obj->planes[n].p[2]=orgp+6;
	obj->planes[n].normals[0].x=1;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=0;
	obj->planes[n].normals[1].x=1;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=0;
	obj->planes[n].normals[2].x=1;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=0;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+1;
	obj->planes[n].p[2]=orgp+2;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=-1;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=-1;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=-1;
	n++;

	obj->planes[n].p[0]=orgp+5;
	obj->planes[n].p[1]=orgp+2;
	obj->planes[n].p[2]=orgp+6;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=-1;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=-1;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=-1;
	n++;

	obj->planes[n].p[0]=orgp+3;
	obj->planes[n].p[1]=orgp+4;
	obj->planes[n].p[2]=orgp+8;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=1;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=1;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=1;
	n++;

	obj->planes[n].p[0]=orgp+3;
	obj->planes[n].p[1]=orgp+8;
	obj->planes[n].p[2]=orgp+7;
	obj->planes[n].normals[0].x=0;
	obj->planes[n].normals[0].y=0;
	obj->planes[n].normals[0].z=1;
	obj->planes[n].normals[1].x=0;
	obj->planes[n].normals[1].y=0;
	obj->planes[n].normals[1].z=1;
	obj->planes[n].normals[2].x=0;
	obj->planes[n].normals[2].y=0;
	obj->planes[n].normals[2].z=1;
	n++;

	obj->numberPlanes=n;
}


void Object::translate(float x, float y, float z)
{
	for(unsigned int i=0; i<obj->numberPoints; i++)
	{

		obj->points[i].x+=x; 
		obj->points[i].y+=y;
		obj->points[i].z+=z;
	}
}

void Object::draw()
{
	unsigned int i, j;

	for(i=0; i<obj->numberPoints && dots==true; i++)
	{
		glPushMatrix();
		glTranslatef(
			obj->points[i].x, 
			obj->points[i].y, 
			obj->points[i].z);
		//Draw sphere
		glColor3f(1, 0, 0);

		glDisable(GL_LIGHTING);
	//	glutSolidSphere(0.05, 32, 32);
		glEnable(GL_LIGHTING);

		glPopMatrix();
	}

	glBegin(GL_TRIANGLES);
	for(i=0; i<obj->numberPlanes; i++)
	{
		for(j=0; j<3; j++)
		{
			glNormal3f(
				obj->planes[i].normals[j].x, 
				obj->planes[i].normals[j].y, 
				obj->planes[i].normals[j].z);

			glVertex3f(
				obj->points[obj->planes[i].p[j]].x, 
				obj->points[obj->planes[i].p[j]].y, 
				obj->points[obj->planes[i].p[j]].z);
		}
	}
	glEnd();

}

void Object::calculateNeighbours()
{
	long vertexA1, vertexB1, vertexA2, vertexB2;
	long P1i, P2i, P1j, P2j;

	for(long i=0; i<obj->numberPlanes-1; i++)
	{
		for(long j=i+1; j<obj->numberPlanes; j++)
		{
			for(long k=0; k<3; k++)
			{
				if(!obj->planes[i].neighbours[k])
				{
					for(long l=0; l<3; l++)
					{
						vertexA1=k;
						vertexA2=l;
						vertexB1=(k+1)%3;
						vertexB2=(l+1)%3;

						vertexA1=obj->planes[i].p[vertexA1];
						vertexB1=obj->planes[i].p[vertexB1];
						vertexA2=obj->planes[j].p[vertexA2];
						vertexB2=obj->planes[j].p[vertexB2];

						P1i=((vertexA1+vertexB1)-abs(vertexA1-vertexB1))/2;
						P2i=((vertexA1+vertexB1)+abs(vertexA1-vertexB1))/2;
						P1j=((vertexA2+vertexB2)-abs(vertexA2-vertexB2))/2;
						P2j=((vertexA2+vertexB2)+abs(vertexA2-vertexB2))/2;

						if((P1i==P1j) && (P2i==P2j))
						{ 
							//they are neighbours
							obj->planes[i].neighbours[k]=j+1;	  
							obj->planes[j].neighbours[l]=i+1;	  
						}
					}
				}
			}
		}
	}
}



// function for computing a plane equation given 3 points
void Object::calculatePlane(unsigned int planeindex)
{
	Plane* plane=&(obj->planes[planeindex]);
	Vertex v[4];
	unsigned int i;

	for(i=0; i<3; i++)
	{
		v[i+1].x=obj->points[plane->p[i]].x;
		v[i+1].y=obj->points[plane->p[i]].y;
		v[i+1].z=obj->points[plane->p[i]].z;
	}

	plane->planeEquation.a=v[1].y*(v[2].z-v[3].z) + v[2].y*(v[3].z-v[1].z) + v[3].y*(v[1].z-v[2].z);
	plane->planeEquation.b=v[1].z*(v[2].x-v[3].x) + v[2].z*(v[3].x-v[1].x) + v[3].z*(v[1].x-v[2].x);
	plane->planeEquation.c=v[1].x*(v[2].y-v[3].y) + v[2].x*(v[3].y-v[1].y) + v[3].x*(v[1].y-v[2].y);
	plane->planeEquation.d=
		-(v[1].x*(v[2].y*v[3].z - v[3].y*v[2].z) +
		v[2].x*(v[3].y*v[1].z - v[1].y*v[3].z) +
		v[3].x*(v[1].y*v[2].z - v[2].y*v[1].z));
}

