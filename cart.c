#include "cart.h"

void draw_cart(float r, float g, float b)
{
	glPushMatrix();
	glRotatef(90,0,1,0);
	glTranslatef(0,0.1,0);

	glEnable(GL_COLOR_MATERIAL);
	glPushAttrib( GL_ALL_ATTRIB_BITS ); // stops our carts being shiny

	// Draw the carts base
	glBegin(GL_POLYGON);
		glColor3f(LTGRAY);
		glNormal3f(0,1,0);
		glVertex3f(-5.0,0.0,0.0);	// Vertex A
		glVertex3f(-2.0,0.0,-2.0);	// Vertex B
		glVertex3f(2.0,0.0,-2.0);	// Vertex C
		glVertex3f(5.0,0.0,0.0);	// Vertex D
		glVertex3f(2.0,0.0,2.0);	// Vertex E
		glVertex3f(-2.0,0.0,2.0);	// Vertex F
	glEnd();

	// Draw side 1 using 3 shapes
	// Right triangle
	glBegin(GL_POLYGON);
		glColor3f(r, g, b);
		glNormal3f(1,0,0);
		glVertex3f(2.0,0.0,-2.0);	// Vertex C
		glVertex3f(7.0,6.0,-4.0);	// Vertex G
		glVertex3f(2.0,6.0,-4.0);	// Vertex H

	glEnd();

	// Middle square	
	glBegin(GL_QUADS);
		glNormal3f(1,0,0);
		glColor3f(r, g, b);
		glVertex3f(2.0,0.0,-2.0);	// Vertex C
		glVertex3f(2,3,-3);		// Vertex I
		glVertex3f(-2,3,-3);		// Vertex J
		glVertex3f(-2,0,-2);		// Vertex B
	glEnd();

	// Left Triangle
	glBegin(GL_POLYGON);
		glNormal3f(1,0,0);
		glColor3f(r, g, b);
		glVertex3f(-2.0,0.0,-2.0);	// Vertex B
		glVertex3f(-7.0,6.0,-4.0);	// Vertex L
		glVertex3f(-2.0,6.0,-4.0);	// Vertex K
	glEnd();

	// End side 1

	// Draw funny sticky out thing to attach to right of side 1
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(2.0,0.0,-2.0);	// Vertex C
		glVertex3f(7.0,6.0,-4.0);	// Vertex G
		glVertex3f(8,6, 0);		// Vertex M
		glVertex3f(5.0,0.0,0.0);	// Vertex D
	glEnd();

	// Draw funny sticky out thing to attach to left of side 1
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(-2.0,0.0,-2.0);	// Vertex B
		glVertex3f(-7.0,6.0,-4.0);	// Vertex L
		glVertex3f(-8,6, 0);		// Vertex N
		glVertex3f(-5.0,0.0,0.0);	// Vertex A
	glEnd();

	// Draw side 2 out of 3 shapes
	// Left triangle
	glBegin(GL_POLYGON);
		glNormal3f(-1,0,0);
		glColor3f(r, g, b);
		glVertex3f(2.0,0.0,2.0);
		glVertex3f(7.0,6.0,4.0);
		glVertex3f(2.0,6.0,4.0);
	glEnd();

	// Middle square	
	glBegin(GL_QUADS);
		glNormal3f(-1,0,0);
		glColor3f(r, g, b);
		glVertex3f(2.0,0.0,2.0);
		glVertex3f(2,3,3);
		glVertex3f(-2,3,3);
		glVertex3f(-2,0,2);
	glEnd();

	// Right triangle
	glBegin(GL_POLYGON);
		glNormal3f(-1,0,0);
		glColor3f(r, g, b);
		glVertex3f(-2.0,0.0,2.0);
		glVertex3f(-7.0,6.0,4.0);
		glVertex3f(-2.0,6.0,4.0);
	glEnd();

	// End side 2


	// Draw funny sticky out thing to attach to right of side 2
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(2.0,0.0,2.0);
		glVertex3f(7.0,6.0,4.0);
		glVertex3f(8,6, 0);
		glVertex3f(5.0,0.0,0.0);
	glEnd();

	// Draw funny sticky out thing to attach to left of side 2
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(-2.0,0.0,2.0);
		glVertex3f(-7.0,6.0,4.0);
		glVertex3f(-8,6, 0);
		glVertex3f(-5.0,0.0,0.0);
	glEnd();
	glFlush();

	glPopAttrib();
	
	glPopMatrix();
}
