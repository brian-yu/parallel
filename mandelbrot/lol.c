

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
