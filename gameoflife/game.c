#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
#include <GL/glut.h>
//

#define H	800
#define W	1500
#define R	40
#define C	75
#define N	20

int pause = 0;
int grid[R*C] = { 0 };


int neighbors[8] = {C, C+1, C-1, 1, -1, -C, -C-1, -C+1};

int neighborCount(int pos) {
    int count = 0;
    for (int i=0; i < 8; i++) {
        int nPos = pos + neighbors[i];
        int nRow = nPos / C;
        int nCol = nPos % C;
        int row = pos / C;
        int col = pos % C;
        if (nPos > 0 && nPos < 64 && abs(row-nRow) == 1 && abs(col-nCol) == 1) {
            if(grid[nPos] == 1) {
                count++;
            }
        }
    }
    return count;
}

void displayfunc()
{
    glClear(GL_COLOR_BUFFER_BIT); // white
    glColor3f( 0.0 , 0.0 , 0.0 ) ;


    for(int i=0; i<R*C; i++) {
        if (grid[i] == 1) {
            int row = i / C;
            int col = i % C;
            glBegin(GL_POLYGON);
            glVertex2f(row,col);
            glVertex2f(row+N,col);
            glVertex2f(row+N,col+N);
            glVertex2f(row,col+N);
            glEnd();
        }
    }

    glutSwapBuffers();

}
void idlefunc()
{
    if( pause ) return ;

    for (int i = 0; i < R*C; i++) {
        int nCount = neighborCount(i);
        if (grid[i] == 1) {
            if (nCount < 2) {
                grid[i] = 0;
            } else if (nCount < 4) {
                grid[i] = 1;
            } else {
                grid[i] = 0;
            }
        } else if (nCount == 3) {
            grid[i] = 1;
        }
    }

    glutPostRedisplay();

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
            int r = yscr / N;
            int c = xscr / N;
            grid[r * c] = 1;
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
    else if (key == 'd') {
        displayfunc();
    }
}

int main(int argc, char * argv[]) {

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(0,0);
    glutCreateWindow("");
    glClearColor(1.0,1.0,1.0,1.0);
    glShadeModel(GL_SMOOTH);
    //
    grid[1] = 1;
    grid[2] = 1;
    grid[76] = 1;
    grid[77] = 1;

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
