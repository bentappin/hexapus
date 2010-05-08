#include <math.h>			// for cos, sin etc

void draw_tetrahedron(int m);
void draw_circle(int faces);
void draw_sphere(float size);

/* 
 * The following, taken from E.Angel's "sphere" program, defines
 * the vertices of a tetrahedron lying in the unit sphere centered
 * at the origin. This is used to derive a globe.
 */

GLfloat v[][3] = {
        {0.0, 0.0, 1.0}, 
        {0.0, 0.942809, -0.33333},
        {-0.816497, -0.471405, -0.333333}, 
        {0.816497, -0.471405, -0.333333}   };

void draw_triangle( GLfloat a[], GLfloat b[], GLfloat c[]);
void normal(GLfloat p[]);
void divide_triangle( GLfloat a[], GLfloat b[], GLfloat c[], int m);
