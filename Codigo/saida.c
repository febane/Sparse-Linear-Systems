/**
 * Resolucao de Sistemas Lineares Esparsos
 * saida.c
 * Escrita do resultado em arquivo de saída
 * Ver relatorio para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include "saida.h"

/**
 *  Escreve resposta em arquivo
 *
 *  @param n tamanho do vetor-resposta
 *  @param resp vetor que contem resposta
 *
 */
void saida_de_dados(int n, double resp[]){
	
	int i;
	FILE *f;
	
	f = fopen("saida_exemplo.txt", "w");
	
	if(f == NULL) {
		
		printf("Erro ao acessar saida_exemplo.txt\n");
		return;
		
	}
	
	fprintf(f, "%d\n", n);
	
	for(i=0;i<n;i++)
		fprintf(f, "%g\n", resp[i]);
	
	fclose(f);
	
}
