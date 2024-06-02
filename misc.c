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
			next_pop[i][j] = pop[indice(indices, i)][j];
		}
	}
}

double dist(double *w, double *s, int m){
	double res=0;
	double wsw[m];
	for(int i=0; i<m; i++){
	//	printf("%lf \n", w[i]);
		res += w[i] * s[i];	
	}
	//printf("res: %lf", res);
	for(int i=0; i<m; i++){
		wsw[i] = s[i] - res * w[i];
		wsw[i] /= norm2(w, m);
	}
	return norm2(wsw, m);

}

double norm2(double *w, int m){
	double res=0;
	for(int i=0; i<m; i++){
		res += fabs(w[i])*fabs(w[i]);
	}
	return sqrt(res);
}


double scl_fun(double *vec, double *w, double *ideal, int m){
	double acum=0.0;
	for(int i=0; i<m; i++){
		acum += w[i]*(vec[i]-ideal[i]);
	}
	return acum;
} 
