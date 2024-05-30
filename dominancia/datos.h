#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	struct node *next;
}Node;

Node *crear_lista(int data);
void agregar(Node *inicio, int data);
void agregar_inicio(Node *inicio, int data);
int agregar_en_pos(Node *inicio, int data, int pos);
int unir(Node *l1, Node *l2);
int pop(Node **inicio);
int eliminar(Node **inicio, int data);
int eliminar_indice(Node **inicio, int index);
int indice(Node *inicio, int index);
int size(Node *inicio);
int vaciar_lista(Node *inicio);
int buscar(Node *inicio, int item);
int *lista_a_arreglo(Node *inicio);
void imprimir_lista(Node *inicio);
void liberar_lista(Node **inicio);
