typedef int Tipo;

typedef struct no {
	Tipo dado;
	struct no* prox;
} No;

typedef struct {
	No* topo;
	int qtde; //topo
} Pilha;

Pilha* pilha_criar();
void pilha_desalocar(Pilha* p);
int pilha_push(Pilha* p, Tipo elemento);
Tipo* pilha_pop1(Pilha* p);
int pilha_pop2(Pilha* p, Tipo* endereco);
int pilha_topo(Pilha* p, Tipo* endereco);
int pilha_tamanho(Pilha* p);
void pilha_imprimir(Pilha* p, void (*printElemento)(void*));

Pilha* pilha_criar() {
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->topo = (No*) malloc(sizeof(No));
	
	p->topo->prox = NULL;
	p->qtde = 0;
	
	return p;
}

void pilha_desalocar(Pilha* p) {
	free(p);
}

int pilha_push(Pilha* p, Tipo elemento) {
	if(p == NULL) return 0;
	
	Pilha* o = (Pilha*) malloc(sizeof(Pilha));
	o->topo = (No*) malloc(sizeof(No));
	
	o->topo->dado = elemento;
	o->topo->prox = p->topo;
	p->topo = o->topo;
	p->qtde++;
	
	return 1;
}

Tipo* pilha_pop1(Pilha* p) {
	if(p == NULL) return NULL;
	if(p->qtde == 0) return NULL;
	
	Pilha* o = (Pilha*) malloc(sizeof(Pilha));
	o->topo = p->topo;
	p->topo = p->topo->prox;
	p->qtde--;
	
	Tipo* r = (Tipo*) malloc(sizeof(Tipo));
	r = o->topo->dado;
	
	free(o);
	return r;
}

int pilha_pop2(Pilha* p, Tipo* endereco) {
	if(p == NULL) return NULL;
	if(p->qtde == 0) return NULL;
	if(endereco == NULL) return 0;
	
	Pilha* o = (Pilha*) malloc(sizeof(Pilha));
	o->topo = p->topo;
	p->topo = p->topo->prox;
	p->qtde--;
	
	endereco = o->topo->dado;
	
	free(o);
	return 1;
}

int pilha_topo(Pilha* p, Tipo* endereco) {
	if(p == NULL) return -1;
	if(endereco == NULL) return -1;
	
	endereco = p->topo->dado;
	return 1;
}

int pilha_tamanho(Pilha* p) {
	if(p == NULL) return -1;
	
	return p->qtde;
}

void pilha_imprimir(Pilha* p, void (*printElemento)(void*)) {
	if(p == NULL)
		printf("\nPilha n�o encontrada");
		
	No* o = p->topo;
	int i;
	
	printf("\nPilha: ");
	for(i = p->qtde-1; i >= 0; i--) {
		printf("|");
		printElemento(&(o->dado));
		o = o->prox;
		printf("| ");
	}
	free(o);
	
	printf("\n");
}
