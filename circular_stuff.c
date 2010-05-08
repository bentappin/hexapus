#include "circular_stuff.h"

void draw_circle(int faces)
{
	GLint i;
	GLfloat cosine, sine;
	GLfloat ffaces = (float)faces;

	glPushMatrix();
	glPushAttrib( GL_ALL_ATTRIB_BITS );
	glMaterialfv( GL_FRONT, GL_SPECULAR, specFact ); 
	glMaterialfv( GL_FRONT, GL_SHININESS, shininess );

	glBegin(GL_POLYGON);
		glNormal3f(0,1,0);
		for(i=0;i<ffaces;i++)
		{
			cosine=cos(i*2*PI/ffaces);
			sine=sin(i*2*PI/ffaces);
			glVertex3f(cosine,0, sine);
		}
	glEnd();
	glFlush();

	glPopAttrib();
	glPopMatrix();
}

/*
 * Pole drawing code adapted from Roy Ruddle's
 * gi31-light.cc which contains this notice
// Copyright (c) 1993-1997, Silicon Graphics, Inc.
// ALL RIGHTS RESERVED 
 *
 */
void draw_pole(GLfloat length)
{
	int l1, l2, num_facet = 12;
	GLfloat ang, col, yy = length;
	GLfloat cx = 0.0, cy = 1.5, cz = 5.0;

	for( l1=0; l1<num_facet; l1++ ) { // draw facetted cylinder
		glBegin (GL_TRIANGLE_STRIP);
		glPushAttrib( GL_ALL_ATTRIB_BITS );
		glMaterialfv( GL_FRONT, GL_SPECULAR, specFact ); 
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

void draw_sphere(float size)
{
	glPushMatrix();
		glScalef(size, size, size);
		tetrahedron(5);
	glPopMatrix();
}

void draw_base()
{
	glPushMatrix();
		glScalef(30,0.5,30);
		draw_circle(100);
	glFlush();
	glPopMatrix();
}

/* 
 * The following three procedures are from E. Angel's "sphere" program,
 * and calculate a sphere by recursive subdivision ...
 *
 * Taken and modified from David Duke's planets.c
 *
 * Colouring has been taken out.
 *
 */

void triangle( GLfloat a[], GLfloat b[], GLfloat c[])
{
	glBegin(GL_POLYGON);
		glNormal3fv(a);
		glVertex3fv(a);
		glNormal3fv(b); // added for smoother shading
		glVertex3fv(b);
		glNormal3fv(c); // added for smoother shading
		glVertex3fv(c);
	glEnd();
}

void normal(GLfloat p[]) {

    /* normalize a vector */

    double sqrt();
    float d =0.0;
    int i;
    
    for(i=0; i<3; i++) 
        d += p[i]*p[i];
    d=sqrt(d);
    if (d > 0.0) 
        for(i=0; i<3; i++) p[i]/=d;
}

void divide_triangle( GLfloat a[], GLfloat b[], GLfloat c[], int m)
{

    /* 
     * Triangle subdivision using vertex numbers.
     * Righthand rule applied to create outward pointing faces.
     * The parameter m is used to terminate subdivision.
     */

    GLfloat v1[3], v2[3], v3[3];
    int j;
    
    if (m>0) {
    
        for(j=0; j<3; j++) {
            v1[j] = a[j]+b[j];
        }
        normal(v1);
        for(j=0; j<3; j++) {
            v2[j] = a[j]+c[j];
        }
        normal(v2);
        for(j=0; j<3; j++) {
            v3[j] = b[j]+c[j];
        }
        normal(v3);    
            
        divide_triangle(a, v1, v2, m-1);
        divide_triangle(c, v2, v3, m-1);
        divide_triangle(b, v3, v1, m-1);
        divide_triangle(v1, v3, v2,m-1);
    }
    else
        triangle(a,b,c); /* draw triangle at end of recursion */
}

void tetrahedron( int m )
{

    
    /* Apply triangle subdivision to faces of tetrahedron */
    glPushMatrix();
    glPushAttrib( GL_ALL_ATTRIB_BITS );
    glMaterialfv( GL_FRONT, GL_SPECULAR, specFact ); 
    glMaterialfv( GL_FRONT, GL_SHININESS, shininess );
    divide_triangle(v[0], v[1], v[2], m-1);
    divide_triangle(v[3], v[2], v[1], m-1);
    divide_triangle(v[0], v[3], v[1], m-1);
    divide_triangle(v[0], v[2], v[3], m-1);
    glPopAttrib();
    glPopMatrix();
}
