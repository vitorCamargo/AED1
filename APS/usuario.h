#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "database.h"

Database* db;
char* ver[] = {"CREATE DATABASE ", "CREATE TABLE ", "INSERT INTO ", "SELECT*FROM ", "SELECT * FROM ", "SHOW TABLES"};

void lerQuery();
void verificaQuery(char buf[]);
void chama_bancoDados(char buf[]);
void chama_tabela(char buf[]);
void inserirDados(char buf[]);
void selecionarDados(char buf[]);
void mostrarTabelas();

void upper(char buf[]);
void progmMessage(int i);

void lerQuery() {
	char buf[1000], c;
	int aux = 0;
	progmMessage(0);
	
	do {
		scanf("%[^;]", buf);
		upper(buf);
		
		if(strcmp(buf, "HELP") == 0) progmMessage(1);
		else if(strcmp(buf, "CLS") == 0) system("cls");
		else if(strcmp(buf, "EXIT") == 0) progmMessage(3);
		else verificaQuery(buf);
		
		fflush(stdin);
	} while(strcmp(buf, "EXIT") != 0);
}

void verificaQuery(char buf[]) {
	if(strncmp(ver[0], buf, strlen(ver[0])) == 0) chama_bancoDados(buf);
	else if(strncmp(ver[1], buf, strlen(ver[1])) == 0) chama_tabela(buf);
	else if(strncmp(ver[2], buf, strlen(ver[2])) == 0) inserirDados(buf);
	else if(strncmp(ver[3], buf, strlen(ver[3])) == 0 || strncmp(ver[4], buf, strlen(ver[4])) == 0) selecionarDados(buf);
	else if(strcmp(ver[5], buf) == 0) mostrarTabelas();
	else progmMessage(2);
}

void chama_bancoDados(char buf[]) {
	int i, aux = 0;
	char nome[30];
	
	for(i = strlen(ver[0]); i < strlen(buf); i++) {
		if(buf[i] == ' ' || buf[i] == '"' || buf[i] == '(' || buf[i] == ')') {
			progmMessage(2);
			return;
		} else
			nome[aux] = buf[i];
		aux++;
	}
	nome[aux] = '\0';
	db = criarDatabase(nome);
	printf("Query OK, 1 row affected\nDatabase created\n");
}

void chama_tabela(char buf[]) {
	int i = strlen(ver[1]), j = 2, k = 0, aux = 0, n = 1;
	char nome[30], atributo[30], tipo[30];
	
	while(buf[i] != ' ' && buf[i] != '(') {
		nome[aux] = buf[i];
		aux++;
		i++;
	}
	
	for(i = strlen(ver[1]); i < strlen(buf); i++)
		if(buf[i] == ',') n++;	
	
	char** tipos = (char**) malloc(n*sizeof(char*));
	char** atributos = (char**) malloc(n*sizeof(char*));
	for(i = 0; i < n; i++) {
		atributos[i] = malloc(30*sizeof(char));
		tipos[i] = malloc(30*sizeof(char));
	}
	
	aux = 0;
	
	for(i = (strlen(ver[1]) + strlen(nome) + 1); i < strlen(buf); i++) {
		if(buf[i] == ' ' || buf[i] == ',' || buf[i] == ')') {
			if(buf[i] == ',' && buf[i+1] == ' ') i++;
			
			if(j%2 == 0) {
				atributo[aux] = '\0';
				strcpy(atributos[k], atributo);
				strcpy(atributo, "");
			} else {
				tipo[aux] = '\0';
				strcpy(tipos[k], tipo);
				strcpy(tipo, "");
				k++;
			}
			aux = 0;
			j++;
		} else {
			if(j%2 == 0) atributo[aux] = buf[i];
			else tipo[aux] = buf[i];	
			aux++;
		}
	}
	if(criarTabela(db, nome, atributos, tipos, n) == -1) progmMessage(2);
	
	for(i = 0; i < n; i++) {
		free(tipos[i]);
		free(atributos[i]);
	}
	free(tipos);
	free(atributos);
	
	printf("Query OK, 0 row affected\nTable created\n");
}

