#include "user_interaction.h"

void keyboard(unsigned char key,int x,int y)
{
	if (key==27 || key=='q') exit(1);	// Esc key or q exits

	if (key=='s')		// start the machine
		if (move_up == 0)
			move_up = 1;

	if (key=='t')
		if (move_height >= POLE_EXTENSION)
			tilt = 1;

	if (key=='b')
		if (tilt == 1)
			tilt = 0;
	
	if (key=='e')
		if (tilt == 0 && tilt_ang <= 0)
			end = 1;

	if (key=='x')
		if (easter == 0)
			easter = 1;
		else
			easter = 0;
}

void keyboard_special(int key, int x, int y)
{
	if (key==GLUT_KEY_DOWN)
	{
		rotate_angle_v -= 1;// increment the rotation angle by 1 degree
	}
	
	if (key==GLUT_KEY_UP)
	{
		rotate_angle_v += 1;// increment the rotation angle by 1 degree
	}

	if (key==GLUT_KEY_LEFT)
	{
		rotate_angle_h -= 1;// increment the rotation angle by 1 degree
	}
	
	if (key==GLUT_KEY_RIGHT)
	{
		rotate_angle_h += 1;// increment the rotation angle by 1 degree
	}


	rotate_angle_v %= 360;		// ... and keep it within 0-359
	rotate_angle_h %= 360;		// ... and keep it within 0-359
	glutPostRedisplay();
}
