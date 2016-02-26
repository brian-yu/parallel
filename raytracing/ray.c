#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define W 640
#define H 480
#define XMIN -0.165625
#define YMIN 0.001042
#define XMAX 1.165625
#define YMAX 0.998958
#define NUMSPHERES 4


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
    triple c;
    double r;
    color h;

} sphere;

typedef struct
{
    int key;
    double val;
} tuple;

sphere a[NUMSPHERES] = {};

triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
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

double magnitude(triple v) {
    return sqrt(dotp(v,v));
}

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

triple unitVector(double x, double y) {
    triple vector;
    triple location = {x, y, 0};
    diff(&vector, location, e);
    double m = magnitude(vector);
    vector.x = vector.x/m;
    vector.y = vector.y/m;
    vector.z = vector.z/m;
    return vector;
}

tuple minDist(triple e, triple r) {

    
    double min = 1.0/0;
    int key = -1;

    for (int i = 0; i < NUMSPHERES; i++) {
        double b = 2*(dotp(e,r)-dotp(r, a[i].c));
        double c = pow((e.x-a[i].c.x),2) + pow((e.y-a[i].c.y),2) + pow((e.z-a[i].c.z),2) - pow((a[i].r),2);
        double d = b*b-4*c;
        double T = (-b-sqrt(d)) / 2;
        if (T < min && T > 0 && d>0) {
            min = T;
            key = i;
        }
    }
    
    tuple pair;
    pair.key = key;
    pair.val = min;
    
    return pair;
    
}

int main(void)
{
    int rgb[H][W][3];
    int y, x;
    FILE* fout;
    init();
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++) {
            double XSIZE = XMAX - XMIN;
            double YSIZE = YMAX - YMIN;
            double valx = XMIN + (((double)x) / W) * XSIZE;
            double valy = YMIN + (((double)y) / H) * YSIZE;
            
            triple r = unitVector(valx,valy);
            
            tuple pair;
            pair = minDist(e, r);
            int i = pair.key;
            double T = pair.val;
            
            int n = H-y-1;
            if (i == -1) {
                rgb[n][x][0] = 178;
                rgb[n][x][1] = 255;
                rgb[n][x][2] = 255;
            } else {
                rgb[n][x][0] = (int)(a[i].h.r);
                rgb[n][x][1] = (int)(a[i].h.g);
                rgb[n][x][2] = (int)(a[i].h.b);
            }
            
            pair = minDist(g, r);
            int il = pair.key;
            double Tl = pair.val;
            
            triple v;
            diff(&v, r, e);
            
            triple l;
            diff(&l, g, a[i].c);
            
            double cosAngle = dotp(l, v)/(magnitude(l) * magnitude(v));
            
            if (cosAngle >= 0) {
                rgb[n][x][0] = (int)(cosAngle * a[i].h.r);
                rgb[n][x][1] = (int)(cosAngle * a[i].h.r);
                rgb[n][x][2] = (int)(cosAngle * a[i].h.r);
            }
        }
    }
    fout = fopen("output.ppm", "w");
    fprintf(fout, "P3\n");
    fprintf(fout, "%d %d\n",W,H);
    fprintf(fout, "255\n");
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++) {
             fprintf(fout, "%d %d %d\n", rgb[y][x][0], rgb[y][x][1], rgb[y][x][2]);
        }
    }
    close(fout);
    return 0;
}
