#include <GL/glut.h>    
#include <math.h>
#include <complex.h>

int main (int argc, char *argv[])
{
    int i, j, count;
    float re_max=1.0, re_min=-2.0, im_max=1.0, im_min=-1.0 ; 
    float real_delta = (re_max - re_min)/750;
    float imag_delta = (im_max - im_min)/500;

    double complex x = 0.0 + 0.0 * I;
    double complex z = re_min + im_min * I;

    double absolute_x;

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(150,150);
    glutInitWindowSize(750,500); 
    glutCreateWindow (argv[0]);

    glClearColor (0.1, 0.2, 0.3, 0.0);  
    glClear (GL_COLOR_BUFFER_BIT);      
    glColor4f(0.5,0.7,0.3,0.0);
    glPointSize(1);

    for (i=0, z = re_min + im_min * I ; i<750; i++, z = (re_min + real_delta) + im_min * I)
        {

        for (j=0, z = creal(z) + im_min * I; j<500; j++, z = creal(z) + (im_min + imag_delta) * I)
            {
            count = 0;
            x = 0 + 0*I;

            while ((absolute_x = fabs(x))<=2.0 && count < 64)
            {
                x = (x * x) + z;
                count++;
            }

                if (absolute_x <= 2.0){
                    glBegin(GL_POINTS);
                        glVertex2i(i,j);
                    glEnd();
                }
            }
        }

    glFlush();

    glutMainLoop();

    return (0);

}
