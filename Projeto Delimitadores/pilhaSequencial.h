#define TAM_VETOR 5

typedef int Tipo;

typedef struct {
    Tipo* vetor;
    int tamVetor; //tam
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
void diminuir_pilha(Pilha* p);
void aumentar_pilha(Pilha* p);

Pilha* pilha_criar() {
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->vetor = (Tipo*) malloc(TAM_VETOR*sizeof(Tipo));
	
	p->qtde = 0;
	p->tamVetor = TAM_VETOR;
	
	return p;
}

void pilha_desalocar(Pilha* p) {
	free(p);
}

int pilha_push(Pilha* p, Tipo elemento) {
	if(p == NULL) return 0;
	
	if(p->qtde == p->tamVetor) aumentar_pilha(p);
	
	p->vetor[p->qtde] = elemento;
	p->qtde++;
	return 1;
}

Tipo* pilha_pop1(Pilha* p) {
	if(p == NULL) return NULL;
	if(p->qtde == 0) return NULL;
	
	p->qtde--;
	Tipo* r = (Tipo*) malloc(sizeof(Tipo));
	r = p->vetor[p->qtde];
	
	diminuir_pilha(p);
	
	return r;
}

int pilha_pop2(Pilha* p, Tipo* endereco) {
	if(p == NULL) return 0;
	if(p->qtde == 0) return 0;
	if(endereco == NULL) return 0;
	
	p->qtde--;
	*endereco = p->vetor[p->qtde];
	
	diminuir_pilha(p);
	
	return 1;
}

int pilha_topo(Pilha* p, Tipo* endereco) {
	if(p == NULL) return 0;
	if(endereco == NULL) return 0;
	
	*endereco = p->vetor[p->qtde-1];
	return 1;
}

int pilha_tamanho(Pilha* p){
	if(p == NULL) return -1;
	
	return p->qtde;
}

void pilha_imprimir(Pilha* p, void (*printElemento)(void*)) {
	if(p == NULL)
		printf("\nPilha n�o encontrada");
	
	int i;
	printf("\nPilha: ");
	for(i = p->qtde-1; i >= 0; i--) {
		printf("|");
		printElemento(&p->vetor[i]);
		printf("| ");
	}
	
	printf("\n");
}

void diminuir_pilha(Pilha* p){
	if(p->qtde >= TAM_VETOR && p->qtde <= p->tamVetor /4 ){
		int i;
		Tipo* vet = (Tipo*) calloc((p->tamVetor/2), sizeof(Tipo));	
		
		for(i = 0; i < p->tamVetor; i++)
			vet[i] = p->vetor[i];
		free(p->vetor);
		
		p->vetor = (Tipo*) calloc((p->tamVetor/2), sizeof(Tipo));
		for(i = 0; i < p->tamVetor; i++)
			p->vetor[i] = vet[i]; 
		free(vet);
		p->tamVetor = (p->tamVetor/2);
	}
}

void aumentar_pilha(Pilha* p){
	int i;
	Tipo* vet = (Tipo*) calloc(2*p->tamVetor, sizeof(Tipo));	
	
	for(i = 0; i < p->tamVetor; i++)
		vet[i] = p->vetor[i]; 
	free(p->vetor);
	
	p->vetor = (Tipo*) calloc(2*(p->tamVetor), sizeof(Tipo));
	for(i = 0; i < p->tamVetor; i++)
		p->vetor[i] = vet[i]; 
	free(vet);
	p->tamVetor = 2*(p->tamVetor);	
}
