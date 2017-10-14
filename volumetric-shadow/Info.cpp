#include <cstring>
#include <sstream>

#include "OpenGL.h"

#include "Info.h"
using namespace std;

/*	
void* bitmap_fonts[7] = {
GLUT_BITMAP_9_BY_15,
GLUT_BITMAP_8_BY_13,
GLUT_BITMAP_TIMES_ROMAN_10,
GLUT_BITMAP_TIMES_ROMAN_24,
GLUT_BITMAP_HELVETICA_10,
GLUT_BITMAP_HELVETICA_12,
GLUT_BITMAP_HELVETICA_18     
};
*/

Info::Info(void)
{
}

Info::~Info(void)
{
}

void Info::print_bitmap_string(char* str)
{
	if(str && strlen(str))
	{
		while(*str)
		{
			glutBitmapCharacter((void*)GLUT_BITMAP_9_BY_15, *str);
			str++;
		}
	}
}

void Info::infoOpenGl()
{
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf( "OpenGL Vendor :  %s\n", glGetString(GL_VENDOR));
	printf( "OpenGL Renderer: %s\n", glGetString(GL_RENDERER));
	char *ptr = (char*)glGetString(GL_VERSION);
	printf( "OpenGL Version:  %s\n", ptr);
}
