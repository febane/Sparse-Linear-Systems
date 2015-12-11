all: listas leitura gauss sor saida programa

all-nodoc: listas leitura gauss saida sor programa

listas: listas.c
	gcc -Wall -c listas.c

leitura: leitura.c
	gcc -Wall -c leitura.c

gauss: gauss.c
	gcc -Wall -c gauss.c

sor: sor.c
	gcc -Wall -c sor.c

saida: saida.c
	gcc -Wall -c saida.c

programa: main.c listas.c leitura.c gauss.c sor.c saida.c
	gcc -Wall -o programa main.c listas.o leitura.o gauss.o sor.o saida.o -lrt

clean: 
	rm *.o programa
