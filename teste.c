#include <stdio.h>
#include <math.h>


void polygon (int n)
{
    double pI = 3.141592653589;
    double area = min(200/2, 400/2);
    int X = 0, Y = area - 1;
    double offset = Y;
    int lastx, lasty;

    double radius = sqrt(X * X + Y * Y);
    double quadrant = atan2(Y, X);

    int i;

    for (i = 1; i <= n; i++)
    {
        lastx = X; lasty = Y;
        quadrant = quadrant + pI * 2.0/n;

        X = round((double)radius * cos(quadrant));
        Y = round((double)radius * sin(quadrant));

        setpen((i * 255)/n, 0, 0, 0.0, 1);//r(interval) g b, a, size

        moveto(offset + lastx, offset + lasty);//Moves line offset
        lineto(offset + X, offset + Y);//Draws a line from offset
    }
}