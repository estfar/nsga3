#ifndef _TAREA01_H
#define _TAREA01_H
#include "aleatorio.h"
#include "datos.h"

void genSol(int n, int m);
int dominancia(double *sol1, double *sol2, int m);
int dominancia2(double *sol1, double *sol2, int m);
double **archivo_a_arreglo(char *fname, int n, int m);
void escribir_soluciones(double **datos, char* fname, int n, int m);
int algoritmo1(char *fname, int n, int m);
int algoritmo2(char *fname, int n, int m);
Node *algoritmoM3(double **datos, int *indices, int n, int m);
//int algoritmo3(char *fname, int n, int m, int **nodominadas, int **dominadas);
int algoritmo3(double **datos, int n, int m, int **nodominadas, int **dominadas);

#endif
