#include "global.h"

void DTLZ2(double *x, double *f, int nvar, int nobj)
{
    double g, v;
    int i, j, t, c;

    g = 0.0;
    c = nvar - nobj + 1;

    for (i = nvar - c; i < nvar; i++) g += pow(x[i] - 0.5, 2.0);

    v = 1.0 + g;

    for (i = 0; i < nobj; i++)
    {
        f[i] = v;
        t = nobj - i - 1;
        for (j = 0; j < t; j++) f[i] *= cos(x[j] * PI * 0.5);

        if (t < nobj - 1) f[i] *= sin(x[t] * PI * 0.5);
    }
}
