#include "tarea01.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

	char fname[50] = "sol3D.txt"; // "sol4D.txt" "sol5D.txt"
	int N = 3000;
	int k= 3; //4, 5

	int tam = algoritmo1(fname, N, k);
	printf("Soluciones dominadas: %d\n\n", tam);
	
	tam = algoritmo2(fname, N, k);
	printf("Soluciones dominadas: %d\n\n", tam);
	
	tam = algoritmo3(fname, N, k);
	printf("Soluciones dominadas: %d\n\n", tam);
}
