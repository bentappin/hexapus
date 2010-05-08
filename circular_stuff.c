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

void draw_sphere(float size)
{
	glPushMatrix();
		glScalef(size, size, size);
		draw_tetrahedron(5);
	glPopMatrix();
}

void draw_triangle( GLfloat a[], GLfloat b[], GLfloat c[])
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
    /* Normalize a vector.
     *
     * Taken from/based on code from E. Angel's "sphere".
     */

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
     *
     * Taken from/based on code from E. Angel's "sphere".
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
        draw_triangle(a,b,c); /* draw triangle at end of recursion */
}

void draw_tetrahedron( int m )
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