void inserirDados(char buf[]) {
	int i = strlen(ver[2]), k = 0, aux = 0, n = 1;
	char nome[30], dado[30];
	
	while(buf[i] != ' ' && buf[i] != '(') {
		nome[aux] = buf[i];
		aux++;
		i++;
	}
	
	for(i = strlen(ver[2]); i < strlen(buf); i++)
		if(buf[i] == ',') n++;
	
	void** dados = (void**) malloc(n*sizeof(void*));
	aux = 0;
	
	for(i = (strlen(ver[2]) + strlen(nome) + 1); i < strlen(buf); i++) {
		if(buf[i] == '\"' || buf[i] == '\'') {
		} else if(buf[i] == ' ' || buf[i] == ',' || buf[i] == ')') {
			if(buf[i] == ',' && buf[i+1] == ' ') i++;
			
			dado[aux] = '\0';
			dados[k] = malloc(strlen(dado)*sizeof(char));
			strcpy(dados[k], dado);
			strcpy(dado, "");
			aux = 0;
			k++;
		} else {
			dado[aux] = buf[i];	
			aux++;
		}
	}
	
	if(criarTupla(db, nome, dados, n) == -1) progmMessage(2);
	
	for(i = 0; i < n; i++) free(dados[i]);
	free(dados);
	
	printf("Query OK, 1 row affected\n");
}

void selecionarDados(char buf[]) {
	int i, k = -1, aux = 0, n = 3, op;
	char nome[30], cond[30];
	
	if(strncmp(ver[3], buf, strlen(ver[3])) == 0) op = 3;
	else op = 4;
	
	i = strlen(ver[op]);
	
	while(buf[i] != ' ') {
		nome[aux] = buf[i];
		aux++;
		i++;
	}
	
	char** condicao = (char**) malloc(n*sizeof(char*));
	for(i = 0; i < n; i++) {
		condicao[i] = malloc(30*sizeof(char));
		strcpy(condicao[i], "");
	}
	
	aux = 0;
	
	for(i = (strlen(ver[op]) + strlen(nome) + 1); i <= strlen(buf); i++) {
		if(buf[i] == '\"' || buf[i] == '\'') {
		} else if(buf[i] == ' ' || i == strlen(buf)) {
			if(buf[i] == ',' && buf[i+1] == ' ') i++;
			
			cond[aux] = '\0';
			if(strcmp(cond, "WHERE") != 0 && k == -1) return;
			if(k >= 0) strcpy(condicao[k], cond);
			
			strcpy(cond, "");
			aux = 0;
			k++;
		} else {
			cond[aux] = buf[i];	
			aux++;
		}
	}
	if(seleciona(db, nome, condicao) == -1) progmMessage(2);
	
	for(i = 0; i < n; i++) free(condicao[i]);
	free(condicao);
	printf("\n");
}

void mostrarTabelas() {
	imprimirDatabase(db);
}

void upper(char buf[]) {
	int i;
	
	for(i = 0; i < strlen(buf); i++)
        buf[i] = toupper(buf[i]);	
}

void progmMessage(int i) {
	if(i == 0) printf("***Welcome to the MySQL simulator monitor.  Commands end with ;\nCopyright (c) 2014, 2017, HEXA6ON {V} and/or its affiliates. All rights reserved by Vitor.\nType 'help;' for help. Or 'cls;' to clear the monitor'\n\n");
	if(i == 1) printf("EXAMPLES:\ncreate database Universidade;\ncreate table Alunos(ra integer, nome string, nota float);\ninsert into Alunos(1921959, 'Vitor', 4.5);\ninsert into Alunos(21212, 'Teste', 10);\nselect*from Alunos where nota > 5;\nType 'exit;' to exit the programm. Or 'show tables;' to see the entire database\n\n");
	if(i == 2) printf("You have an error in your SQL syntax; check the manual that corresponds to your MySQL server version\n");
	if(i == 3) printf("\n***Goodbye, give me 10!");
}
