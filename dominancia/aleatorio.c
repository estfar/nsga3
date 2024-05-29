#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "aleatorio.h"

int jrand = 0;
double oldrand[55] = {0.0};
double Rseed = 0.0;

/* Initialize random numbers batch */
void randomize()
{
	int j1;

    for(j1=0; j1<=54; j1++)
      oldrand[j1] = 0.0;

    jrand=0;

     warmup_random(Rseed);
}



/* Get random off and running */
void warmup_random(double random_seed)
{
	int j1, ii;
	double new_random, prev_random;

	oldrand[54] = random_seed;
	new_random = 0.000000001;
	prev_random = random_seed;

	for(j1 = 1 ; j1 <= 54; j1++){
		ii = (21*j1)%54;
		oldrand[ii] = new_random;
		new_random = prev_random-new_random;
		if(new_random<0.0) new_random = new_random + 1.0;
			prev_random = oldrand[ii];
		}
		advance_random();
		advance_random();
		advance_random();
		jrand = 0;

}

/* Create next batch of 55 random numbers */
void advance_random()
{
	int j1;
	double new_random;

	for(j1 = 0; j1 < 24; j1++){
		new_random = oldrand[j1] - oldrand[j1+31];
		if(new_random < 0.0) new_random = new_random + 1.0;
		oldrand[j1] = new_random;
	}
	for(j1 = 24; j1 < 55; j1++){
		new_random = oldrand [j1] - oldrand [j1-24];
		if(new_random < 0.0) new_random = new_random + 1.0;
		oldrand[j1] = new_random;
	}
}

/* Flip a biased coin - true if heads */
int flip(double prob){
	double randomperc();
	if(randomperc() <= prob)
		return(1);
	else
		return(0);
}

/* Fetch a single random number between 0.0 and 1.0 - Subtractive Method */
/* See Knuth, D. (1969), v. 2 for details */
/* name changed from random() to avoid library conflicts on some machines*/
double randomperc()
{
	jrand++;
	if(jrand >= 55){
		jrand = 1;
		advance_random();
	}
	return((double) oldrand[jrand]);
}


double aleatorios_0_1(){
	int i;
	double x;
	/* inicializacion de la semilla de aleatorios */
	srand(time(0));
	/* aleatorios % 0 y 1 */
	for(i=0; i<10; i++){
		x =(double) (((rand()%32000) / 32000.0)-1);
	       /*	printf("  %f	 ", x);*/
	}
	return x;
 }

 /* Pick a random integer between low and high */
 long rnd(long low, long high){
    long i;
    double randomperc();

    if(low >= high)
	i = low;
    else {
	i = (randomperc() * (high - low + 1)) + low;
	if(i > high) i = high;
    }
    return(i);
}

/* real random number between specified limits */

float rndreal(float lo ,float hi)

{
    return((randomperc() * (hi - lo)) + lo);
}
