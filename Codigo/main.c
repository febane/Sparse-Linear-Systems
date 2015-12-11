/**
 * Resolucao de Sistemas Lineares Esparsos
 * main.c
 * Arquivo Principal para a Resolucao
 * de Sistemas Lineares Esparsos
 * Ver relatorio para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include <stdio.h>
#include <string.h>
#include "leitura.h"
#include "gauss.h"
#include "sor.h"


int main(int argc, char *argv[]) {
	
	if(argc < 3) {
	
		printf("Usage: ./main algoritmo [tolerancia] [relaxacao] arquivo\n");
		return 1;
		
	}
	
	int tam;
	
	if(!strcmp(argv[1],"gauss")) {
		
		Coluna *matriz = le_matriz(argv[2], &tam, 0);
		
		if(matriz == NULL)
			return 2;
		else{
			
			resolve_gauss(matriz, tam);
			
		}
		
		free_matriz(tam, matriz);
		
	}
	else if(!strcmp(argv[1],"sor")){
		
		Coluna *matriz = le_matriz(argv[4], &tam, 1);
		double omega, toler;
		
		if(matriz==NULL)
			return 2;
		else{
			
			sscanf(argv[2], "%lf", &toler);
			sscanf(argv[3], "%lf", &omega);
			
			resolve_sor2(matriz, tam, omega, toler);
			
		}
		
		free_matriz(tam, matriz);
		
	}
	else{
		
		printf("Algoritmo invalido.\nUsage: ./main algoritmo [tolerancia] [relaxacao] arquivo\n");
		return 1;
		
	}
	
	return 0;
}


