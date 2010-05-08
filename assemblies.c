#include "assemblies.h"

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
		glVertex3f(2,3,-3);		    // Vertex I
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
		glVertex3f(8,6, 0);		    // Vertex M
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

void draw_base(float r, float g, float b)
{
    glPushMatrix();
		glColor3f(r,g,b);
		glPushMatrix();
    		glScalef(30,0.5,30);
    		draw_circle(100);
    	glFlush();
    	glPopMatrix();
	glPopMatrix();
}

/*
 * Pole drawing code adapted from Roy Ruddle's
 * gi31-light.cc which contains this notice
 * Copyright (c) 1993-1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 */
void draw_pole(GLfloat length)
{
	int l1, l2, num_facet = 12;
	GLfloat ang, col, yy = length;
	GLfloat cx = 0.0, cy = 1.5, cz = 5.0;

	for( l1=0; l1<num_facet; l1++ ) { // draw facetted cylinder
		glBegin (GL_TRIANGLE_STRIP);
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glMaterialfv( GL_FRONT, GL_SPECULAR, spec_fact ); 
		glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

		// get the the angle at which the triangle will have
		ang = ((GLfloat) l1) / ((GLfloat) num_facet) * 2.0 * PI;
 
		for( l2=0; l2<2; l2++ ) // draw facet
		{
			glNormal3f(cos( ang ), 0.0, -sin( ang ));
			// calulate distant vertex
			glVertex3f(cos( ang ), yy, -sin( ang ));
			glVertex3f(cos( ang ), 0.0, -sin( ang ));
			ang = ((GLfloat) l1 + 1) / ((GLfloat) num_facet) * 2.0 * PI;
		}
		glEnd();
	}
	glPopAttrib();
	glFlush ();
}
