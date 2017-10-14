#ifndef _WORLD_H_
#define _WORLD_H_

class World
{
private:
	float position[3];
public:
	World(void);
	~World(void);

	void init();
	void draw();
};

#endif