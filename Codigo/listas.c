/**
 * Resolucao de Sistemas Lineares Esparsos
 * listas.c
 * Implementação matricial
 * Ver relatorio para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include "listas.h"

/**
 *  Cria e aloca matriz e vetor independente
 *
 *  @param tam ordem da matriz
 *  @return matriz matriz desejada
 *
 */
Coluna* cria_matriz(int tam) {
	
	int i;
	
	Coluna* matriz = (Coluna*) calloc(tam+1, sizeof(Coluna));
	
	for(i = 0; i < tam; i++) {
		
		matriz[i].primeiro = NULL;
		
	}
	
	return matriz;
}

/**
 *  Adiciona elemento na matriz
 *
 *  @param l linha a ser inserido o elemento
 *  @param c coluna a ser inserido o elemento
 *  @param valor valor do elemento
 *  @param matriz matriz a ter elemento inserido
 *  @param tam ordem da matriz
 *
 */
void adiciona_elemento(int l, int c, double valor, Coluna *matriz, int tam){
	
	Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
	
	if(c >= tam+1 || l >= tam+1) {
		
		printf("Posicao matricial (%d, %d) invalida\n", l, c);
		return;
		
	}
	
	novo->l = l;
	novo->v = valor;
	novo->prox = NULL;
	novo->ant = NULL;
	
	if(matriz[c].primeiro == NULL) {
		
		matriz[c].primeiro = novo;
		
	}
	else{	
		
		Elemento* busca = matriz[c].primeiro;
		Elemento* atras = matriz[c].primeiro;
		
		while(busca->prox!=NULL && l>busca->prox->l){
			
			atras = busca;
			busca = busca->prox;
			
		}
		
		if(busca->prox==NULL){
			
			if(l>busca->l){
				
				busca->prox = novo;
				novo->ant = busca;
				
			}
			else{
				
				novo->prox = busca;
				atras->prox = novo;
				busca->ant = novo;
				novo->ant = atras;
				
			}
			
		}
		else{
			
			if(l<busca->l){
				
				novo->ant = NULL;
				novo->prox = busca;
				busca->ant = novo;
				
			}
			else{
			
				busca->prox->ant = novo;
				novo->ant = busca;
				novo->prox = busca->prox;
				busca->prox = novo;
			
			}
			
		}
		
	}
	
}

/**
 *  Imprime matriz
 *
 *  @param matriz matriz a ser apresentada
 *  @param tam ordem da matriz
 *
 */
void imprime_matriz(Coluna* matriz, int tam) {
	
	int i;
	Elemento* atual;
	
	for(i = 0; i < tam+1; i++) {
		
		atual = matriz[i].primeiro;
		printf("\nColuna %d: \n", i+1);
		
		while(atual != NULL) {
			
			printf("(linha %d, valor %lf)\n", atual->l+1, atual->v);
			atual = atual->prox;
			
		}
		
	}
	
}

/**
 *  Libera memória alocada da matriz
 *
 *  @param tam ordem da matriz
 *  @param matriz matriz a ser liberada
 *
 */
void free_matriz(int tam, Coluna *matriz){
	
	int i;
	Elemento *atual, *ant;
	
	for(i=0;i<tam+1;i++){
		
		atual = matriz[i].primeiro;
		
		while(atual!=NULL){
			
			ant = atual;
			atual = atual->prox;
			free(ant);
			
		}
		
	}
	
	free(matriz);
	
}
