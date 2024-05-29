//double  RAND_MAX = 4294967296.0; //2147483647; //
#ifndef _ALEATORIO_H
#define _ALEATORIO_H

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>

void randomize();
void warmup_random(double);
void advance_random();
int flip(double);
double randomperc();
double aleatorios_0_1();
long  rnd(long, long);
float rndreal(float ,float );

extern double  Rseed;			       		         /* Random numbers seed */
extern double oldrand[55];                               /* Array of 55 random numbers */
extern int jrand;/* current random number */
#endif
