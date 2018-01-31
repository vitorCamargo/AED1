typedef int T;

typedef struct no{
    T dado;
    struct no* prox;
} No;

typedef struct{
    No* primeiro;
    No* ultimo;
    int qtde;
} Fila;

Fila* fila_criar();
void fila_desalocar(Fila* f);
int fila_inserir(Fila* f, T elemento);
T* fila_remover1(Fila* f);
int fila_remover2(Fila* f, T* endereco);
T* fila_primeiro(Fila* f);
int fila_tamanho(Fila* f);
int fila_contem(Fila* f, T elemento);
void fila_imprimir(Fila* f, void (*printElemento)(void*));

Fila* fila_criar() {
	Fila* f = (Fila*) malloc(sizeof(Fila));
	
	f->primeiro = NULL;
	f->ultimo = NULL;
	f->qtde = 0;
	
	return f;
}

void fila_desalocar(Fila* f) {
	int i;
	
	for(i = 0; i < f->qtde; i++)
		fila_remover1(f);
	
	free(f);
}

int fila_inserir(Fila* f, T elemento) {
	if(f == NULL) return 0;
	
	No* o = (No*) malloc(sizeof(No));
	
	o->dado = elemento;
	o->prox = NULL;
	
	if(f->primeiro == NULL) f->primeiro = o;
	else f->ultimo->prox = o;
		
	f->ultimo = o;
	f->qtde++;
	
	return 1;
}

T* fila_remover1(Fila* f) {
	if(f == NULL) return NULL;
	if(f->qtde == 0) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	*r = f->primeiro->dado;
	
	No* n = f->primeiro;
	f->primeiro = f->primeiro->prox;
	f->qtde--;
	
	free(n);
	return r;
}

int fila_remover2(Fila* f, T* endereco) {
	if(f == NULL) return 0;
	if(f->qtde == 0) return 0;
	
	*endereco = f->primeiro->dado;
	
	No* n = f->primeiro;
	f->primeiro = f->primeiro->prox;
	f->qtde--;
	
	free(n);
	return 1;
}

T* fila_primeiro(Fila* f) {
	if(f == NULL) return NULL;
	if(f->qtde == 0) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	*r = f->primeiro->dado;
	
	return r;
}

int fila_tamanho(Fila* f) {
	if(f == NULL) return 0;
	
	return f->qtde;
}

int fila_contem(Fila* f, T elemento) {
	if(f == NULL) return 0;
	if(f->qtde == 0) return 0;
	
	No* o = f->primeiro;
	int i;
	
	for(i = f->qtde-1; i >= 0; i--) {
		if(o->dado == elemento)
			return 1;
		o = o->prox;
	}
	
	return 0;
}

void fila_imprimir(Fila* f, void (*printElemento)(void*)) {
	if(f == NULL)
		printf("\nFila não encontrada");
		
	No* o = f->primeiro;
	int i;
	
	printf("\nFila: ");
	for(i = f->qtde-1; i >= 0; i--) {
		printf("|");
		printElemento(&(o->dado));
		o = o->prox;
		printf("| ");
	}
	free(o);
	
	printf("\n");
}
