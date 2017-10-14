#ifndef _LIGHT_H_
#define _LIGHT_H_

class Light
{
private:
	float lightColor[4];
	float position[4];
	float maxPosition; 
public:
	Light(void);
	~Light(void);

	void init();
	void draw();

	void setPosX(float);
	void setPosY(float);
	void setPosZ(float);

	float getPosX();
	float getPosY();
	float getPosZ();
	float getPositioned();

	float getColorR();
	float getColorG();
	float getColorB();
	float getColorA();
};

#endif