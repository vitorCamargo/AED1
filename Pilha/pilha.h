#define TAM_VETOR 5

typedef struct {
	int* vetor;
	int topo; //qtde
	int tam;
} Pilha;

Pilha* pilha_criar();
int pilha_push(Pilha* p, int elem);
int* pilha_pop1(Pilha* p);
int pilha_pop2(Pilha* p, int* end);
int pilha_topo(Pilha* p, int* end);
void pilha_imprimir(Pilha* p);
int pilha_tamanho(Pilha* p);
void diminuir_pilha(Pilha* p);
void aumentar_pilha(Pilha* p);

Pilha* pilha_criar() {
	Pilha* p = (Pilha*) malloc(sizeof(Pilha));
	p->vetor = (int*) malloc(TAM_VETOR*sizeof(int));
	
	p->topo = 0;
	p->tam = TAM_VETOR;
	
	return p;
}

int pilha_push(Pilha* p, int elem) {
	if(p == NULL) return 0;
	
	if(p->topo == p->tam) aumentar_pilha(p);
	
	p->vetor[p->topo] = elem;
	p->topo++;
	return 1;
}

int* pilha_pop1(Pilha* p) {
	if(p == NULL) return NULL;
	if(p->qtde == 0) return NULL;
	
	p->topo--;
	int* r = (int*) malloc(sizeof(int));
	r = p->vetor[p->topo];
	
	diminuir_pilha(p);
	
	return r;
}

int pilha_pop2(Pilha* p, int* end) {
	if(p == NULL) return 0;
	if(p->qtde == 0) return 0;
	if(end == NULL) return 0;
	
	p->topo--;
	end = p->vetor[p->topo];
	
	diminuir_pilha(p);
	
	return 1;
}

int pilha_topo(Pilha* p, int* end) {
	if(p == NULL) return 0;
	if(end == NULL) return 0;
	
	end = p->vetor[p->topo-1];
	return 1;
}

void pilha_imprimir(Pilha* p){
	if(p == NULL)
		printf("\nPilha não encontrada");
		
	int i;
	printf("\nPilha: ");
	for(i = 0; i < p->topo; i++)
		printf("|%d| ", p->vetor[i]);
	printf("\n");
}

int pilha_tamanho(Pilha* p){
	if(p == NULL) return -1;
	
	return p->topo;
}

void diminuir_pilha(Pilha* p){
	if(p->topo >= TAM_VETOR && p->topo <= p->tam /4 ){
		int i;
		int* vet = (int*) calloc((p->tam/2), sizeof(int));	
		
		for(i = 0; i < p->tam; i++)
			vet[i] = p->vetor[i];
		free(p->vetor);
		
		p->vetor = (int*) calloc((p->tam/2), sizeof(int));
		for(i = 0; i < p->tam; i++)
			p->vetor[i] = vet[i]; 
		free(vet);
		p->tam = (p->tam/2);
	}
}

void aumentar_pilha(Pilha* p){
	int i;
	int* vet = (int*) calloc(2*p->tam, sizeof(int));	
	
	for(i = 0; i < p->tam; i++)
		vet[i] = p->vetor[i]; 
	free(p->vetor);
	
	p->vetor = (int*) calloc(2*(p->tam), sizeof(int));
	for(i = 0; i < p->tam; i++)
		p->vetor[i] = vet[i]; 
	free(vet);
	p->tam = 2*(p->tam);	
}
