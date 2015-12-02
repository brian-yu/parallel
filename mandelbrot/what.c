#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// 
#include <GL/glut.h>
// 
#define N     600
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
   double x, y, x1, y1;
   //
   //
   glClear(GL_COLOR_BUFFER_BIT); // white
   //
   for( x = 0 ; x < N ; x++ )
   {
      for( y = 0 ; y < N ; y++ )
      { 
         glColor3f( 0.0 , 0.0 , 0.0 ) ; // black
         glBegin(GL_POINTS);
         glVertex2f(x,y);
         glEnd();
      }
   }
   //
   //         glColor3f( 0.0 , 0.0 , 0.0 ) ; // black 
   //
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
