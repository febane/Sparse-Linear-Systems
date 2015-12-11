/**
 * Resolucao de Sistemas Lineares Esparsos
 * sor.c
 * Resolução do sistema por SOR
 * Ver relatorio para mais informacoes
 * 
 * @author Fernando Barbosa Neto
 * @author Jeferson de Oliveira Batista
 * 
 * @version 1.0
 * 
 */


#include "sor.h"

/**
 *  Resolve sistema por SOR (primeira implementacao)
 *
 *  @param matriz matriz do sistema
 *  @param n ordem da matriz
 *  @param omega parametro de relaxacao
 *  @param toler toleranicia
 *
 */
void resolve_sor(Coluna *matriz, int n, double omega, double toler){
	
	int i, j, it=0;
	double x[n], r[n], soma, v[n], normanum, normaden, t, Elapsed_Time;
	Elemento *atual[n+1];
	struct timespec Start, End;
	
	clock_gettime(CLOCK_MONOTONIC, &Start);
	
	atual[n] = matriz[n].primeiro;
	for(i=0;i<n;i++){
		
		atual[i] = matriz[i].primeiro;
		while(atual[i]->l < i)
			atual[i] = atual[i]->prox;
		r[i] = 1/atual[i]->v;
		
		for(j=0;j<n;j++){
			
			if(i!=j){
				
				atual[j] = matriz[j].primeiro;
				while(atual[j] != NULL && atual[j]->l < i)
					atual[j] = atual[j]->prox;
				if(atual[j] != NULL && atual[j]->l == i){
					atual[j]->v *= r[i];
				}
				
				
			}
			
		}
		
		atual[n]->v *= r[i];
		x[i] = atual[n]->v;
		atual[n] = atual[n]->prox;
		
	}
	
	while(1){
		
		it++;
		
		for(j=0;j<n+1;j++)
			atual[j] = matriz[j].primeiro;
		
		for(i=0;i<n;i++){
			
			soma = 0.0;
			
			for(j=0;j<n;j++){
				
				if(i!=j){
					
					atual[j] = matriz[j].primeiro;
					while(atual[j] != NULL && atual[j]->l < i)
						atual[j] = atual[j]->prox;
					if(atual[j] != NULL && atual[j]->l == i)
						soma += atual[j]->v*x[j];
					
				}
				
			}
			
			v[i] = x[i];
			x[i] = omega*(atual[n]->v-soma)+(1.0-omega)*x[i];
			atual[n] = atual[n]->prox;
			
		}
		
		normanum = 0.0;
		normaden = 0.0;
		
		for(i=0;i<n;i++){
			
			t = fabs(x[i]-v[i]);
			
			if(t>normanum)
				normanum = t;
			if(fabs(x[i])>normaden)
				normaden = fabs(x[i]);
			
		}
		
		if(normanum/normaden <= toler)
			break;
		
	}
	
	clock_gettime(CLOCK_MONOTONIC, &End);
	Elapsed_Time = End.tv_sec - Start.tv_sec + 1e-9*(End.tv_nsec-Start.tv_nsec);
	printf("O tempo de execucao do trecho foi %lf segundos\n", Elapsed_Time);
	
	saida_de_dados(n, x);
	
}

/**
 *  Resolve sistema por SOR (segunda implementacao)
 *
 *  @param matriz matriz do sistema
 *  @param n ordem da matriz
 *  @param omega parametro de relaxacao
 *  @param toler toleranicia
 *
 */
void resolve_sor2(Coluna *matriz, int n, double omega, double toler){
	
	int i, it=0;
	double x[n], r, soma, v[n], t, Elapsed_Time;
	struct timespec Start, End;
	
	//atual determina sobre qual linha serão realizadas as operações;
	Elemento *atual[n+1];
	
	//inicio da contagem do tempo
	clock_gettime(CLOCK_MONOTONIC, &Start);
	
	//seta atual[n] para primeiro valor do vetor independente
	atual[n] = matriz[n].primeiro;
	
	//ajuste do vetor x a ser iterado e dos valores da matriz
	for(i=0;i<n;i++){
		
		//busca diagonal principal
		atual[i] = matriz[i].primeiro;
		while(atual[i]->l < i)
			atual[i] = atual[i]->prox;
		
		//armazena inverso do valor de elemento da diagonal principal em r
		r = 1/atual[i]->v;
		
		//multiplica elemento da mesma linha da matriz por r
		for(atual[i] = matriz[i].primeiro; atual[i] != NULL; atual[i] = atual[i]->prox)
			if(i!=atual[i]->l)
				atual[i]->v *= r;
		
		//multiplica elemento da mesma linha do vetor independente por r
		atual[n]->v *= r;
		
		//seta valor em x
		x[i] = atual[n]->v;
		
		//avanca no vetor independente
		atual[n] = atual[n]->prox;
		
	}
	
	//iteracoes do SOR
	while(1){
		
		//incrementa quantidade de iteracoes
		it++;
		
		//seta atual para os primeiros elementos das linhas
		for(i=0;i<n+1;i++)
			atual[i] = matriz[i].primeiro;
		
		//transformacao de x
		for(i=0;i<n;i++){
			
			//seta acumulador
			soma = 0.0;
			
			//acumula
			for(atual[i] = matriz[i].primeiro; atual[i] != NULL; atual[i] = atual[i]->prox){
				
				//valor de x multiplicando elemento da matriz correspondente e acumulando resultado
				if(i!=atual[i]->l)
					soma += atual[i]->v*x[atual[i]->l];
				
			}
			
			//v possui os antigos valores de x para calcular erro posteriormente
			v[i] = x[i];
			
			//recebe novo valor para x
			x[i] = omega*(atual[n]->v-soma)+(1.0-omega)*x[i];
			
			//avanca no vetor independente
			atual[n] = atual[n]->prox;
			
		}
		
		//numerador para calculo do erro, aproveitando variavel
		soma = 0.0;
		
		//denominador para calculo do erro, aproveitando variavel
		r = 0.0;
		
		//seta numerador e denominador
		for(i=0;i<n;i++){
			
			//t guarda diferenca entre valores de x antes e depois da ultima iteracao
			t = fabs(x[i]-v[i]);
			
			//maior valor de t sera o numerador
			if(t>soma)
				soma = t;
			
			//maior valor absoluto em x sera o denominador
			if(fabs(x[i])>r)
				r = fabs(x[i]);
			
		}
		
		//checa se erro e menor que a tolerancia
		if(soma/r <= toler)
			break;
		
	}
	
	//termina contagem e printa tempo gasto pelo algoritmo
	clock_gettime(CLOCK_MONOTONIC, &End);
	Elapsed_Time = End.tv_sec - Start.tv_sec + 1e-9*(End.tv_nsec-Start.tv_nsec);
	printf("O tempo de execucao do trecho foi %lf segundos\n", Elapsed_Time);
	
	//mostra a quantidade de iterações
	printf("A quantidade de iteracoes eh: %d\n", it);
	
	//escreve vetor-resposta x na saida
	saida_de_dados(n, x);
	
}
