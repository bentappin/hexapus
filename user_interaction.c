#include "user_interaction.h"

void keyboard(unsigned char key,int x,int y)
{
    key = tolower(key);
	if (key==27 || key=='q')
	    exit(1);	// Esc key or q exit.

	if (key=='s' && move_up==0)
	    move_up = 1;

	if (key=='t' && move_height>=POLE_EXTENSION)
		tilt = 1;

	if (key=='b' && tilt==1)
		tilt = 0;
	
	if (key=='e' && tilt==0 && tilt_ang<=0)
		end = 1;
}

void keyboard_special(int key, int x, int y)
{
	if (key==GLUT_KEY_DOWN)
		view_rotation_v -= 1;
	
	if (key==GLUT_KEY_UP)
		view_rotation_v += 1;

	if (key==GLUT_KEY_LEFT)
		view_rotation_h -= 1;
	
	if (key==GLUT_KEY_RIGHT)
		view_rotation_h += 1;

	view_rotation_v %= 360;
	view_rotation_h %= 360;
	glutPostRedisplay();
}
