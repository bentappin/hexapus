/************************************************************************/
/* hex.c : Hex-a-Pus - Animated fairground ride				*/
/************************************************************************/
/* 
 * By Ben Tappin scs4brt@comp.leeds.ac.uk
 * For GI21 (David Duke) - Coursework 2
 *
 * Keys:
 *	ESC,q	Quits the program
 *	s	Starts the ride
 *	t	Tilt the ride out once started
 *	b	Brings the ride back in
 *	e	Stops the ride spinning and brings it back down
 *
 ************************************************************************/

#include <GL/glut.h>			// should be obvious really ;-)

#define SMALL_SPHERE	2.5			// standard sphere size
#define BIG_SPHERE	SMALL_SPHERE + 1.5	// larger sphere size
#define MAX_TILT	45.0

#define BIG_POLE	35.0		// length of the large pole
#define SMALL_POLE	BIG_POLE / 2.0	// length of the smaller poles
#define POLE_EXTENSION	15.0

#include "colour_materials.h"		// for predefined colour floats e.g., RED, WHITE etc
#include "cart.c"			// draws our cart
#include "circular_stuff.c"		// contains functions for circles, spheres, cylinders

float ani_ang = 0.0;	// animation angle
float ani_inc = 0.8; 	// animation increment
float ani_ang2 = 0.0;	// for the inner arm and cart rotations
float ani_inc2 = 0.6; 	// animation increment for inner arms

#include "user_interaction.c"		// sorts out all the button presses

void draw_moveable()
{
	
	// draw sphere on top of pole
	glPushMatrix();
		glTranslatef(0.0, BIG_POLE, 0.0);
		glColor3f(RED);
		draw_sphere(BIG_SPHERE);
	glPopMatrix();

	int i;
	for(i = 0; i < 360; i += 120) // loops 3 times, increasing rotation each time ...
	{
		glPushMatrix();
			glRotatef(i, 0.0, 1.0, 0.0); // ... a third of the way round
			
			glTranslatef(0.0, BIG_POLE, 0.0); // to the top of the centre pole

			// horizontal pole
			glRotatef(180, 1.0, 1.0, 0.0); 			// flip so we're horizontal
			glTranslatef(0.0, -SMALL_POLE, 0.0); 	// move half the length of the pole out
			glColor3f(WHITE);
			draw_pole(SMALL_POLE); 		// draw a small pole
			
			glColor3f(RED);
			draw_sphere(SMALL_SPHERE);		// draw a sphere at the end of it
		
			// if the tilt key has been pressed lets tilt the thing!	
			if (tilt == 1)
			{
				if (tilt_ang < MAX_TILT)
					tilt_ang += 0.25;
				
				glRotatef(tilt_ang, 0.0, 0.0, 1.0);
			}
			else
			{
				if (tilt_ang >= 0.0)
					tilt_ang -=  0.25;
				
				glRotatef(tilt_ang, 0.0, 0.0, 1.0);
			}
						
			glRotatef(180.0, 1.0, 1.0, 0.0); 	// flip so we're vertical again
			glTranslatef(0.0, -SMALL_POLE, 0.0); 	// move half the length of the pole out/down/whatever :S
			glColor3f(WHITE);
			draw_pole(SMALL_POLE); 			// draw a small pole

			glColor3f(RED);
			draw_sphere(SMALL_SPHERE);		// draw a sphere at the end of it

			// now to draw horizontal arms at the, then vertical arms to the carts
			// and rotate them if we're ready
			
			glRotatef(180.0, 1.0, 1.0, 0.0); 	// flip so we're horizontal again
			glRotatef(90.0, 1.0, 0.0, 0.0); 	// rotate to align with carts

			if (move_height >= POLE_EXTENSION && end == 0)	// ok, definately already moved the assembly up now
			{
				ani_ang2 += ani_inc2;
				if (easter == 1)
					glRotatef(ani_ang2, 0.0, 1.0, 0.0);	// animate ...
				else
					glRotatef(ani_ang2, 1.0, 0.0, 0.0);	// animate ...
			}
			
			glTranslatef(0.0, SMALL_POLE/2.0, 0.0); // translate back a bit
			glColor3f(RED);
			draw_sphere(SMALL_SPHERE);		// draw sphere
			glTranslatef(0.0, -SMALL_POLE/2.0, 0.0);// return to old position
			
			glTranslatef(0.0, -SMALL_POLE/2.0, 0.0);// move half the length of the pole out
			glColor3f(WHITE);
			draw_pole(SMALL_POLE); 			// draw a small pole

			glColor3f(RED);
			draw_sphere(SMALL_SPHERE);		// draw sphere

			glRotatef(180 ,1.0, 1.0 ,0.015); 	// rotate to align with carts
			glTranslatef(0.0, -SMALL_POLE, 0.0);
			glColor3f(WHITE);
			draw_pole(SMALL_POLE); 			// draw a small pole
			
			// colour each cart differently
			switch (i)
			{
				case 0:
					draw_cart(RED);
					break;
		
				case 120:
					draw_cart(GREEN);
					break;

				case 240:
					draw_cart(DKBLUE);
					break; 
			}

			glTranslatef(SMALL_POLE, 0.0, 0.0);	// move half the length of the pole out
			glColor3f(WHITE);
			draw_pole(SMALL_POLE); 			// draw a small pole

			// colour each cart differently
			switch (i)
			{
				case 0:
					draw_cart(CYAN);
					break;
		
				case 120:
					draw_cart(DKRED);
					break;

				case 240:
					draw_cart(DKMAGENTA);
					break; 
			}
			
		glPopMatrix();
	} // end for
}

