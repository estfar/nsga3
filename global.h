#ifndef _GLOGAL_H
#define _GLOBAL_H
#define PI 3.1415926535897932384626433832795
#include"dominancia/tarea01.h"
#include<string.h>
#include<math.h>
/*misc.c*/
int factorial(int x);
void copiar_ind(double **next_pop, int m, int nvar, int pos, double *ind);
void copiar(double **pop, double **next_pop, int n, int m, int nvar, Node *indices); 
double dist(double *w, double *s, int m);
double norm2(double *w, int m);
double scl_fun(double *vec, double *w, double *ideal, int m);

/* evop.c */
void SBX(double *parent1, double *parent2, double *child1, double *child2, int nvar, double Pc, 
	 double lim_inf, double lim_sup, double eta_c);
void poly_mutation(double *x, int num_var, double pm, double nm, double lim_inf, double lim_sup);
void recombination(double **gen, int n, int k, int m, double Pc, double eta_c, double *lim);
void mutation(double **gen, int n, int k, int m, double pm, double nm, double *lim);

/* pop.c */
void init_pop(double **gen, int n, int k, int m, double lim_inf, double lim_sup);
void evaluate_ind(double *ind, double *eval, int k, int m, void(*f)(double *, double *, int, int));
void evaluate_pop(double **gen, int n, int k, int m, void(*f)(double *, double*, int, int));

/* problems.c */
void DTLZ2(double *x, double *f, int nvar, int nobj);

/*nsga3.c*/
double **normalize(double **pop, int *elite_arr, int curr_size, int m); 
void associate(double **normalized, Node * elite, int current_size, int m, double **ref_points, int H);
void niching(int *niche_count, Node *elite, int H, int curr_size, int size_nondom, double **pop, 
	     double **next_pop, int n, int m, int nvar);
void non_dominanted_sort(double **c_pop, double **nextpop, int n, int m, int nvar, int H, char *fname);
//void nsga3(int n, int m, char *pname, int stop_crit);

#endif
