#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double sin_lookup(double x)
{
    static double *lookup;
    static const int length = 360;
    int i;

    if (lookup == NULL) {
        lookup = malloc(length * sizeof(double));
        for (i = 0; i < length; i++) {
            printf("Calculating angle %f for slice %d\n",
                i * 2 * M_PI / length,
                i);
            lookup[i] = sin(i * 2 * M_PI / length);
        }
    }

    printf("Looking at %d th slice for angle %f\n",
        (int)((x - ((int)(x/(2*M_PI)))*(2*M_PI)) * length / (2*M_PI)),
        x);
    return lookup[(int)((x - ((int)(x/(2*M_PI)))*(2*M_PI)) * length / (2*M_PI))];
}

void main()
{
    int i, degs = 30, count = 15;

    for (i = 0; i < count; i++) {
        printf("sin(%d degs) = %f, sin_lookup(%d degs) = %f\n",
            i * degs,
            sin(i * degs * M_PI / 180),
            i * degs,
            sin_lookup(i * degs * M_PI / 180));
    }
}
