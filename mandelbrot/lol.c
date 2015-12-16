

__global__ 
void CoreLoop(
    int *p, 
    float xld, float yld, /* Left-Down coordinates */
    float xru, float yru, /* Right-Up coordinates */
    int MAXX, int MAXY)   /* Window size */
{
    float re,im,rez,imz;
    float t1, t2, o1, o2;
    int k;
    unsigned result = 0;
    unsigned idx = blockIdx.x*blockDim.x + threadIdx.x;
    int y = idx / MAXX;
    int x = idx % MAXX;
    
    re = (float) xld + (xru-xld)*x/MAXX;
    im = (float) yld + (yru-yld)*y/MAXY;

    rez = 0.0f;
    imz = 0.0f;

    k = 0;
    while (k < ITERA) {
	o1 = rez * rez;
	o2 = imz * imz;
	t2 = 2 * rez * imz;
	t1 = o1 - o2;
	rez = t1 + re;
	imz = t2 + im;
	if (o1 + o2 > 4) {
	    result = k;
	    break;
	}
	k++;
    }

    p[y*MAXX + x] = lookup[result]; // Palettized lookup
}


int s(double x, double y, int lim)
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
