#include <iostream>
#include <time.h>
#include <GL/glut.h>
#include <math.h>
#include <chrono>
#include <unistd.h>

void desenhaRetas();

int main(int argc, char *argv[])
{   
    /* code */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Retas");
    glutDisplayFunc(desenhaRetas);

    glutMainLoop();
    return 0;
}


void equacaoDaReta(int x1, int x2, int y1, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    float coeficienteAgunular = (float)dy/(float)dx;
    glVertex2i(x1, y1);
    for(float x = x1; x < x2; x++)
    {
        int dx2 = x - x1;
        float y = (coeficienteAgunular * (float)dx2) + (float)y1;
        glVertex2i(x, y);
    }
}

void DDA(int x1, int x2, int y1, int y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float tamanho = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xAlt = dx/tamanho;
    float yAlt = dy/tamanho;
    glVertex2i(x1, y1);

    for(float k = 1; k < tamanho; k++)
    {
        x1 += xAlt;
        y1 += yAlt;
        glVertex2i(x1,y1);
    }

}


void Bresenham(int x1, int x2, int y1, int y2)
{
    int dx, dy, x, y, xfinal, p, const1, const2;
    dx = fabs(x1 - x2); dy = fabs(y1 - y2);
    p = 2 * dy - dx; 
    const1 = 2 * dy;
    const2 = 2 * (dy - dx);
    if(x1 > x2)
    {
        x = x2;
        y = y2;
        xfinal = x1;
    }
    else
    {
        x = x1;
        y = y1;
        xfinal = x2;
    }
    glVertex2i(x,y);
    while(x < xfinal)
    {
        x++;
        if(p < 0)
        {
            p += const1;
        }
        else
        {
            y++;
            p += const2;
        }
        glVertex2i(x,y);
    }
    
}

void desenhaRetas()
{
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0.0,50.0,0.0,50.0);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
            auto start = std::chrono::steady_clock::now();
            glColor3d(1, 0, 0);
            equacaoDaReta(10, 20, 45, 35);
            auto endER = std::chrono::steady_clock::now();

            glColor3d(0, 1, 0);
            DDA(30, 40, 45, 35);
            auto endDDA = std::chrono::steady_clock::now();
            
            glColor3d(0, 0, 1);
            Bresenham(30, 20, 25, 15);
            auto endBresh = std::chrono::steady_clock::now();
    glEnd();
    
    std::cout << "Duracao Equacao da Reta : " << std::chrono::duration_cast<std::chrono::nanoseconds>(endER - start).count() << "ns";
    std::cout << "\nDuracao DDA : " << std::chrono::duration_cast<std::chrono::nanoseconds>(endDDA - endER).count() << "ns";
    std::cout << "\nDuracao Bresenham : " << std::chrono::duration_cast<std::chrono::nanoseconds>(endBresh - endDDA).count() << "ns";
    //std::cout << "\nENd";
    
    glBegin(GL_LINES);
        start = std::chrono::steady_clock::now();
        glColor3d(1, 1, 0);
        glVertex2i(5, 15);
        glVertex2i(10, 25);
        auto endBreshGL = std::chrono::steady_clock::now();
        std::cout << "\nDuracao Bresenham GL : " << std::chrono::duration_cast<std::chrono::nanoseconds>(endBreshGL - start).count() << "ns";
    glEnd();
    std::cout << "\nFIM";
    glFlush();
}


