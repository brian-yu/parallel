#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <complex.h>
//
#include <GL/glut.h>
//

#define H	1000
#define W	1920
#define R	50
#define C	96
#define N	20

int pause = 0;

int grid[R][C] = { 0 };



void displayfunc()
{
	for (int x=0; x<R; x++) {
		for (int y=0; y<C; y++) {
			glColor3f( 0.584 , 0.647 , 0.651 ) ;
			glBegin(GL_LINES);
				glVertex2f(x*N, x*N);
				glVertex2f(20, 20);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(10, 10);
				glVertex2f(20, 20);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(10, 10);
				glVertex2f(20, 20);
			glEnd();
			glBegin(GL_LINES);
				glVertex2f(10, 10);
				glVertex2f(20, 20);
			glEnd();
			if (grid[x][y] == 1) {
				int pass;
			} else {
				int pass;
			}
		}
	}
	
	glutSwapBuffers();
	
}
void idlefunc()
{
	
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
	if(button==GLUT_LEFT_BUTTON)
    {
		if(state==GLUT_DOWN)
        {
			int pass;
		}
	}
	else if(button==GLUT_RIGHT_BUTTON)
	{
		if(state==GLUT_DOWN)
		{
			int pass;
		}
	}
}
void keyfunc(unsigned char key,int xscr,int yscr)
{
	if( key == ' ' ) {
		pause = !pause ;
    }
    else if( key == 'q' )
    {
        exit( 0 ) ;
    }
}

int main(int argc, char * argv[]) {
	
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(H,W);
    glutInitWindowPosition(0,0);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,1.0);
    glShadeModel(GL_SMOOTH);
    //

    //
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
