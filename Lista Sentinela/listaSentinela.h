typedef int T;

typedef struct no{
	T dado;
	struct no* ant;
	struct no* prox;
} No;

typedef struct {
	No* sentinela;
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

No* novoNo(T elemento);
No* referencia(Lista* l, int pos);
void adicionaDepoisDe(Lista* l, No* novo, No* ref);
void removeDepoisDe(Lista* l, No* ref, T* end);

Lista* lista_cria() {
	Lista* l = (Lista*) malloc(sizeof(Lista));
	
	l->sentinela = (No*) malloc(sizeof(No));
	l->sentinela->prox = l->sentinela;
	l->sentinela->ant = l->sentinela;
	
	l->qtde = 0;
	
	return l;
}

void lista_desaloca(Lista* l) {
	int i;
	
	for(i = 0; i < l->qtde; i++)
		lista_remove1(l, 0);
	
	free(l->sentinela);
	free(l);
}

int lista_insere(Lista* l, T elemento, int posicao) {
	if(l == NULL) return 0;
	if(posicao > l->qtde) return 0;
	
	No* o = novoNo(elemento);
	No* ref = referencia(l, posicao);
	adicionaDepoisDe(l, o, ref);
	
	return 1;
}

int lista_insere_fim(Lista* l, T elemento) {
	if(l == NULL) return 0;
	
	No* o = novoNo(elemento);
	No* ref = referencia(l, l->qtde);
	adicionaDepoisDe(l, o, ref);
	
	return 1;
}

T* lista_remove1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->qtde == 0) return NULL;
	if(posicao > l->qtde) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	
	No* ref = referencia(l, posicao);
	removeDepoisDe(l, ref, r);
	
	return r;
}

int lista_remove2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	if(posicao > l->qtde) return 0;
	
	No* ref = referencia(l, posicao);
	removeDepoisDe(l, ref, endereco);
	
	return 1;
}

int lista_remove_elemento(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	
	No* o = l->sentinela->prox;
	int i, aux = 0;
	
	for(i = 0; i < l->qtde; i++) {
		if(compara(&(o->dado), &elemento)) return *lista_remove1(l, aux);
		
		o = o->prox;
		aux++;
	}
	
	return 1;
}

T* lista_busca1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->qtde == 0) return NULL;
	if(posicao > l->qtde) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	No* o = referencia(l, posicao);
	
	*r = o->dado;
	return r;
}

int lista_busca2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	if(posicao > l->qtde) return 0;
	
	No* o = referencia(l, posicao);
	
	*endereco = o->dado;
	return 1;
}

int lista_contem(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	if(l->qtde == 0) return 0;
	
	No* o = l->sentinela->prox;
	int i;
	
	for(i = 0; i < l->qtde; i++) {
		if(compara(&(o->dado), &elemento)) return 1;
		
		o = o->prox;
	}
	
	return 0;
}

int lista_posicao(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return -3;
	if(l->qtde == 0) return -2;
	
	No* o = l->sentinela->prox;
	int i;
	
	for(i = 0; i < l->qtde; i++) {
		if(compara(&(o->dado), &elemento)) return i;
		
		o = o->prox;
	}
	
	return -1;
}

int lista_tamanho(Lista* l) {
	if(l == NULL) return 0;
	
	return l->qtde;
}

void lista_imprime(Lista* l, void (*printElemento)(void*)) {
	if(l == NULL)
		printf("\nLista não encontrada");
		
	No* o = l->sentinela->prox;
	int i;
	
	printf("\nLista: ");
	for(i = 0; i < l->qtde; i++) {
		printf("|");
		printElemento(&(o->dado));
		o = o->prox;
		printf("| ");
	}
	
	printf("\n");
}

No* novoNo(T elemento) {
	No* o = (No*) malloc(sizeof(No));
	
	o->ant = NULL;
	o->prox = NULL;
	o->dado = elemento;
	
	return o;
}

No* referencia(Lista* l, int pos) {
	No* o = l->sentinela;
	int i;
	
	for(i = 0; i < pos; i++)
		o = o->prox;
		
	return o;
}

void adicionaDepoisDe(Lista* l, No* novo, No* ref) {
	novo->ant = ref;
	novo->prox = ref->prox;
	
	ref->prox->ant = novo;
	ref->prox = novo;
	
	l->qtde++;
}

void removeDepoisDe(Lista* l, No* ref, T* end) {
	No* n;
	n = n->prox;
	*end = n->dado;
	
	ref->prox->prox->ant = ref;
	ref->prox = ref->prox->prox;
	
	l->qtde--;
	free(n);
}