/*
 * METHOD: display
 * The display callback: anything to be drawn goes in here.
 */
void display()
{
	/*
	 * begin by clearing out the buffers needed to render the model.
	 */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glRotatef( rotate_angle_v, 1.0, 0.0, 0.0 );
	glRotatef( rotate_angle_h, 0.0, 1.0, 0.0 );

	glPushMatrix();

	// draw main pole
	glPushMatrix();
		glColor3f(WHITE);
		glScalef(1.6,1.0,1.6);	// Make pole fatter
		draw_pole(BIG_POLE+POLE_EXTENSION);
	glPopMatrix();

	if (move_up == 1) // indicate we want to move part of the assembly up to the top of the pole
	{
		if (move_height >= POLE_EXTENSION)
			move_up = 0;
		else
		{
			move_height += 0.25;
			glTranslatef(0.0,move_height,0.0);
			draw_moveable();
		}
	}
	else // we're at the top of the pole or in the starting position
	{
		if (move_height >= POLE_EXTENSION && end == 0) // ok, definately already moved the assembly up now
		{
			ani_ang += ani_inc;			// increase rotate variable
								
			glRotatef(ani_ang,0.0,1,0.0);		// animate ...
			glTranslatef(0.0,move_height,0.0);  	// ... at full height ...
			draw_moveable();			// ... these components
		}
		else // still in start position, or moving the ride down again
			if (end == 1)
			{
				if (move_height <= 0.0) // if we've already at the bottom lets not loop another time
					end = 0;
				
				move_height -= 0.25;
				glTranslatef(0.0,move_height,0.0); 
				draw_moveable();
			}
			else
				draw_moveable();
	}

	glPopMatrix(); // we do not want the base to spin

	// draw ride base
	glPushMatrix();
		glColor3f(DKGREEN);
		draw_base();
	glPopMatrix();

	// needed when using double buffering
	glutSwapBuffers();
}

/*
 * METHOD: reshape
 * The reshape callback: called when window is resized
 * and when the program is first run.
 */
void reshape(int w, int h)
{
	// sets what's been viewed relative to the bottom left corner
	glViewport(0.0, 0.0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(105.0, (GLfloat)w/(GLfloat)h, 0.1, 120.0);
	glTranslatef(0.0, 0.0, -50.0);

	gluLookAt( 	0.0, 20.0, -10.0,	// eye
			0.0, 16.0, 0.0,		// at
			0.0, 1.0 , 0.0);	// up

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(900, 700);

	glutCreateWindow("Hex-a-Pus");

	glutReshapeFunc(reshape);		// window resizes and program initilisation
	glutDisplayFunc(display);		// let's draw some stuff :-)
	glutSpecialFunc(keyboard_special);	// for the arrow keys
	glutKeyboardFunc(keyboard);		// for other key presses
	glutIdleFunc(display);			// used for animation!

	/*
	 * Since we are going to scale the geometry of some objects,
	 * the normal vectors used for lighting effects will need to
	 * be recalculated.  This is something for GL to do.
	 */
	glEnable( GL_NORMALIZE );

	glEnable( GL_DEPTH_TEST );
	
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );

//	glEnable ( GL_COLOR_MATERIAL );
//	glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );

	// Create light components
	GLfloat ambientLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
//	GLfloat position[] = { -20.0f, 50.0f, -30.0f, 1.0f };
	GLfloat position[] = { -10.0f, 40.0f, -10.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glutMainLoop();
}
