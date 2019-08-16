
#include <stdlib.h>
#include <stdio.h>
#include "pilhaEncadenada.h"

void printInt(void* valor) {
	int *p = (int*) valor;
	printf("%d", *p);
} 

void main() {
	Tipo oi[3];
	Pilha* p1 = pilha_criar();
	Pilha* p2 = pilha_criar();
	printf("\n%d", pilha_push(p1, 1));
	printf("\n%d", pilha_push(p1, 2));
	printf("\n%d", pilha_push(p1, 3));
	pilha_imprimir(p1, printInt);
}
