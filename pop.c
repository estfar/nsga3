#include "global.h"

void init_pop(double **gen, int n, int k, int m, double lim_inf, double lim_sup){
	for(int i=0; i<n; i++){
		for(int j=m; j<m+k; j++){
			gen[i][j] = rndreal(lim_inf, lim_sup);
		}
	}
}

void evaluate_ind(double *ind, double *eval, int k, int m, void(*f)(double *, double *, int, int)){
	(*f)(ind, eval, k, m);
}

void evaluate_pop(double **gen, int n, int k, int m, void(*f)(double *, double *, int, int)){
	for(int i=0; i<2*n; i++){
		evaluate_ind(gen[i]+m, gen[i], k, m, f);
	}
}
