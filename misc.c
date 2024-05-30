#include"global.h"

int factorial(int x){
	int res=1;
	for(int i=x; i>=0; i--){
		res*=i;
	}
	return res;
}

/* Copiar un arreglo (ind) en la posicion pos del arreglo nextpop */
void copiar_ind(double **next_pop, int m, int pos, double *ind){
	for(int i=0; i<m; i++){
		next_pop[pos][i] = ind[i];
	}
}

/* Copiar los n primeros elementos indices de pop en las primeras
 * n posiciones de next_pop  */

void copiar(double **pop, double **next_pop, int n, int m, 
	    Node *indices){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			next_pop[i][j] = pop[indice(indices, i+1)][j];
		}
	}
}
