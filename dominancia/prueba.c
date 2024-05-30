#include<stdio.h>
#include<stdlib.h>
#include"datos.h"

int main(){
	Node *lista = crear_lista(1);
	agregar(lista, 2);	
	agregar(lista, 32);	
	agregar(lista, 22);	
	agregar(lista, 12);

	Node *l2 = crear_lista(3);
	agregar(l2, 5);
	agregar(l2, 15);
	agregar(l2, 56);
	agregar(l2, 590);
	printf("l2\n");
	imprimir_lista(l2);

	int tam = size(lista);
	int * arreglo = lista_a_arreglo(lista);
	for(int i=0; i<tam; i++){
		printf("%d\t", arreglo[i]);
	}
	printf("\n");
	printf("Imprimir lista de tamaño: %d\n", tam);	
	imprimir_lista(lista);

	printf("Nueva lista\n");
	eliminar_indice(&lista, 2);
	imprimir_lista(lista);

	int in = indice(lista, 2);
	printf("dato en indice 2: %d\n", in);

	agregar_en_pos(lista, 56, 2);
	printf("Nuevo lista\n");
	imprimir_lista(lista);
	
	printf("Nuevo lista\n");
	agregar_en_pos(lista, 13, 5);
	imprimir_lista(lista);

	printf("Nuevo lista\n");
	agregar_en_pos(lista, 13, 1);
	imprimir_lista(lista);
	
	printf("Nuevo lista\n");
	agregar_en_pos(lista, 13, 8);
	imprimir_lista(lista);
	
	printf("Union lista y l2\n");
	int r = unir(lista, l2);
	imprimir_lista(lista);
	printf("tamaño de la nueva lista: %d\n", size(lista));

	//liberar_lista(l2);
	liberar_lista(&lista->next);	
	printf("liberada\n, tam nodo: %ld\n", sizeof(Node*));
	imprimir_lista(lista);
	printf("sizeof: %ld\n", sizeof(lista));	
	/*
	eliminar(&lista, 22);
	tam = size(lista);
	printf("Imprimir lista de tamaño: %d\n", tam);	
	imprimir_lista(lista);
	eliminar(&lista, 2);
	printf("Imprimir lista\n");
	imprimir_lista(lista);
	eliminar(&lista, 1);
	printf("Imprimir lista\n");
	imprimir_lista(lista);
	eliminar(&lista, 10);
	printf("Imprimir lista\n");
	imprimir_lista(lista);
	*/

}
