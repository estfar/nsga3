#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "tarea01.h"

// Generar 3000 soluciones aleatorias ( distribucion uniforme )
// Funcion que escribe en un archivo la cantidad de soluciones
// dada de manera uniforme. 
// Recibe dos parametro n: la cantidad de soluciones que se quiere
// m: la cantidad de objetivos

void genSol(int n, int m){
	Rseed = 0.9;
	randomize();
	FILE *fptr;
	char fname[30];
	sprintf(fname, "sol%dD.txt", m);
	printf("nombre: %s\n", fname);
	fptr = fopen(fname, "w");
	fprintf(fptr, "#\t%d\t%d\n", n, m);
	for( int j=0; j<n; j++){
		for( int i=0; i<m; i++){
			fprintf(fptr, "%.3f\t", rndreal(0,1));
		}
		fprintf(fptr, "\n");
	}
	fclose(fptr);
}

// * Función para comparar dos soluciones i y j, devolviendo:
// i domina a j = 1
// j domina a i = 2
// Son mutualmente no dominadas = 3
int dominancia(double *sol1, double *sol2, int m){
	int sum1=0, sum2=0;
	for(int i=0; i<m; i++){
		if(sol1[i]<sol2[i]){
			sum2++;
		}else if(sol1[i]>sol2[i]){
			sum1++;
		}
	}
	if(sum1 == 0){
		return 1;
	}else if(sum2 == 0){
		return 2;
	}else{
		return 3;
	}
}
	
// * Función que toma un archivo y lo transforma en un arreglo de arreglos 
// para almacenar todas las soluciones archivo.
double **archivo_a_arreglo(char *fname, int n, int m){
	double **datos;
	datos = (double **)malloc(sizeof(double*)*n);
	int i=0;
	char buffer[100];
	char *expres = (char *)malloc(sizeof(char)*(5*m));
	double *temp= (double *)malloc(sizeof(double)*5);

	for(i=0; i<n; i++){
		datos[i] = (double *)malloc(sizeof(double)*m);
	}
	FILE * f;
       	f = fopen(fname, "r");
	
	// construir la expresión para leer los datos
	strcpy(expres, "");
	for(i=0; i<m; i++){
		strcat(expres,"%lf\t");
	} 
	i=0;
	while( fgets(buffer, sizeof(buffer), f) != NULL && i<n){
		//printf("%s", buffer);	
		sscanf(buffer, expres, &temp[0], &temp[1], &temp[2],
				&temp[3], &temp[4]);
		for(int j=0; j<m; j++){
			datos[i][j] = temp[j];
		}
		i++;
	}

	fclose(f);
	free(expres);
	free(temp);
	return datos;
}

// *Lista ligada para los indices de las soluciones no dominadas encontradas
// hasta el momento. 

