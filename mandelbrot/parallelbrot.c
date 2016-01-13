// 
// Torbert, 27 October 2014
// 
// MPI Demo
//    mpicc mpiDemo.c
//    mpirun -np 4 a.out
// 
// Manager-Worker model for parallel processing.
// 
// time ... real ... user 
// 
// htop 
// 
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <complex.h>
//
#include <GL/glut.h>
// 
#include "mpi.h"
// 
//
#define N 750

int max = 25;
double minReal = -2.0;
double maxReal = 2.0;
double minImag = -2.0;
double maxImag = 2.0;

//
// MPI variables
//
int rank;
int size;
MPI_Status status;
int tag = 0;
//
//
void idlefunc() {}
/*
GLUT_BITMAP_8_BY_13
GLUT_BITMAP_9_BY_15
GLUT_BITMAP_TIMES_ROMAN_10
GLUT_BITMAP_TIMES_ROMAN_24
GLUT_BITMAP_HELVETICA_10
GLUT_BITMAP_HELVETICA_12
GLUT_BITMAP_HELVETICA_18
*/
void displayfunc() {

    int j, x;
    int col = 0;
    int terminate = -1;
    int result;
    //
    // manager has rank = 0
    //
    if (rank == 0) {
        printf("Im Mr. Manager\n");
        for (int i = 1; i < size; i++) {
			printf("%d\n", col);
            MPI_Send( &col, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
            col += 1;
        }
        printf("!!\n");
        while (col < N) {
            printf("b%d\n", col);
            MPI_Recv( &result, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
			printf("a%d\n", col);
            j = status.MPI_SOURCE;

            MPI_Send( &col, 1, MPI_INT, j, tag, MPI_COMM_WORLD);
            col++;
        }
        printf("!!!\n");
        for (int k = 1; k < size; k++) {
            MPI_Recv( &result, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            //
            j = status.MPI_SOURCE;
            //
            MPI_Send( &terminate, 1, MPI_INT, j, tag, MPI_COMM_WORLD);
        }

        glutSwapBuffers(); //
    }
    //
    // workers have rank > 0
    //
    else {
        while (1) {

            MPI_Recv( &x, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
            printf("%d\n", x);
            if (x < 0) {
                break;
            }
            //
            //
            double px, py;
            //
            //
            glClear(GL_COLOR_BUFFER_BIT); // white

            double realScale = (maxReal - minReal) / (N);
            double imagScale = (maxImag - minImag) / (N);

            for (int y = 0; y < N; y++) {
                double cImag = maxImag - y * imagScale;
                double cReal = minReal + x * realScale;
                int steps = 0;
                double zReal = cReal, zImag = cImag;
                int blown = 0;
                for (int n = 0; n < max; n++) {
                    steps++;
                    double zReal2 = zReal * zReal, zImag2 = zImag * zImag;
                    if (zReal2 + zImag2 > 4) {
                        blown = 1;
                        break;
                    }
                    zImag = 2 * zReal * zImag + cImag;
                    zReal = zReal2 - zImag2 + cReal;
                }
                if (blown == 0) {
                    glColor3f(0.3039, 0.69608, 0.95882);
                } else {
                    glColor3f(0.25, (double) steps / max * 1.0, 0.75);
                }
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
            }

            MPI_Send( &col, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);

        }
    }

    glutSwapBuffers(); //

}
void reshapefunc(int wscr, int hscr) {
    glViewport(0, 0, (GLsizei) N, (GLsizei) N);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0 * N, 0.0, 1.0 * N); // always a square
    glMatrixMode(GL_MODELVIEW);
}
void mousefunc(int button, int state, int xscr, int yscr) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            printf("Zooming In.\n");
            double realScale = (maxReal - minReal) / (N);
            double imagScale = (maxImag - minImag) / (N);
            double imag = minImag + yscr * imagScale;
            double real = minReal + xscr * realScale;
            minReal = real - 0.25 * (maxReal - minReal);
            maxReal = real + 0.25 * (maxReal - minReal);
            minImag = imag - 0.25 * (maxImag - minImag);
            maxImag = imag + 0.25 * (maxImag - minImag);
            displayfunc();
            printf("Done.\n");
        }
    } else if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            printf("Resetting.\n");
            maxReal = 2.0;
            minReal = -2.0;
            maxImag = 2.0;
            minImag = -2.0;
            max = 25;
            displayfunc();
        }
    }
}
void keyfunc(unsigned char key, int xscr, int yscr) {
    if (key == 'w') {
        max += 100;
        printf("Increasing maximum iterations to %d.\n", max);
        displayfunc();
        printf("Done.\n");
    }
    if (key == 'q' && max > 0) {
        max -= 100;
        printf("Decreasing maximum iterations to %d.\n", max);
        displayfunc();
        printf("Done.\n");
    }

}

int main(int argc, char * argv[]) {

        //
        // boilerplate
        //
        MPI_Init( & argc, & argv);
        MPI_Comm_size(MPI_COMM_WORLD, & size); // same
        MPI_Comm_rank(MPI_COMM_WORLD, & rank); // different
        if (rank == 0) {
            printf("Press W to sharpen, Q to unsharpen.\nLeft click to zoom and right click to reset.\nMaximum iterations set to %d.\n", max);
            glutInit( & argc, argv);
            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
            glutInitWindowSize(N, N);
            glutInitWindowPosition(1000, 50);
            glutCreateWindow("");
            glClearColor(1.0, 1.0, 1.0, 0.0);
            glShadeModel(GL_SMOOTH);

            glutIdleFunc(idlefunc);
            glutDisplayFunc(displayfunc);
            glutReshapeFunc(reshapefunc);
            glutMouseFunc(mousefunc);
            glutKeyboardFunc(keyfunc);
            //
            glutMainLoop();
        }
        //
        //
        // boilerplate
        //
        MPI_Finalize();
        return 0;
    }
    // 
    // end of file
    //
