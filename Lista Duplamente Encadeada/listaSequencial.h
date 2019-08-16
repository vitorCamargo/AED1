#define TAM_VETOR 5

typedef int T;

typedef struct {
    T* vetor;
    int tamanhoVet;
    int qtde;
} Lista;

Lista* lista_cria();
void lista_desaloca(Lista* l);

int lista_insere(Lista* l, T elemento, int posicao);
int lista_insere_fim(Lista* l, T elemento);

T* lista_remove1(Lista* l, int posicao);
int lista_remove2(Lista* l, int posicao, T* endereco);
int lista_remove_elemento(Lista* l, T elemento, int (*compara)(void*, void*));

T* lista_busca1(Lista* l, int posicao);
int lista_busca2(Lista* l, int posicao, T* endereco);
int lista_contem(Lista* l, T elemento, int (*compara)(void*, void*));
int lista_posicao(Lista* l, T elemento, int (*compara)(void*, void*));

int lista_tamanho(Lista* l);
void lista_imprime(Lista* l, void (*imprimeElemento)(void*));

void aumenta_lista(Lista* l);
void diminue_lista(Lista* l);

Lista* lista_cria() {
	Lista* l = (Lista*) malloc(sizeof(Lista));
	
	l->qtde = 0;
	l->tamanhoVet = TAM_VETOR;
	l->vetor = (T*) malloc(TAM_VETOR*sizeof(T));
	
	return l;
}

void lista_desaloca(Lista* l) {
	free(l->vetor);
	free(l);
}

int lista_insere(Lista* l, T elemento, int posicao) {
	if(l == NULL) return 0;
	if(posicao > l->qtde) return 0;
	if(l->qtde == l->tamanhoVet) aumenta_lista(l);
	
	int i;
	for(i = l->qtde-1; i >= posicao; i--)
		l->vetor[i+1] = l->vetor[i];
	l->vetor[i+1] = elemento;
	
	l->qtde++;
	
	return 1;
}

int lista_insere_fim(Lista* l, T elemento) {
	if(l == NULL) return 0;
	if(l->qtde == l->tamanhoVet) aumenta_lista(l);
	
	l->vetor[l->qtde] = elemento;
	
	l->qtde++;
	
	return 1;
}

T* lista_remove1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->qtde == 0) return NULL;
	if(posicao >= l->qtde) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	int i;
	*r = l->vetor[posicao];
	
	for(i = posicao; i < l->qtde-1; i++)
		l->vetor[i] = l->vetor[i+1];
	
	l->qtde--;
	diminue_lista(l);
	
	return r;
}

int lista_remove2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	if(posicao >= l->qtde) return 0;
	
	int i;
	*endereco = l->vetor[posicao];
	
	for(i = posicao; i < l->qtde-1; i++)
		l->vetor[i] = l->vetor[i+1];
	
	l->qtde--;
	diminue_lista(l);
	
	return 1;
}

int lista_remove_elemento(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	
	int i, aux = 0;
	
	for(i = 0; i < l->qtde; i++) {
		if(compara(&(l->vetor[i]), &elemento))
			return *lista_remove1(l, aux);
		aux++;
	}
	
	return 0;
}

T* lista_busca1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->qtde == 0) return NULL;
	if(posicao >= l->qtde) return NULL;
	
	T* r = (T*) malloc(sizeof(T));	
	*r = l->vetor[posicao];
	
	return r;
}

int lista_busca2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	if(posicao >= l->qtde) return 0;
	
	*endereco = l->vetor[posicao];
	
	return 1;
}

int lista_contem(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	
	int i;
	for(i = 0; i < l->qtde; i++)
		if(compara(&(l->vetor[i]), &elemento))
			return 1;
			
	return 0;
}

int lista_posicao(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return -1;
	if(l->qtde == 0) return -1;
	
	int i;
	for(i = 0; i < l->qtde; i++)
		if(compara(&(l->vetor[i]), &elemento))
			return i;
			
	return -1;
}

int lista_tamanho(Lista* l) {
	if(l == NULL) return -1;
	
	return l->qtde;
}

void lista_imprime(Lista* l, void (*imprimeElemento)(void*)) {
	if(l == NULL)
		printf("\nLista n�o encontrada");
	
	int i;
	
	printf("\nLista: ");
	for(i = 0; i < l->qtde; i++) {
		printf("|");
		imprimeElemento(&l->vetor[i]);
		printf("| ");
	}	
	printf("\n");
}

void aumenta_lista(Lista* l) {
	int i;
	T* vet = (T*) calloc(2*l->tamanhoVet, sizeof(T));	
	
	for(i = 0; i < l->tamanhoVet; i++)
		vet[i] = l->vetor[i]; 
	free(l->vetor);
	
	l->vetor = (T*) calloc(2*(l->tamanhoVet), sizeof(T));
	for(i = 0; i < l->tamanhoVet; i++)
		l->vetor[i] = vet[i]; 
	free(vet);
	l->tamanhoVet = 2*(l->tamanhoVet);	
}

void diminue_lista(Lista* l) {
	if(l->qtde >= TAM_VETOR && l->qtde <= l->tamanhoVet/4 ){
		int i, j;
		l->tamanhoVet = (l->tamanhoVet/2);
		T* vet = (T*) calloc(l->tamanhoVet, sizeof(T));
		
		for(i = 0; i < l->tamanhoVet; i++)
			vet[i] = l->vetor[i];
		free(l->vetor);
		
		l->vetor = (T*) calloc(l->tamanhoVet, sizeof(T));
		for(i = 0; i < l->tamanhoVet; i++)
			l->vetor[i] = vet[i]; 
		free(vet);
	}
}
