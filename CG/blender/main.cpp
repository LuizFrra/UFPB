#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include </usr/include/glm/vec3.hpp>
#include </usr/include/glm/vec2.hpp>
#include <string.h>
#include <GL/glext.h>
#include <GL/glx.h>

double angTerra = 0;

void DisplayF();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Solar System");
    glutDisplayFunc(DisplayF);
    glutIdleFunc(DisplayF); 
    /* code */
    
    glutMainLoop();

    return 0;
}

void DisplayF()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(-70, 70, -70, 70, 1, 70);
    glTranslated(0, 0, -2);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    gluLookAt(20, 30, 20, 0, 0, 0, 0, 0, 1);


    glColor3d(1, 1, 0);
    glTranslated(0, 0, 5);
    glutWireSphere(10, 500, 500);

    glRotated(angTerra, 0, 0, 1);
    glColor3d(0, 0, 1);
    glTranslated(-25, 0 , 5);
    glutWireSphere(6, 500, 500);

    glColor3d(1, 1, 1);
    glTranslated(-15, 0, 5);
    glutWireSphere(3, 500, 500);

    angTerra += 2.0;
    glFlush();
}

