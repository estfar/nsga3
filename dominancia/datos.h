#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int data;
	int c_point; //closest ref point
	double dist; //distance to the closest ref point
	struct node *next;
}Node;

Node *crear_lista(int data);
void agregar(Node *inicio, int data, int c_point, double dist);
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
void set_info_list(Node *inicio, int pos, int c_point, double dist);
double get_dist_list(Node *list, int index);
