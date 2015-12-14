
if (magnitude of Z (sqrt(a^2+b^2) >= 2))
{
	break;
}

if (steps == max)
{
	*set color*
}
else if *blows up*
{
	*scale*
}

//Usually, there is no Z variable, there is variable a and b. Z = a + bi
//
//
For each pixel (Px, Py) on the screen, do:
{
 x0 = scaled x coordinate of pixel (scaled to lie in the Mandelbrot X scale (-2.5, 1))
 y0 = scaled y coordinate of pixel (scaled to lie in the Mandelbrot Y scale (-1, 1))
 x = 0.0
 y = 0.0
 iteration = 0
 max_iteration = 1000
 while ( x*x + y*y < 2*2  AND  iteration < max_iteration )
   {
    xtemp = x*x - y*y + x0
    y = 2*x*y + y0
    x = xtemp
    iteration = iteration + 1
   }
   color = palette[iteration]
   plot(Px, Py, color)
 }
