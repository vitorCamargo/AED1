#define TAM_TABELA 1
#define TAM_TUPLA 1

typedef struct noDado {
    void* dado;
    int tamDado;
    struct noDado* dir;
    struct noDado* esq;
    struct noDado* cima;
    struct noDado* baixo;
} NoDado;

typedef struct noAtributo {
    char nome[30];
    char tipo[30];
    NoDado* valores;
    struct noAtributo* dir;
    struct noAtributo* esq;
} NoAtributo;

typedef struct {
    char nome[30];
    NoAtributo* atributos;
    NoDado** tuplas;
    unsigned short int tamVetor;
    unsigned short int qtdeTuplas;
} Tabela;

typedef struct {
    char nome[30];
    NoAtributo* atributos;
    Tabela** tabelas;
    unsigned short int tamTabelas;
    unsigned short int qtdeTabelas;
} Database;

//PROTOTIPOS PRIM�RIOS
Database* criarDatabase(char* nome);
int criarTabela(Database* db, char* nome, char** atributos, char** tipos, int qtdeAtributos);
int criarTupla(Database* db, char* nome, void** dados, int qtdeDados);
int seleciona(Database* db, char* nome, char** condicao);

//PROTOTIPOS AUXILIARES
void printDado(void* dado, char* tipo);
void imprimirTupla(NoDado* sentinelaTupla, NoAtributo* sentinelaAtributo);
void imprimirTabela(Tabela* table);
void imprimirAtributos(Tabela* table);
void imprimirDatabase(Database* db);

Tabela* selecionaTabela(Database* db, char* nome);
NoAtributo* novoAtributo(char* atributo, char* tipo);
NoDado* novoDado(void* dado);
void adicionaAtributo(Tabela* tb, NoAtributo* novo);
void adicionaDado(NoDado* sentinela, NoDado* atributo, NoDado* novo);
int verificaCondicao(char* tipo, char* dado1, char* dado2, char* condicao);

void aumentaTabelas(Database* db);
void aumentaTuplas(Tabela* tb);

//FUN��ES PRIM�RIAS
Database* criarDatabase(char* nome) {
	Database* db = (Database*) malloc(sizeof(Database));
	db->tabelas = (Tabela**) malloc(TAM_TABELA*sizeof(Tabela*));
	
	strcpy(db->nome, nome);
	db->tamTabelas = TAM_TABELA;
	db->qtdeTabelas = 0;
	
	return db;
}

int criarTabela(Database* db, char* nome, char** atributos, char** tipos, int qtdeAtributos) {
	if(db == NULL) return -1;
	if(db->qtdeTabelas == db->tamTabelas) aumentaTabelas(db);
	int i;
	
	Tabela* tb = (Tabela*) malloc(sizeof(Tabela));
	tb->tuplas = (NoDado**) malloc(TAM_TUPLA*sizeof(NoDado*));
	
	strcpy(tb->nome, nome);
	tb->tamVetor = TAM_TUPLA;
	tb->qtdeTuplas = 0;
	
	tb->atributos = (NoAtributo*) malloc(sizeof(NoAtributo));
	tb->atributos->dir = tb->atributos;
	tb->atributos->esq = tb->atributos;
	
	for(i = 0; i < qtdeAtributos; i++)
		adicionaAtributo(tb, novoAtributo(atributos[i], tipos[i]));
		
	db->tabelas[db->qtdeTabelas] = tb;
	db->qtdeTabelas++;
	return 0;
}

int criarTupla(Database* db, char* nome, void** dados, int qtdeDados) {
	Tabela* tb = selecionaTabela(db, nome);	
	if(tb == NULL) return -1;
	if(db == NULL) return -1;
	if(tb->qtdeTuplas == tb->tamVetor) aumentaTuplas(tb);

	int i;
	
	NoDado* qry = (NoDado*) malloc(sizeof(NoDado));
	qry->dir = qry;
	qry->esq = qry;
	tb->tuplas[tb->qtdeTuplas] = qry;
	
	NoAtributo* val = tb->atributos->dir; 
	for(i = 0; i < qtdeDados; i++) {
		adicionaDado(tb->tuplas[tb->qtdeTuplas], val->valores, novoDado(dados[i]));
		val = val->dir;
	}
	
	tb->qtdeTuplas++;
	return 0;
}

int seleciona(Database* db, char* nome, char** condicao) {
	Tabela* tb = selecionaTabela(db, nome);
	if(tb == NULL) return -1;
	if(db == NULL) return -1;
	
	if(strcmp(condicao[0], "") == 0) imprimirTabela(tb);
	else {
		int i;
		NoAtributo* o = tb->atributos->dir;
		
		while(o != tb->atributos) {
			if(strcmp(o->nome, condicao[0]) == 0) break;
			o = o->dir;
		}
		NoDado* dado = o->valores->baixo;
		
		imprimirAtributos(tb);
		for(i = 0; i < tb->qtdeTuplas; i++) {
			if(verificaCondicao(o->tipo, dado->dado, condicao[2], condicao[1])) 
				imprimirTupla(tb->tuplas[i], tb->atributos);
			dado = dado->baixo;
		}
	}
	return 0;
}

//FUN��ES AUXILIARES
void printDado(void* dado, char* tipo) {
	printf("%s\t\t", (char*)dado);
}

