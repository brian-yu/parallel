#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
//
#include <GL/glut.h>
//
#define N     750
//
//
//
//
int calcMandel(double x, double y, int lim)
{
    int i;
    int steps = 0;
    double a = 0;
    double b = 0;
    for (i=0; i < lim; i++) {
        steps++;
        double tmp_a = a*a - b*b +x;
        double tmp_b = 2*a*b + y;
        a = tmp_a;
        b = tmp_b;
        if ((a*a + b*b) > 4)
        {
            return steps;
        }
    }
    return -1;

}
void idlefunc()
{
}
/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18
*/
void displayfunc()
{
    double px, py;
    //
    //
    glClear(GL_COLOR_BUFFER_BIT); // white

    double MinRe = -2.0;
    double MaxRe = 2.0;
    double MinIm = -2.0;
    double MaxIm = MinRe+(MaxRe-MinRe)*N/N;
    double Re_factor = (MaxRe-MinRe)/(N);
    double Im_factor = (MaxIm-MinIm)/(N);
    int MaxIterations = 1000;

    for(int y=0; y<N; y++)
    {
        double c_im = MaxIm - y*Im_factor;
        for(int x=0; x<N; x++)
        {
            double c_re = MinRe + x*Re_factor;
            int steps = 0;
            double Z_re = c_re, Z_im = c_im;
            int blown = 0;
            for(int n=0; n<MaxIterations; n++)
            {
                steps++;
                double Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4)
                {
                    blown = 1;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if(blown == 0) {
                glColor3f( 0.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2f(x,y);
                glEnd();
            } else {
                glColor3f( 0.5, steps/MaxIterations * 1.0, 1.0);
                glBegin(GL_POINTS);
                glVertex2f(x,y);
                glEnd();
            }
        }
    }


    glutSwapBuffers(); // single buffering... call glFlush();

}
void reshapefunc(int wscr,int hscr)
{
    glViewport(0,0,(GLsizei)N,(GLsizei)N);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,1.0*N,0.0,1.0*N); // always a square
    glMatrixMode(GL_MODELVIEW);
}
void mousefunc(int button,int state,int xscr,int yscr)
{

}
void keyfunc(unsigned char key,int xscr,int yscr)
{
}
int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(N,N);
    glutInitWindowPosition(100,50);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,0.0);
    glShadeModel(GL_SMOOTH);



    glutIdleFunc(idlefunc);
    glutDisplayFunc(displayfunc);
    glutReshapeFunc(reshapefunc);
    glutMouseFunc(mousefunc);
    glutKeyboardFunc(keyfunc);
    //
    glutMainLoop();
    //
    return 0;
}
//
// end of file
//
