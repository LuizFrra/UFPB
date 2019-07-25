#include "GL/glut.h"

void display();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Planos");
    glutDisplayFunc(display);
    /* code */
    glutMainLoop();
    return 0;
}


void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glOrtho(-50, 50, -50, 50, 1, 50);
    glTranslated(0, 0, -2);
    //gluLookAt(50, 50, 50, 50, 1, 50, 0, 1, 0);
    gluLookAt(20, 30, 20, 0, 0, 0, 0, 0, 1);
    glutWireCube(5);
    
    glBegin(GL_LINES);
        glColor3d(1, 0, 1); // Y
        glVertex3d(0, 0, 0);
        glVertex3d(0, 45, 0);

        glColor3d(0, 1, 0); // X
        glVertex3d(0, 0, 0);
        glVertex3d(45, 0, 0);

        glColor3d(0, 1, 1); // Z
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, 45);
    glEnd();
    
    glFlush();
}