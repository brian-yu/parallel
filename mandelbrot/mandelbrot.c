#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
// 
#include <GL/glut.h>
// 
#define N     1000
// 
// 
// 
// 
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
   int x, y;
   //
   //
   glClear(GL_COLOR_BUFFER_BIT); // white
   //
   for( x = 0 ; x < N ; x++ )
   {
      for( y = 0 ; y < N ; y++ )
      {
         double a = 0.0;
         double b = 0.0;
         double x0 = (((double)x)/N)*(2.5+2.5)-2.5;
         double y0 = (((double)y)/N)*(1.5+1.5)-1.5;
         int i = 0;
         int max = 100;
         int steps = 0;
         for (i=0; i < max; i++) {
            if (a*a + b*b >= 2*2) {
                break;
            }
            else {
               // double temp = (a+b)*(a+b) + x0;
               double temp = a*a - b*b + x0;
               b = 2*a*b + y0;
               a = temp; 
            }
         }
         
         if (i == max) {
            glColor3f( 0.0, 0.0, 0.0);
         }
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
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