void imprimirTupla(NoDado* sentinelaTupla, NoAtributo* sentinelaAtributo) {  
	NoDado* auxDado = sentinelaTupla->dir;
    NoAtributo* auxAtributo = sentinelaAtributo->dir;
    printf("\n");
    
    while(auxDado != sentinelaTupla) {
        printDado(auxDado->dado, auxAtributo->tipo);
        auxDado = auxDado->dir;
        auxAtributo = auxAtributo->dir;
    }

}

void imprimirTabela(Tabela* table) {
	int i;
	printf("\n\nTabela: %s\n", table->nome);
    imprimirAtributos(table);
    
    for (i = 0; i < table->qtdeTuplas; i++)
        imprimirTupla(table->tuplas[i], table->atributos);  
		
	printf("\n");      
}

void imprimirAtributos(Tabela* table) {
	NoAtributo* aux = table->atributos->dir;
    while(aux != table->atributos) {
        printf("%s\t\t", aux->nome);
        aux = aux->dir;
    }
}

void imprimirDatabase(Database* db) {
	int i;
    printf("Database: %s\n", db->nome);
    printf("TABELAS\n");
    
    for (i = 0; i < db->qtdeTabelas; i++)
        imprimirTabela(db->tabelas[i]);
}

NoAtributo* novoAtributo(char* atributo, char* tipo) {
	NoAtributo* novo = (NoAtributo*) malloc(sizeof(NoAtributo));
	
	strcpy(novo->nome, atributo);
	strcpy(novo->tipo, tipo);
	
	novo->valores = (NoDado*) malloc(sizeof(NoDado));
	novo->valores->cima = novo->valores;
	novo->valores->baixo = novo->valores;
	
	novo->dir = NULL;
	novo->esq = NULL;
	
	return novo;
}

Tabela* selecionaTabela(Database* db, char* nome) {
	int i;
	
	for(i = 0; i < db->qtdeTabelas; i++)
		if(strcmp(db->tabelas[i]->nome, nome) == 0) return db->tabelas[i];
}

NoDado* novoDado(void* dado) {
	NoDado* novo = (NoDado*) malloc(sizeof(NoDado));
	
	novo->dado = malloc(sizeof(dado));
	memcpy(novo->dado, dado, sizeof(dado));
	
	novo->cima = NULL;
	novo->baixo = NULL;
	novo->dir = NULL;
	novo->esq = NULL;
	
	return novo;	
}

void adicionaAtributo(Tabela* tb, NoAtributo* novo) {
	novo->esq = tb->atributos->esq;
	novo->dir = tb->atributos;
	
	tb->atributos->esq->dir = novo;
	tb->atributos->esq = novo;
}

void adicionaDado(NoDado* sentinela, NoDado* atributo, NoDado* novo) {
	novo->esq = sentinela->esq;
	novo->dir = sentinela;
	sentinela->esq->dir = novo;
	sentinela->esq = novo;
	
	novo->cima = atributo->cima;
	novo->baixo = atributo;
	atributo->cima->baixo = novo;
	atributo->cima = novo;
}

int verificaCondicao(char* tipo, char* dado1, char* dado2, char* condicao) {
	int result = 0;
	if(strcmp(tipo, "STRING") == 0 && strcmp(condicao, "=") == 0) {
		if(strcmp(dado1, dado2) == 0) result = 1;
	} else if(strcmp(tipo, "INTEGER") == 0) {
		int valor1 = atoi(dado1); 
		int valor2 = atoi(dado2);
		
		if(strcmp(condicao, "<") == 0 && valor1 < valor2) result = 1;
		else if(strcmp(condicao, ">") == 0 && valor1 > valor2) result = 1;
		else if(strcmp(condicao, "=") == 0 && valor1 == valor2) result = 1;		
	} else {
		float valor1 = atof(dado1); 
		float valor2 = atof(dado2);
		
		if(strcmp(condicao, "<") == 0 && valor1 < valor2) result = 1;
		else if(strcmp(condicao, ">") == 0 && valor1 > valor2) result = 1;
		else if(strcmp(condicao, "=") == 0 && valor1 == valor2) result = 1;
	}
	
	return result;
}

void aumentaTabelas(Database* db) {
	int i;
	Tabela** vet = (Tabela**) calloc(2*db->tamTabelas, sizeof(Tabela*));	
	
	for(i = 0; i < db->tamTabelas; i++)
		vet[i] = db->tabelas[i]; 
	free(db->tabelas);
	
	db->tabelas = (Tabela**) calloc(2*db->tamTabelas, sizeof(Tabela*));
	for(i = 0; i < db->tamTabelas; i++)
		db->tabelas[i] = vet[i]; 
	free(vet);
	db->tamTabelas = 2*(db->tamTabelas);
}

void aumentaTuplas(Tabela* tb) {
	int i;
	NoDado** vet = (NoDado**) calloc(2*tb->tamVetor, sizeof(NoDado*));	
	
	for(i = 0; i < tb->tamVetor; i++)
		vet[i] = tb->tuplas[i]; 
	free(tb->tuplas);
	
	tb->tuplas = (NoDado**) calloc(2*tb->tamVetor, sizeof(NoDado*));
	for(i = 0; i < tb->tamVetor; i++)
		tb->tuplas[i] = vet[i]; 
	free(vet);
	tb->tamVetor = 2*(tb->tamVetor);
}
