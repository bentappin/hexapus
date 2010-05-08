#include <math.h>			// for cos, sin etc

void tetrahedron(int m);
void drawCircle(int faces);
void drawSphere(float size);

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

void triangle( GLfloat a[], GLfloat b[], GLfloat c[]);
void normal(GLfloat p[]);
void divideTriangle( GLfloat a[], GLfloat b[], GLfloat c[], int m);
