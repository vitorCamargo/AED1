#include <stdio.h>
#include <stdlib.h>
#include "listaSentinela.h"

void printInt(void* valor){
	int *p = (int*) valor;
	printf("%d", *p);
} 

int compInt(void* valor1, void* valor2){
	int *p = (int*) valor1;
	int *q = (int*) valor2;
	
	if(*p == *q)
		return 1;
	
	return 0;
} 

void main() {
	T removed;
	
	Lista *l = lista_cria();
	lista_insere_fim(l, 5);
	lista_insere_fim(l, 10);
	lista_insere_fim(l, 20);
	lista_insere_fim(l, 30);
	lista_insere(l, 1, 0);
	lista_insere(l, 15, 3);
	lista_insere(l, 35, 6);
	
	lista_remove1(l, 0);
	lista_remove1(l, 5);
	lista_remove2(l, 4, &removed);
	printf("\n%d", removed);
	lista_remove_elemento(l, 15, compInt);
	
	printf("\n%d", *lista_busca1(l, 2));
	lista_busca2(l, 1, &removed);
	printf("\n%d", removed);
	
	printf("\n\n%d", lista_contem(l, 1, compInt));
	printf("\n\n%d", lista_posicao(l, 1, compInt));
	printf("\n\n%d", lista_tamanho(l));/**/
	
	lista_imprime(l, printInt);
}
