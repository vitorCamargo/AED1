typedef int T;

typedef struct no{
	T dado;
	struct no* ant;
	struct no* prox;
} No;

typedef struct {
	No* primeiro;
	No* ultimo;
	int tam;
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

Lista* lista_cria() {
	Lista* l = (Lista*) malloc(sizeof(Lista));
	
	l->primeiro = NULL;
	l->ultimo = NULL;
	l->tam = 0;
	
	return l;
}

void lista_desaloca(Lista* l) {
	int i;
	
	for(i = 0; i < l->tam; i++)
		lista_remove1(l, 0);
	
	free(l);
}

int lista_insere(Lista* l, T elemento, int posicao) {
	if(l == NULL) return 0;
	if(posicao > l->tam) return 0;
	
	if(posicao == l->tam)
		return lista_insere_fim(l, elemento);
	
	No* novo = novoNo(elemento);
	if(posicao == 0) {
		l->primeiro->ant = novo;
		novo->prox = l->primeiro;
		l->primeiro = novo;
	} else {
		No* o = l->primeiro;
		int i;
		
		for(i = 0; i < posicao-1; i++)
			o = o->prox;
		
		novo->ant = o;
		novo->prox = o->prox;
		
		o->prox->ant = novo;
		o->prox = novo;
	}
	l->tam++;
	
	return 1;
}

int lista_insere_fim(Lista* l, T elemento) {
	if(l == NULL) return 0;
	
	No* o = novoNo(elemento);
	
	if(l->tam == 0)	
		l->primeiro = o;	
	else {
		o->ant = l->ultimo;
		l->ultimo->prox = o;	
	}
		
	l->ultimo = o;
	l->tam++;
	
	return 1;
}

T* lista_remove1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->tam == 0) return NULL;
	if(posicao > l->tam) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	No* n;
	
	if(posicao == 0) {
		*r = l->primeiro->dado;
		n = l->primeiro;
		
		l->primeiro = l->primeiro->prox;
		l->primeiro->ant = NULL;
	} else if(posicao == l->tam-1) {
		*r = l->ultimo->dado;
		n = l->ultimo;
		
		l->ultimo = l->ultimo->ant;
		l->ultimo->prox = NULL;
	} else {
		No* o = l->primeiro;
		int i;
		
		for(i = 0; i < posicao-1; i++)
			o = o->prox;
		
		n = o->prox;
		*r = o->prox->dado;
		
		o->prox->prox->ant = o;
		o->prox = o->prox->prox;
	}
	
	free(n);
	l->tam--;
	
	return r;
}

int lista_remove2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->tam == 0) return 0;
	if(posicao > l->tam) return 0;
	
	No* n;
	
	if(posicao == 0) {
		n = l->primeiro;
		*endereco = l->primeiro->dado;
		
		l->primeiro = l->primeiro->prox;
		l->primeiro->ant = NULL;
	} else if(posicao == l->tam-1) {
		n = l->ultimo;
		*endereco = l->ultimo->dado;
		
		l->ultimo = l->ultimo->ant;
		l->ultimo->prox = NULL;
	} else {
		No* o = l->primeiro;
		int i;
		
		for(i = 0; i < posicao-2; i++)
			o = o->prox;
		
		n = o->prox;
		*endereco = o->prox->dado;
		
		o->prox->prox->ant = o;
		o->prox = o->prox->prox;
	}
	free(n);
	l->tam--;
	
	return 1;
}

int lista_remove_elemento(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	if(l->tam == 0) return 0;
	
	No* o = l->primeiro;
	int i, aux = 0;
	
	for(i = 0; i < l->tam; i++) {
		if(compara(&(o->dado), &elemento)) return *lista_remove1(l, aux);
		
		o = o->prox;
		aux++;
	}
	
	return 1;
}

T* lista_busca1(Lista* l, int posicao) {
	if(l == NULL) return NULL;
	if(l->tam == 0) return NULL;
	if(posicao > l->tam) return NULL;
	
	T* r = (T*) malloc(sizeof(T));
	No* o = l->primeiro;
	int i;
	
	for(i = 0; i < posicao; i++)
		o = o->prox;
	
	*r = o->dado;
	return r;
}

int lista_busca2(Lista* l, int posicao, T* endereco) {
	if(l == NULL) return 0;
	if(l->tam == 0) return 0;
	if(posicao > l->tam) return 0;
	
	No* o = l->primeiro;
	int i;
	
	for(i = 0; i < posicao; i++)
		o = o->prox;
	
	*endereco = o->dado;
	return 1;
}

int lista_contem(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return 0;
	if(l->tam == 0) return 0;
	
	No* o = l->primeiro;
	int i;
	
	for(i = 0; i < l->qtde; i++) {
		if(compara(&(o->dado), &elemento)) return 1;
		
		o = o->prox;
	}
	
	return 0;
}

int lista_posicao(Lista* l, T elemento, int (*compara)(void*, void*)) {
	if(l == NULL) return -3;
	if(l->tam == 0) return -2;
	
	No* o = l->primeiro;
	int i;
	
	for(i = 0; i < l->tam; i++) {
		if(compara(&(o->dado), &elemento)) return i;
		
		o = o->prox;
	}
	
	return -1;
}

int lista_tamanho(Lista* l) {
	if(l == NULL) return 0;
	
	return l->tam;
}

void lista_imprime(Lista* l, void (*printElemento)(void*)) {
	if(l == NULL)
		printf("\nLista não encontrada");
		
	No* o = l->primeiro;
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
