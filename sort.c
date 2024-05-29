#include"dominancia/tarea01.h"

/* fast non-dominated sort, deb, 14 */

void non_dominanted_sort(double **pop, double **nextpop, int n, int m){
	// Hacer los frentes nodominados de una manera iterativa
	// Puedo usar uno de los algoritmos que ya hice para obtener 
	// los elementos no dominados, modificandolos para obtener
	// la población que es dominadas
	int *dominadas, *nodominadas;
	int size_dom, size_nondom, current_size=0;
	
	size_nondom =algoritmo3(pop, n, m, nodominadas, dominadas);
	size_dom = n-size_nondom;
	
	while(current_size < n){
		if(size_nondom <= n){
			// agregar nodominadas a  nextpop
			current_size += size_nondom;
		}else{
			// que pasa si size_nondom > n (n es el tamaño de la población)
			break;
			// la población nextpop y los indices de nodominadas serán sometidos
			// a los siguientes pasos del algoritmo	
		}
		int temp = size_nondom;
		size_nondom = algoritmo3(pop, size_nondom, m, nodominadas, dominadas);
		size_dom = n-size_nondom;
	}
}