// Función para escribir las soluciones no dominadas
// n cantidad de soluciones
// m cantidad de objetivos
void escribir_soluciones(double **datos, char* fname, int n, int m){
	FILE *f;
	f = fopen(fname, "w");
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){	
			fprintf(f, "%.3lf\t", datos[i][j]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
	printf("Datos escritos en %s\n", fname);

}

// Algoritmo 1: fuerza bruta
// Parametros: datos - estructura de datos originales
// 	       n - cantidad de soluciones
// 	       m - cantidad de objetivos
// Salida: int cantidad de soluciones nodomindas
// solNoDom - arreglo de indices de las soluciones no dominadas

//double ** 
int algoritmo1(char *fname, int n, int m){
	// leer los datos
	double ** datos = archivo_a_arreglo(fname, n, m);
	clock_t start, end;	
	int i=0, j=0;
	int dom=0;
	int flag = 0;
	Node *lista = crear_lista(0);
	start = clock();
	// Algoritmo
	for (i=0; i<n; i++){
		flag = 0;
		for(j=0; j<n; j++){
			if(j != i){
				dom = dominancia2(datos[j], datos[i], m);
				if(dom == 1){
					flag =1;
					// si j domina a i, ir al siguiente i
					break;
				}
			}
		}
		if(flag == 0){
			agregar(lista, i, 0, 0);
		}
	}
	end = clock();
	double timeTaken = ((double)(end-start))/ CLOCKS_PER_SEC;
	printf("El algoritmo 1 se ejecuto en: %lf\n", timeTaken);
	pop(&lista);
	int tam = size(lista);
	int *indices = lista_a_arreglo(lista);
	
	liberar_lista(&lista);

	int dominadas = n-tam;
	for(i=0; i<n; i++){
	
	}
	printf("La cantidad de soluciones dominadas es: %d de %d\n", tam, n);
	
	// Recuperar los elementos de los datos originales.
	double **noDominadas = (double **)malloc(sizeof(double*)*tam);

	for(i = 0; i<tam; i++){
		noDominadas[i] = (double*)malloc(sizeof(double)*m);
	}

	for(i = 0; i<tam; i++){
		for(j=0; j<m; j++){
			noDominadas[i][j] = datos[indices[i]][j];
		}
	}
	free(indices);
	
	for(i=0; i<n; i++){
		free(datos[i]);
	}
	free(datos);
	
	char fnamend[50];
	sprintf(fnamend, "salida/%s-1.nd", fname);
	escribir_soluciones(noDominadas, fnamend, tam, m);
	
	// Liberar noDominadas
	for(i=0; i<tam; i++){
		free(noDominadas[i]);
	}
	free(noDominadas);

	return tam;
	//return noDominadas;
}

int algoritmo2(char *fname, int n, int m){
	double ** datos = archivo_a_arreglo(fname, n, m);
	Node * lista = crear_lista(0);
	int j=1, i=1, tam=0;
	agregar(lista, 0, 0, 0); // agregando el primer elemento de datos
	clock_t start, end;
	// Algoritmo
	start = clock();
	while( i < n ){
		// Paso 3: Comparar la solución i con j de P'
		//printf("i: %d, j: %d\n", i-1, indice(lista, j));	
		int dom = dominancia2(datos[i], datos[indice(lista, j)], m);
		
		if( dom == 1 ){
		// Paso 4: Si i domina a j, borrar el j-esimo 
		// miembro de P'
			//printf("eliminar: %d de P (%d), i: %d\n", j, indice(lista, j), i);
			eliminar_indice(&lista, j);
		}
		
		if( dom != 2 ){	
			tam = size(lista);
			if( j < tam-1 ){
			// Si j < |P'|, entonces incrementar j en uno e 
			// ir al paso 3
				if(dom == 3){
				j++;
				}
				continue;
			}else{
			// Si no, ir al paso 5
				agregar(lista, i, 0, 0);
				i++;
				j=1;
			}
		}
		// Alternativamente, si el j-esimo miembro de 
		// P' domina a i, incrementa i en uno e ir al Paso 2
		if( dom == 2 ){
			i++;
			///if(i>=n) printf("i es a n en j: %d\n", indice(lista, j));	
			j = 1;
		}
		//printf("i: %d, j: %d\n", i, j);
	}
	end = clock();
	double timeTaken = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("El algoritmo 2 se ejecuto en: %lf\n", timeTaken);
	//imprimir_lista(lista);	
	pop(&lista);
	tam = size(lista);
	int *indices = lista_a_arreglo(lista);
	
	liberar_lista(&lista);

	printf("La cantidad de soluciones dominadas es: %d de %d\n", tam, n);
	
	// Recuperar los elementos de los datos originales.
	double **noDominadas = (double **)malloc(sizeof(double*)*tam);
	
	for(i = 0; i<tam; i++){
		noDominadas[i] = (double*)malloc(sizeof(double)*m);
	}

	for(i = 0; i<tam; i++){
		for(j=0; j<m; j++){
			noDominadas[i][j] = datos[indices[i]][j];
		}
	}
	free(indices);	
	for(i=0; i<n; i++){
		free(datos[i]);
	}
	free(datos);
	
	char fnamend[50];
	sprintf(fnamend, "salida/%s-2.nd", fname);
	escribir_soluciones(noDominadas, fnamend, tam, m);
	
	// Liberar noDominadas
	for(i=0; i<tam; i++){
		free(noDominadas[i]);
	}
	free(noDominadas);

	return tam;
}

int dominancia2(double *sol1, double *sol2, int m){
	/*Bentley, '93*/	
	
	int i=0;
	double tol = 1e-4;
	
	while(i < m && fabs(sol1[i]-sol2[i]) < tol){
		i = i+1;
	}
	if (i > m){
		return 0; // son iguales
	}
	if( sol1[i] < sol2[i] ){
		for(int j=0; j<m; j++){
			if(sol2[j] < sol1[j]){
				return 3;// sol1 y sol2 son incomparables
			}
		}
		return 1; // sol1 domina a sol2
	}else{
		for(int j=0; j<m; j++){
			if(sol1[j] < sol2[j]) return 3; // sol1 y sol2 son incoparable
		}
		return 2; // sol2 domina a sol1
	}
}

/* tiene que recibir una lista con los indices del conjunto de soluciones a examinar
 * tambien el arreglo de arreglos original para obtener los vectores 
 * Regresa: un arreglo de los indices de los datos originales 
 *  */
Node * algoritmoM3(double **datos, int *indices, int n, int m){
	/*Bentley, '93*/
	int topMax = 1;
	Node *Max = crear_lista(0);
	agregar(Max, indices[0], 0, 0);

	// iterar sobre los elementos de la lista indices
	for(int i=1; i<n; i++){
		int j=1; // j va a iterar sobre Max, que es una lista
		while(j<= topMax){
			int dom = dominancia2(datos[indice(Max, j)], datos[indices[i]], m);
			if(dom == 1){
			// If point Max[j] dominates point i
				// mover Max[j] al frente de Max[1]
				// j= topmax + 2
			int point = eliminar_indice(&Max, j);
			agregar_inicio(Max, point);
			j = topMax + 2;

			} else if(dom == 2){
			// If point i dominated point Max[j]
				// delete Max[j]
				eliminar_indice(&Max, j);
				topMax = topMax-1;
			} else if(dom == 0){
			// If point i equals point Max[j]
				j = topMax + 2;
			} else{
			// If point i and Max[j] are incomparable
				j = j+1;
			}
		}
		if(j == topMax + 1){
			topMax = topMax+1;
			agregar_en_pos(Max, indices[i], topMax);
		}
	}
	return Max;
}

//int algoritmo3(char * fname, int n, int m, int **nodominadas, int **dominadas){
int algoritmo3(double **datos, int n, int m, int **nodominadas, int **dominadas){
	/*Bentley, '93*/
	
	//double ** datos = archivo_a_arreglo(fname, n, m);
	
	// Initialize the sets A, C and BD to empty
	// Serian tres listas?
	//Node * A = crear_lista(0);
	Node * C = crear_lista(0);
	Node * B = crear_lista(0);
	Node * maxima;
	clock_t start, end;

	double P[m];
	// initialized p
	for(int i=0; i<m; i++){
		P[m] = n * ( 1-pow( log(n)/n, 1.0/m) );
	}
	// compare each point Q in the set S to P.
	start = clock();
	for(int i=0; i<m; i++){
		int dom = dominancia2(P, datos[i], m);
		// If P dominates Q, place Q inside A
		if (dom == 1){
			//agregar(A, i);
		}else if(dom == 2){
		// If Q dominates P, place Q in set C
			agregar(C, i, 0, 0);
		}else{
		// Otherwise place Q in set BD (incomparable)
			agregar(B, i, 0, 0);
		}
	}
	// If set C is empty, then compue the maxima of S and return
	int sizeC = size(C);

	if (sizeC <= 1){
		int indexes[n];
		for(int i=0; i<n; i++) indexes[i] = i;
		maxima = algoritmoM3(datos,  indexes, n, m);
	}else{
	// Because C is not empty, no maxima are in set A. compute the
	// maxima of B \union C
		int sizeTotal;
		unir(B,C);
		pop(&B);
		sizeTotal = size(B);
		
		int *indexes = lista_a_arreglo(B);
		
		maxima = algoritmoM3(datos, indexes, sizeTotal, m);
		
		liberar_lista(&B);
	}
	end = clock();

	double timeTaken = ((double)(end-start)) / CLOCKS_PER_SEC;
	printf("El algoritmo 3 se ejecuto en: %lf\n", timeTaken);
	
	pop(&maxima);
	int tam = size(maxima);
	int dominadas_tam = n - tam;
	*nodominadas = lista_a_arreglo(maxima);
	int i, j;

	*dominadas = (int *)malloc(dominadas_tam * sizeof(int));
	Node * temp1 = maxima;

	j=0;
	int k=0, kk=0;
	for(i=0; i<n; i++){
		if(buscar(maxima, i)==0){
			(*dominadas)[j] = i;
			j++;
		}
		if(j>=dominadas_tam) break;
	}


	liberar_lista(&maxima);

	printf("La cantidad de soluciones dominadas es: %d de %d\n", tam, n);
	
	// Recuperar los elementos de los datos originales.
	/*
	double **noDominadas = (double **)malloc(sizeof(double*)*tam);
	
	for(i = 0; i<tam; i++){
		noDominadas[i] = (double*)malloc(sizeof(double)*m);
	}

	for(i = 0; i<tam; i++){
		for(j=0; j<m; j++){
			noDominadas[i][j] = datos[indices[i]][j];
		}
	}

	free(indices);
	*/
	
	/*
	char fnamend[50];
	sprintf(fnamend, "salida/%s-3.nd", fname);
	escribir_soluciones(noDominadas, fnamend, tam, m);
	
	// Liberar noDominadas
	for(i=0; i<tam; i++){
		free(noDominadas[i]);
	}
	free(noDominadas);
	*/
	return tam;	
}
