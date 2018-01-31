#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "pilhaEncadenada.h"
#define TAM_BUFFER 100

void main() {
	FILE *p;
	Pilha* p1 = pilha_criar();
	
	p = fopen("arquivo.txt", "r");
	
    int aux = 0, lixo;
    char buffer[TAM_BUFFER], carac;
    
    while(!feof(p)) {
    	carac = fgetc(p);
    	if(carac == '\n') {
    		buffer[aux] = '\0';
    		contas(p, buffer);
    		aux = -1;
		} else if(carac == '\0') {
			contas(p, buffer);
			break;
		} else
			buffer[aux] = carac;
		
		aux++;
    }
    fclose(p);
}

void contas(Pilha* p, char* buffer) {
	int i = 0, j, aux = 0, l;
	double num, n;
	
	while(buffer[i] != '\0') {
		
		if(buffer[i] == '+')
			soma(p);
		else if(buffer[i] == '-')
			subtracao(p);
		else if(buffer[i] == '*')
			multiplicacao(p);
		else if(buffer[i] == '/')
			divisao(p);
		else {
			if(buffer[i] != ' ')
				aux++;
			
			if(buffer[i] == ' ') {
				
				num = atof(buffer+i-aux);
					
				if(num != 0) pilha_push(p, num); 
				aux = 0;
			}	
		}
		i++;
	}
	printf("\n%.0f", *pilha_pop1(p));
}

void soma(Pilha* p) {
	double num1, num2;
	pilha_pop2(p, &num1);
	pilha_pop2(p, &num2);
	pilha_push(p, (num1+num2));
}

void subtracao(Pilha* p) {
	double num1, num2;
	pilha_pop2(p, &num2);
	pilha_pop2(p, &num1);
	pilha_push(p, (num1-num2));
}

void multiplicacao(Pilha* p) {
	double num1, num2;
	pilha_pop2(p, &num1);
	pilha_pop2(p, &num2);
	pilha_push(p, (num1*num2));
}

void divisao(Pilha* p) {
	double num1, num2;
	pilha_pop2(p, &num2);
	pilha_pop2(p, &num1);
	pilha_push(p, (num1/num2));
}
