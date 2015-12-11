/**
 * Resolucao de Sistemas Lineares Esparsos
 * leitura.c
 * Leitura da matriz de entrada
 * Ver documentacao para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include "leitura.h"

/**
 *  Le matriz
 *
 *  @param arquivo nome da arquivo que possui a matriz
 *  @param tam ordem da matriz
 *  @param sor determina construcao especial da matriz para SOR
 *  @return matriz matriz lida
 *
 */
Coluna* le_matriz(char* arquivo, int *tam, int sor) {
	
	Coluna* matriz;
	FILE *f;
	
	f = fopen(arquivo, "r");
	
	if(f == NULL) {
		
		printf("Erro ao acessar %s\n", arquivo);
		return NULL;
		
	}
	
	int linhas, colunas, elementos, i, l, c;
	double valor;
	
	fscanf(f, "%d %d %d", &linhas, &colunas, &elementos);
	
	if(linhas != colunas) {
		
		printf("Coluna invalida.\n");
		return NULL;
		
	}
	
	matriz = cria_matriz(colunas);
	
	for(i = 0; i < elementos; i++) {
		
		fscanf(f, "%d %d %lf", &l, &c, &valor);
		
		if(sor==0)
			adiciona_elemento(l-1, c-1, valor, matriz, colunas);
		else
			adiciona_elemento(c-1, l-1, valor, matriz, colunas);
		
	}
	
	*tam = colunas;
	
	for(i = 0; i < colunas; i++){
		
		fscanf(f, "%lf", &valor);
		adiciona_elemento(i, colunas, valor, matriz, colunas);
		
	}
	
	fclose(f);
	
	return matriz;
	
}


