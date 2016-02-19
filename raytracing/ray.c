#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define M 640 //width
#define N 480 //height
#define XMIN -0.166
#define YMIN 0
#define XMAX 1.166
#define YMAX 1
#define NUMSPHERES 4

double INF = 1.0/0.0;

typedef struct
{
   double x ;
   double y ;
   double z ;

} triple ;

typedef struct
{
   unsigned char r ;
   unsigned char g ;
   unsigned char b ;

} color;

typedef struct
{
	int key;
	double value;
} pair;

typedef struct
{
	triple c;
	double r;
	color h;

} sphere;

triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
double zcam = 0;
triple g = { 0.00 , 1.25 , -0.50 } ; // the light

double dotp( triple t , triple u )
{
   return t.x * u.x + t.y * u.y + t.z * u.z ;
}

void diff( triple* t , triple u , triple v ) // t = u - v
{
   t->x = u.x - v.x ;
   t->y = u.y - v.y ;
   t->z = u.z - v.z ;
}

double magnitude(triple v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

sphere a[4];

void init()
{
   a[0].c.x =      0.50 ;
   a[0].c.y = -20000.00 ; // the floor
   a[0].c.z =      0.50 ;
   a[0].r   =  20000.25 ;
   a[0].h.r =    205    ; // color is Peru
   a[0].h.g =    133    ;
   a[0].h.b =     63    ;
   //
   a[1].c.x =      0.50 ;
   a[1].c.y =      0.50 ;
   a[1].c.z =      0.50 ;
   a[1].r   =      0.25 ;
   a[1].h.r =      0    ; // color is Blue
   a[1].h.g =      0    ;
   a[1].h.b =    255    ;
   //
   a[2].c.x =      1.00 ;
   a[2].c.y =      0.50 ;
   a[2].c.z =      1.00 ;
   a[2].r   =      0.25 ;
   a[2].h.r =      0    ; // color is Green
   a[2].h.g =    255    ;
   a[2].h.b =      0    ;
   //
   a[3].c.x =      0.00 ;
   a[3].c.y =      0.75 ;
   a[3].c.z =      1.25 ;
   a[3].r   =      0.50 ;
   a[3].h.r =    255    ; // color is Red
   a[3].h.g =      0    ;
   a[3].h.b =      0    ;
}

triple unitVector(double x, double y)
{
    triple vector;
	triple location = {x, y, zcam};
	diff(&vector,location,e);
	double m = magnitude(vector);
	vector.x = vector.x/m;
	vector.y = vector.y/m;
	vector.z = vector.z/m;
	return vector;
}

pair minDist(triple e, triple r)
{
	int i;
	double minT = INF;
	int mkey = -1;
	for (i=0;i<NUMSPHERES;i++) {
		double ayy = 1;
		double b = 2*(e.x*r.x+e.y*r.y+e.z*r.z-r.x*(a[i].c.x)-r.y*(a[i].c.y)-r.z*(a[i].c.z));
		double c = (e.x-a[i].c.x)*(e.x-a[i].c.x) + (e.y-a[i].c.y)*(e.y-a[i].c.y) + (e.z-a[i].c.z)*(e.z-a[i].c.z) - ((a[i].r)*(a[i].r));
		double T = (((-1)*b)-sqrt(b*b-4*ayy*c))/(2*ayy);
		if (T < minT && T > 0 && b*b-4*ayy*c>0) {
			minT = T;
			mkey = i;
		}
	}
	pair p = {mkey,minT};
	return p;
}

int main(void)
{
	int rgb[N][M][3];
	int y,x;
	FILE* fout;
	init();
	for (y=0;y<N;y++) {
		for (x=0;x<M;x++) {
			double XSIZE = XMAX - XMIN;
			double YSIZE = YMAX - YMIN;
			double valx = XMIN + (((double)x)/M)*XSIZE;
			double valy = YMIN + (((double)y)/N)*YSIZE;
			triple r = unitVector(valx,valy);
			pair tmp = minDist(e,r);
			int mindex = tmp.key;
			double T = tmp.value;
			triple point = {e.x + r.x*T,e.y + r.y*T,e.z + r.z*T};
			if (mindex == -1) {
				rgb[N-y-1][x][0] = 0;
				rgb[N-y-1][x][1] = 0;
				rgb[N-y-1][x][2] = 0;
			} else {
				rgb[N-y-1][x][0] = (int)(a[mindex].h.r);
				rgb[N-y-1][x][1] = (int)(a[mindex].h.g);
				rgb[N-y-1][x][2] = (int)(a[mindex].h.b);
			}
		}
	}
	fout = fopen("output.ppm", "w");
	fprintf(fout, "P3\n");
	fprintf(fout, "%d %d\n",M,N);
	fprintf(fout, "255\n");
	for (y = 0; y < N; y++) {
		for (x = 0; x < M; x++) {
			 fprintf(fout, "%d %d %d\n", rgb[y][x][0], rgb[y][x][1], rgb[y][x][2]);
		}
	}
	close(fout);
	return 0;
}
