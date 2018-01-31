typedef struct {
	char cod[15];
	char* descricao;
	float valor;
	int qtd;
}Produto;

typedef struct {
	char nome[30];
	int capacidade;
	int qtd_produtos;
	Produto** estoque;
}Empresa;

Produto* produto_novo(char* cod, char* desc, float valor);
Empresa* empresa_novo(char* nome, int cap);
int cadastrarProduto(Empresa* e, char* codigo, char* desc, float valor);
int incluirEstoque(Empresa* e, char* codigo, int qtd);
int removerEstoque(Empresa* e, char* codigo, int qtd);
int descadastrarProduto(Empresa* e, char* cod);
void produto_imprimir(Produto* p);
void empresa_imprimir(Empresa* e);

Produto* produto_novo(char* cod, char* desc, float valor) {
	Produto* p = (Produto*) malloc(sizeof(Produto));
	p->descricao = (char*) calloc(strlen(desc)+1, sizeof(char));
	
	strcpy(p->cod, cod);
	strcpy(p->descricao, desc);
	p->valor = valor;
	p->qtd = 0;
	
	return p;
}

Empresa* empresa_novo(char* nome, int cap) {
	Empresa* e = (Empresa*) malloc(sizeof(Empresa));
	
	strcpy(e->nome, nome);
	e->capacidade = cap;
	e->qtd_produtos = 0;
	e->estoque = (Produto**) calloc(e->capacidade, sizeof(Produto*));
	
	return e;
}

int cadastrarProduto(Empresa* e, char* codigo, char* desc, float valor) {
	if(e == NULL) return -1;
	if(e->capacidade == e->qtd_produtos) return -1;
	if(posicaoProduto(e, codigo) != -1) return -1;
	
	e->estoque[e->qtd_produtos] = produto_novo(codigo, desc, valor);
	e->qtd_produtos++;
	return e->qtd_produtos;
}

int incluirEstoque(Empresa* e, char* codigo, int qtd) {
	int pos = posicaoProduto(e, codigo);
	if(e == NULL) return -1;
	if(pos == -1) return -1;
	
	e->estoque[pos]->qtd += qtd;
	return e->qtd_produtos;
}

int removerEstoque(Empresa* e, char* codigo, int qtd) {
	int pos = p+osicaoProduto(e, codigo);
	if(e == NULL) return -1;
	if(pos == -1) return -1;
	if(e->estoque[pos]->qtd < qtd) return -1;
	
	e->estoque[pos]->qtd -= qtd;
	return e->qtd_produtos;
}

int descadastrarProduto(Empresa* e, char* cod) {
	int pos = posicaoProduto(e, cod), i;
	if(e == NULL) return -1;
	if(e->qtd_produtos == 0) return -2;
	if(pos == -1) return -3;
	
	for(i = pos; i < e->qtd_produtos; i++)
		e->estoque[i] = e->estoque[i+1];
	
	free(e->estoque[i]);
	
	e->qtd_produtos--;
	return e->qtd_produtos;
}

void produto_imprimir(Produto* p) {
	printf("\nProduto %s", p->cod);
	printf("\n\tDescrição: %s", p->descricao);
	printf("\n\tValor Unitário: R$%.2f", p->valor);
	printf("\n\tQuantidade em estoque: %d", p->qtd);
}

void empresa_imprimir(Empresa* e) {
	int i;
	printf("\nEmpresa: %s", e->nome);
	printf("\n\tTamanho do Estoque: %d", e->capacidade);
	printf("\n\t%d produtos em estoque: ", e->qtd_produtos);
	
	for(i = 0; i < e->qtd_produtos; i++)
		produto_imprimir(e->estoque[i]);
}

int posicaoProduto(Empresa* e, int cod) {
	int i;
	for(i = 0; i < e->qtd_produtos; i++) {
		if(strcmp(cod, e->estoque[i]->cod) == 0) return i;
	}
	return -1;
}
