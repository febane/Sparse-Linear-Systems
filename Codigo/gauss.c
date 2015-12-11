/**
 * Resolucao de Sistemas Lineares Esparsos
 * gauss.c
 * Resolução do sistema por eliminação de Gauss
 * Ver relatorio para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include "gauss.h"

/**
 *  Resolve sistema por Gauss
 *
 *  @param matriz matriz do sistema
 *  @param n ordem da matriz
 *
 */
void resolve_gauss(Coluna *matriz, int n){
	
	int k, j, linha;
	double m, resp[n], soma, Elapsed_Time;
	struct timespec Start, End;
	
	//atual trabalha como escalonador e subatual o escalonado
	Elemento *atual[n+1], *subatual[n+1];
	
	//tenta setar os ponteiros de atual para a primeira linha da matriz
	for(j=0;j<n+1;j++)
		atual[j]=matriz[j].primeiro;
	
	//inicio da contagem do tempo
	clock_gettime(CLOCK_MONOTONIC, &Start);
	
	//inicio da eliminacao de gauss
	//lembrar que k atinge ate a ultima linha
	for(k=0;k<n-1;k++){
		
		//tenta setar os ponteiros de atual para a linha do escalonador
		for(j=k;j<=n;j++)
			while( atual[j]->l < k)
				atual[j] = atual[j]->prox;
		
		for( subatual[k]=atual[k]->prox ; subatual[k] != NULL ; subatual[k] = subatual[k]->prox ){
			
			//variavel linha recebe numero da linha a ser escalonada
			linha = subatual[k]->l;
			
			//fator multiplicador
			m = -(subatual[k]->v)/(atual[k]->v);
			
			for(j=k;j<n;j++){
				
				//verifica se o j-esimo elemento do escalonador e nao-nulo
				if(atual[j]->prox != NULL && atual[j]->l == k)
					subatual[j] = atual[j]->prox;
				else
					continue;
				
				//seta o j-esimo elemento do escalonado
				while(subatual[j] != NULL && subatual[j]->l<linha)
						subatual[j] = subatual[j]->prox;
				
				//se o j-esimo elemento do escalonado nao existe, cria-se-o
				if(subatual[j]==NULL || subatual[j]->l!=linha){
					
					//cria elemento
					adiciona_elemento(linha, j, 0.0, matriz, n);
					
					//procura elemento criado na matriz para iniciar escalonamento do mesmo
					subatual[j] = atual[j]->prox;
					while(subatual[j] != NULL)
						if(subatual[j]->l >= linha)
							break;
						else
							subatual[j] = subatual[j]->prox;
					
				}
				
				//escalona j-esimo elemento da matriz
				subatual[j]->v += m*(atual[j]->v);
				
			}
			
			//seta o termo do vetor independente em subatual para ser escalonado
			subatual[n] = atual[n];
			while(subatual[n]->l != linha)
				subatual[n] = subatual[n]->prox;
			
			//escalona termo independente
			subatual[n]->v += m*(atual[n]->v);
			
		}
		
	}
	//matriz ja escalonada
	
	//inicio das substituicoes retroativas
	//determina o valor na n-ésima variável
	resp[n-1] = atual[n]->prox->v/atual[n-1]->prox->v;
	
	//iteracoes que prosseguem com as substituicoes retroativas
	for(linha=n-2; linha>=0; atual[n] = atual[n]->ant){
		
		soma = 0.0;
		
		for(j=linha+1;j<n;j++){
			
			//sobe atual na coluna
			if(atual[j]!=NULL && atual[j]->l!=linha)
				atual[j] = atual[j]->ant;
			
			//acumula valores em soma
			if(atual[j]!=NULL && atual[j]->l==linha)
				soma += atual[j]->v*resp[j];
			
		}
		
		//pega resultado de soma
		resp[linha] = (atual[n]->v-soma)/atual[linha]->v;
		
		//sobe uma linha na matriz
		linha--;
		
	}
	
	//termina contagem e printa tempo gasto pelo algoritmo
	clock_gettime(CLOCK_MONOTONIC, &End);
	Elapsed_Time = End.tv_sec - Start.tv_sec + 1e-9*(End.tv_nsec-Start.tv_nsec);
	printf("O tempo de execucao do trecho foi %lf segundos\n", Elapsed_Time);
	
	//escreve resposta na saida
	saida_de_dados(n, resp);
	
}
