#include <GL/glut.h>

double angTerra = 0;
double angLua = 0;

void Draw(void) 
{ 
	
	glClearColor(0.0, 0.0, 0.0, 0.0); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Olho Esquerdo, Azul
			glColorMask(0, 0, 1, 0);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0);
			
			glViewport(0, 0, 400, 400); 
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity();
			glTranslated(0.0, 0.0, -40.0 );
			glRotatef(90, 1.0, 0.0, 0.0);
	
			glPushMatrix(); 
			glColor3f (1.0, 1.0, 1.0);
			glutWireSphere(0.2, 20, 20);
			glRotatef(angTerra, 0.0, 0.0, 1.0); 
			glTranslatef(0.5, 0.0, 0.0); 

			glutWireSphere(0.1, 10, 10);
			glPopMatrix();
			glPushMatrix(); 
			glRotatef(angLua, 0.0, 0.0, 1.0); 
			glTranslatef(0.75, 0.0, 0.0); 

			glutWireSphere(0.1, 10, 10);
			
		// Olho direito, Vermelho
			glColorMask(1, 0, 0, 0);
			glMatrixMode (GL_MODELVIEW);
			glLoadIdentity();
			glTranslated(0.0, 0.0, -40.0 );
			glRotatef(4, 0.0, 1.0, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
			
			glPushMatrix(); 
			glColor3f (1.0, 1.0, 0.0); 
			glutWireSphere(0.2, 20, 20);
			glRotatef(angTerra, 0.0, 0.0, 1.0); 
			glTranslatef(0.5, 0.0, 0.0); 

			glutWireSphere(0.1, 10, 10);
			glPopMatrix();
			glPushMatrix(); 
			glRotatef(angLua, 0.0, 0.0, 1.0); 
			glTranslatef(0.75, 0.0, 0.0); 

			glutWireSphere(0.1, 10, 10);
			glColorMask(1, 1, 1, 0);
			glClearColor(0.0, 0.0, 0.0, 0.0);

	glFlush(); 	
} 


void Girar(unsigned char key, int x, int y) 
{ 
	if((key == 'g')||(key == 'G')) 
	{ 
		angTerra += 2.0;
		angLua += 2.0;
	
		if(angTerra >= 360) 
			angTerra = 0.0;  
	}
} 

int main(int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH); 
	glutInitWindowSize(400,400); 
	glutCreateWindow("Solar System"); 
	glutKeyboardFunc(Girar); 
	glutDisplayFunc(Draw); 
    glutIdleFunc(Draw);
	glutMainLoop(); 
	return 0; 
}