#include "global.h"

int main(){
	double **gen;
	int n = 92;
	int m = 3;
	int k = 10;
	int nvar = m+k-1;
	//gen = archivo_a_arreglo("dominancia/sol5D.txt", n*2, 3);

	Rseed = 0.0;
	randomize();
	/*
	double ind[5] = {0.0, 0.3, 0.5, 1.0, 0.3};
	double ind2[5] = {2.0, 3.0, 1.5, 0.5, 0.1};
	double child[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
	double child2[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

	SBX(ind+m, ind2+m, child+m, child2+m, 2, 1.0, 0.0, 3.0, 30);	
	//evaluate_ind(ind+m, ind, 2, 3, DTLZ2);
	for(int i=0; i<5; i++) printf("%lf\n", ind[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", ind2[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", child[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", child2[i]);
	printf("\n");
	
	poly_mutation(child+m, 2, 0.5, 20, 0.0, 3.0);
	printf("Mutadas\n");
	for(int i=0; i<5; i++) printf("%lf\n", ind[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", ind2[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", child[i]);
	printf("\n");
	for(int i=0; i<5; i++) printf("%lf\n", child2[i]);
	printf("\n");
	return 1;
	*/

	double **next_gen = (double **)calloc(n*2, sizeof(double *));
        gen = (double **)calloc(n*2, sizeof(double*));	
	for(int i=0; i<2*n; i++){
		next_gen[i] = (double *)calloc(nvar+m, sizeof(double));
		gen[i] = (double *)calloc(nvar+m, sizeof(double));
	}
	double lim[2] = {0.0, 1.0};
	
	init_pop(gen, n, nvar, m, 0.0, 1.0);

	for(int lm =0; lm<100; lm++){
		
		recombination(gen, n, nvar, m, 1.0, 20.0, lim);
		mutation(gen, n, nvar, m, 0.084, 30.0, lim);
		evaluate_pop(gen, n, nvar, m, DTLZ2);
	
		non_dominanted_sort(gen, next_gen, n, m, nvar, 91, "ref_dirs.txt");	
	
		printf("next_gen: \n");
	
		for(int i=0; i<n; i++){
			for(int j=0; j<m+nvar; j++) printf("%lf ", next_gen[i][j]);
			printf("\n");
		}
	
		double **temp = next_gen;
		next_gen = gen;
		gen = temp;
		printf("-------------GENERACIÓN %d-----------\n", lm);
	
	}

	for(int i=0; i<n; i++){
		free(gen[i]);
		free(next_gen[i]);
	}
	free(next_gen);
	free(gen);
}
