#define TAM_VETOR 5

typedef int T;

typedef struct{
    T* vetor;
    int primeiro;
    int ultimo;
    int tamanhoVet;
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
void diminuir_fila(Fila* f);
void aumentar_fila(Fila* f);

Fila* fila_criar() {
	Fila* f = (Fila*) malloc(sizeof(Fila));
	f->vetor = (T*) malloc(TAM_VETOR*sizeof(T));
	
	f->ultimo = 0;
	f->primeiro = 0;
	f->tamanhoVet = TAM_VETOR;
	
	return f;
}

void fila_desalocar(Fila* f) {
	frre(f->vetor);
	free(f);
}

int fila_inserir(Fila* f, T elemento) {
	if(f == NULL) return 0;
	
	if(f->ultimo == f->tamanhoVet) aumentar_fila(f);
	
	f->vetor[f->ultimo] = elemento;
	f->ultimo++;
	
	return 1;
}

T* fila_remover1(Fila* f) {
	if(f == NULL) return NULL;
	if(f->primeiro == f->ultimo) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	*r = f->vetor[f->primeiro];
	
	f->primeiro++;
	
	diminuir_fila(f);
	return r;
}

int fila_remover2(Fila* f, T* endereco) {
	if(f == NULL) return 0;
	if(f->primeiro == f->ultimo) return 0;
	
	*endereco = f->vetor[f->primeiro];
	
	f->primeiro++;
	
	diminuir_fila(f);
	return 1;
}

T* fila_primeiro(Fila* f) {
	if(f == NULL) return NULL;
	if(f->primeiro == f->ultimo) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	*r = f->vetor[f->primeiro];
	
	return r;
}

int fila_tamanho(Fila* f) {
	if(f == NULL) return 0;
	
	return f->ultimo - f->primeiro;
}

int fila_contem(Fila* f, T elemento) {
	if(f == NULL) return 0;
	if(f->primeiro == f->ultimo) return 0;
	
	int i;
	
	for(i = f->primeiro; i < f->ultimo; i++)
		if(f->vetor[i] == elemento) return 1;
	
	return 0;
}

void fila_imprimir(Fila* f, void (*printElemento)(void*)) {
	if(f == NULL)
		printf("\nFila não encontrada");
	
	int i;
	
	printf("\nFila: ");
	for(i = f->primeiro; i < f->ultimo; i++) {
		printf("|");
		printElemento(&f->vetor[i]);
		printf("| ");
	}	
	printf("\n");
}

void diminuir_fila(Fila* f){
	if((f->ultimo - f->primeiro) >= TAM_VETOR && (f->ultimo - f->primeiro) <= f->tamanhoVet/4){
		int i, j;
		f->tamanhoVet = (f->tamanhoVet/2);
		T* vet = (T*) calloc(f->tamanhoVet, sizeof(T));
		
		for(i = 0; i < f->tamanhoVet; i++)
			vet[i] = f->vetor[i+f->primeiro];
		free(f->vetor);
		
		f->vetor = (T*) calloc(f->tamanhoVet, sizeof(T));
		for(i = 0; i < f->tamanhoVet; i++)
			f->vetor[i] = vet[i]; 
		free(vet);
		
		f->ultimo = (f->ultimo - f->primeiro);
		f->primeiro = 0;
	}
}

void aumentar_fila(Fila* f){
	int i;
	T* vet = (T*) calloc(2*f->tamanhoVet, sizeof(T));	
	
	for(i = 0; i < f->tamanhoVet; i++)
		vet[i] = f->vetor[i]; 
	free(f->vetor);
	
	f->vetor = (T*) calloc(2*(f->tamanhoVet), sizeof(T));
	for(i = 0; i < f->tamanhoVet; i++)
		f->vetor[i] = vet[i]; 
	free(vet);
	f->tamanhoVet = 2*(f->tamanhoVet);	
}
