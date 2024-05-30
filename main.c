#include "global.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	
	double **datos;
	datos = archivo_a_arreglo("dominancia/sol5D.txt", 10, 3);

	double **next_datos = (double**)calloc(10, sizeof(double *));
	for(int i=0; i<10; i++){
		next_datos[i] = (double *)calloc(3, sizeof(double));
	}	

	//escribir_soluciones(datos, "solNoDom.txt", 10, 3);
	//int indices[10] = {0,1,2,3,4,5,6,7,8,9};
	
	int tam ;
	int * dominadas, *nodominadas;
	int n, m;
	Node *lista;
	lista = crear_lista(-1);
	n=10;
	m = 3;
	tam = algoritmo3(datos, n, m, &nodominadas, &dominadas);
	printf("Soluciones no dominadas: %d\n", tam);
	for(int i=0; i<n-tam; i++)
		printf("%d\n", dominadas[i]);
	printf("no dominadas\n");
	for(int i=0; i<tam; i++){ 
		printf("%d\n", nodominadas[i]);
		agregar(lista, nodominadas[i],0,0);
	}
	printf("copiar\n");
	copiar(datos, next_datos, 3, 3, lista);
	copiar_ind(next_datos, 3, 4, datos[indice(lista, 4)]);
	for(int i=0; i<10; i++){ 
		for(int j=0; j<3; j++) printf("%f\t", next_datos[i][j]);
		printf("\n");
	}
	free(dominadas);
	free(nodominadas);
	printf("done\n");
	for(int i=0; i<10; i++){
		free(next_datos[i]);
		free(datos[i]);
	}	
	free(next_datos);
	free(datos);

	//Node *res = algoritmoM3(datos, indices, 10, 3);

	/* Imprimir el resultado*/
	//imprimir_lista(res);

	//liberar_lista(res);

	//tam = algoritmo1("sol5D.txt", 10, 3);
	/*
	double ind1[] = {1,2,3,4};
	double ind2[] = {1,1,0,3};
	double ind3[] = {1,0,1,3};
	int res = dominancia2(ind2, ind1, 4);
	printf("ind2 vs ind1 resultado: %d\n", res);
	res = dominancia2(ind3, ind2, 4);	
	printf("ind3 vs ind2 resultado: %d\n", res);
	*/
}
