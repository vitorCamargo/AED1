#include <stdio.h>
#include <stdlib.h>
#include "filaSequencial.h"

void printInt(void* valor){
	int *p = (int*) valor;
	printf("%d", *p);
} 

void main() {
	T removed;
	
	Fila *q = fila_criar();
	fila_inserir(q,10);
	fila_inserir(q,20);
	fila_inserir(q,30);
	
	fila_remover1(q);
	fila_remover2(q, &removed);
	
	removed = *fila_primeiro(q);
	printf("\n%d", removed);
	
	printf("\n%d", fila_tamanho(q));
	
	fila_inserir(q,40);
	fila_inserir(q,50);
	fila_inserir(q,60);
	fila_inserir(q,70);
	
	printf("\n%d", fila_tamanho(q));
	
	printf("\n%d", fila_contem(q, 50));
	printf("\n%d", fila_contem(q, 51));
	
	fila_imprimir(q, printInt);
}
