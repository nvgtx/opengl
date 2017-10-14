#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object
{
public:
	// vertex in 3d-coordinate system
	struct Vertex
	{
		float x, y, z;
	};

	// plane equation
	struct PlaneEquation
	{
		float a, b, c, d;
	};

	// structure describing an object's face
	struct Plane
	{
		unsigned int p[3];
		Vertex normals[3];
		unsigned int neighbours[3];
		PlaneEquation planeEquation;
		bool visible;
	};

	// object structure
	struct ObjectStructure
	{
		unsigned int numberPlanes, numberPoints;
		Vertex points[100];
		Plane planes[200];
	};

	float translatex,translatey,translatez;
	float d, l;
	bool dots;

	Object(void);
	~Object(void);

	ObjectStructure* obj;

	void init();

	void draw();
	bool init(ObjectStructure*);

	void calculatePlane(unsigned int);
	void calculateNeighbours();

	void translate(float x, float y, float z);

	void createXObject(int x=0, int y=0, int z=0);
	void createYObject(int x=0, int y=0, int z=0);
	void createZObject(int x=0, int y=0, int z=0);
	void createPObject();
};

#endif