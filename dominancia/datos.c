#include"datos.h"
/* Seneca 16-05-24/ */

/* Lista ligada */

/* Crear la lista ligada */
// Regresa el inicio de una lista ligada (cabeza)
Node *crear_lista(int data){
	Node * inicio = NULL;
	inicio = (Node *)malloc(sizeof(Node));
	if (inicio == NULL){
		printf("ERROR AL RESERVAR MEMORIA PARA LISTA");
		exit(1);
	}
	inicio->data = data;
	inicio->next = NULL;
	return inicio;	
}
/* Agregar elemento al final de la lista */
void agregar(Node *inicio, int data, int c_point, double dist){
	Node * actual = inicio;
	while(actual->next != NULL){
		actual = actual->next;
	}
	actual->next = (Node *)malloc(sizeof(Node));
	actual->next->data = data;
	actual->next->c_point = c_point;
	actual->next->dist = dist;
	actual->next->next = NULL;
}

void agregar_inicio(Node * inicio, int data){
	// agregar al inicio, después de la cabeza
	//Node *temp = inicio;

	Node *nuevo = (Node *)malloc(sizeof(Node));
	nuevo->data = data;
	nuevo->next = inicio->next;

	inicio->next = nuevo;
}

/* Agregar en la posición pos */
int agregar_en_pos(Node * inicio, int data, int pos){
	// buscar el nodo previo a la posicion
	// unir el nodo nuevo->next a previo->next
	// unir previo->next a nuevo
	int tam = size(inicio);
	if (pos > tam){
		printf("POSICION INVALIDA, MAYOR QUE SIZE\n");
		return tam;
	}

	Node * current = inicio ;
	int i = 0;
	
	while(i<pos-1){
		current = current->next;
		i++;
	}
	Node * nuevo = (Node *)malloc(sizeof(Node));
	nuevo->data = data;
	nuevo->next = current->next;

	current->next = nuevo;
	return i;
}

int unir(Node *l1, Node *l2){
	Node * actual = l1;
	while(actual->next != NULL){
		actual = actual->next;
	}
	int retval = pop(&l2);
	actual->next = l2;
	return retval;
}

/* Eliminar elemento de la primera posicion */
int pop(Node **inicio){
	Node * temp;
	int val=-1;

	if (*inicio == NULL){
		printf("NO SE PUEDE ELIMINAR EL UNICO ELEMENTO");
		return 0;
	}
	temp = (*inicio)->next;
	val = (*inicio)->data;
	free(*inicio);
	*inicio = temp;	
	return val;
}
/* Eliminar elemento (en cualquier posición) */
int eliminar(Node **inicio, int data){
	// Buscar el nodo donde se encuentra el dato que se
	// quiere eliminar
	int dato = -1;
	Node *actual = *inicio;
	Node *temp = NULL;
	// Si es el primero, quitarlo
	if (actual->data == data){
		return pop(inicio);
	}

	while( actual->next != NULL && actual->next->data != data ){
		actual = actual->next;
	}
	
	if (actual->next == NULL){
		printf("EL ELEMENTO NO SE ENCUENTRA EN LA LISTA\n");
		return dato;
	}

	if( actual->next->next == NULL ){
		// Es el último
		dato=actual->next->data;
		free(actual->next);
		actual->next = NULL;
	}else{
		// El nodo que se quiere eliminar es el siguiente a 'actual'
		temp = actual->next;
		dato = temp->data;
		actual->next = temp->next;
		free(temp);
	}
	return dato;
	
}

int eliminar_indice(Node ** inicio, int index){
	int i=0;
	int retval = -1;
	Node * actual = *inicio;
	Node * temp = NULL;
	if(index == 0){
		return pop(inicio);
	}

	for(i=0; i<index-1; i++){
		if(actual->next == NULL){
			return -1;
		}
		actual = actual->next;
	}

	if(actual->next == NULL){
		return -1;
	}

	temp = actual->next;
	retval = temp->data;
	actual->next = temp->next;
	free(temp);

	return retval;

}

/* Obtener el j-esimo miembro de la lista (de 1 a n) */
int indice(Node *inicio, int index){
	int val = -1;
	Node *actual = inicio;
	for (int i=0; i<index; i++){
		actual = actual->next;
	}
	return actual->data;
}
/* Vaciar la lista, conservando la cabeza */
int vaciar_lista(Node *inicio){
	while(inicio->next != NULL){
		pop(&inicio);
	}
}
/* Buscar elemento 'item' en la lista */
int buscar(Node *inicio, int item){
	Node *actual = inicio;
	while(actual != NULL){
		if (actual->data == item){
			return 1;
		}
		actual = actual->next;
	}
	return 0;
}

/* Tamaño de la lista */
int size(Node *inicio){
	Node *actual = inicio;
	int tam=0;
	while(actual != NULL){
		tam++;
		actual = actual->next;
	}
	return tam;
}
/* Convertir a arreglo */
int *lista_a_arreglo(Node *inicio){
	int tam = size(inicio);
	int *arreglo = (int *)malloc(sizeof(int)*tam);
	Node *actual = inicio;
	int i=0;
	while(actual != NULL){
		arreglo[i] = actual->data;
		i++;	
		actual = actual->next;
	}
	return arreglo;
}
/* Imprimir el contenido de lista */
void imprimir_lista(Node *inicio){
	Node *actual = inicio;
	int i=0;
	while(actual != NULL){
		printf("%d\t%d\n", i, actual->data);
		actual = actual->next;
		i++;
	}
}

void liberar_lista(Node **inicio){
	Node * temp = *inicio;
	Node *temp2;
	while(temp != NULL){
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	*inicio = NULL;
}
