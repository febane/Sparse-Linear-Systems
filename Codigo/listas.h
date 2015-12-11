#include <stdio.h>
#include <stdlib.h>
#ifndef LISTAS_H
#define LISTAS_H


struct elemento {
	
	int l;
	double v;
	struct elemento *ant, *prox;
	
};

struct coluna {
	
	struct elemento *primeiro;
	
};

typedef struct coluna Coluna;
typedef struct elemento Elemento;

Coluna* cria_matriz(int tam);
void adiciona_elemento(int l, int c, double valor, Coluna* matriz, int tam);
void imprime_matriz(Coluna* matriz, int tam);
void free_matriz(int tam, Coluna *matriz);


#endif
