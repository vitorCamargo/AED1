#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhaEncadenada.h"

int main() {
	FILE *p;
	Pilha* p1 = pilha_criar();
	char carac, cmp;
	p = fopen("arquivo.txt", "r");
	
	if(p == NULL) printf("\nErro na abertura do arquivo!\n");
	else {
		while(!feof(p)) {
			carac = fgetc(p);
			if(ferror(p)) printf("\nErro na leitura do caractere\n");
			
			if(carac == '{' || carac == '[' || carac == '('){
				pilha_push(p1, carac);
			}
			
			if((carac == '}' || carac == ']' || carac == ')') && pilha_tamanho(p1) == 0) {
				printf("\nDelimitador de fechamento sobrando");
				return 0;	
			}
		 	
			if(carac == '}') {
				pilha_topo(p1, &cmp);
				
				if(cmp == '{')
					pilha_pop2(p1, &cmp);
				else {
					printf("\nIncompatibilidade de delimitadores");
					return 0;
				}
			}
			else if(carac == ']'){
				pilha_topo(p1, &cmp);
				
				if(cmp == '[')
					pilha_pop2(p1, &cmp);
				else {
					printf("\nIncompatibilidade de delimitadores");
					return 0;
				}
			}
			else if(carac == ')'){
				pilha_topo(p1, &cmp);
				
				if(cmp == '(')
					pilha_pop2(p1, &cmp);
				else {
					printf("\nIncompatibilidade de delimitadores");
					return 0;
				}
			}
		}
	}
	fclose(p);
	
	if(pilha_tamanho(p1) != 0) 
		printf("\nDelimitador de fechamento faltando");
	else
		printf("\nOK!");
	
	pilha_desalocar(p1);
	return 1;
}
