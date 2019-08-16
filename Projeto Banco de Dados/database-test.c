#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

void main() {
	Database* db = criarDatabase("Universidade");
	char* i[3] = {"ra", "nome", "nota"};
	char* j[3] = {"integer", "string", "float"};
	void* v[3] = {"1921959", "Vitor", "9.8"};
	void* p[3] = {"212121", "Teste", "0.1"};
	void* k[3] = {"343434", "Britto", "10"};
    criarTabela(db, "Alunos", i, j, 3);
    criarTupla(db, "Alunos", v, 3);
	criarTupla(db, "Alunos", p, 3);
	criarTupla(db, "Alunos", k, 3);
	
	char* e[2] = {"nome", "preco"};
	char* r[2] = {"string", "float"};
	void* v1[2] = {"leve", "5.5"};
	void* p1[2] = {"bom ", "0.1"};
	void* k1[2] = {"Teste1", "10"};
	criarTabela(db, "Ola", e, r, 2);
    criarTupla(db, "Ola", v1, 2);
	criarTupla(db, "Ola", p1, 2);
	criarTupla(db, "Ola", k1, 2);
	
	char* oi[3] = {"nota", "<", "5"};
	seleciona(db, "Alunos", oi);
}
