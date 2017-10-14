#ifndef _SHADOW_H_
#define _SHADOW_H_

class Shadow
{
public:
	Light* light;
	Object* object;

	Shadow(void);
	~Shadow(void);

	void init(Light*);
	void draw(Object*);
private:
	void drawShadow();
	void testShadow();
};

#endif