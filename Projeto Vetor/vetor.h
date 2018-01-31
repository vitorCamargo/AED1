typedef struct{
    int* v; 
    int tamanho;
    int qtde;
} Vetor;

Vetor* vetor_criar();
void vetor_inserirPosicao(Vetor* vetor, int valor, int posicao);
void vetor_inserirFim(Vetor* vetor, int valor);
void vetor_removerFim(Vetor* vetor);
void vetor_removerPosicao(Vetor* vetor, int posicao);
int vetor_procuraQtdTermos(Vetor* vetor, int termo);
void vetor_edita(Vetor* vetor, int valor, int posicao);
void vetor_ordenar(Vetor* vetor);
void vetor_imprimir(Vetor* vetor);
void aumenta(Vetor* vetor);

Vetor* vetor_criar(){
	Vetor* vetor = (Vetor*) malloc(sizeof(Vetor));
	vetor->v = (int*) calloc(10, sizeof(int));
	vetor->tamanho = 10;
	vetor->qtde = 0;
	
	return vetor;
}

void vetor_inserirPosicao(Vetor* vetor, int valor, int posicao){
	if(posicao > vetor->tamanho)
		printf("\nPosição não existe!");
	else
		if(vetor->v[posicao] != NULL)
			printf("\nPosição Ocupada");
		else {
			vetor->v[posicao] = valor;
			vetor->qtde++;
		}
}

void vetor_inserirFim(Vetor* vetor, int valor){
	if(vetor->qtde == vetor->tamanho)
		aumenta(vetor);
	
	vetor->v[vetor->qtde] = valor;
	vetor->qtde++;	
}

void vetor_removerFim(Vetor* vetor){
	vetor->v[vetor->qtde] = NULL;
	vetor->qtde--;
}

void vetor_removerPosicao(Vetor* vetor, int posicao){
	if(posicao > vetor->tamanho)
		printf("\nPosição não existe!");
	else {
		vetor->v[posicao] = NULL;
		vetor->qtde--;
	}
}

int vetor_procuraQtdTermos(Vetor* vetor, int termo){
	int aux = 0, i;
	
	for(i = 0; i < vetor->tamanho; i++)
		if(vetor->v[i] == termo)
			aux++;
	
	return aux;
}

int vetor_procuraPrimeiroTermo(Vetor* vetor, int termo){
	int pos = 0, i;
	
	for(i = 0; i < vetor->tamanho; i++)
		if(vetor->v[i] == termo)
			pos = i;
	
	return pos;
}

void vetor_edita(Vetor* vetor, int valor, int posicao){
	if(vetor->v[posicao] == NULL)
		printf("\nPosição desocupada");
	else {
		vetor->v[posicao] = valor;
		vetor->qtde++;
	}
}

void vetor_imprimir(Vetor* vetor){
	int i;
	
	printf("\nVetor: ");
	for(i = 0; i < vetor->tamanho; i++){
		printf("%d ", vetor->v[i]);
	}
}

void vetor_ordenar(Vetor* vetor){
	int i, j;
	for(i = 1; i < vetor->tamanho; i++){
        int elemento = vetor->v[i];
        j = i - 1;
        while(j >= 0 && elemento < vetor->v[j]){
            vetor->v[j+1] = vetor->v[j];
            j--;
        }
        vetor->v[j+1] = elemento;
    }
}

void aumenta(Vetor* vetor){
	int i, aux;
	aux = vetor->tamanho;
	
	int* vt = (int*) calloc(vetor->tamanho, sizeof(int));
	vetor->tamanho += 10;
	
	for(i = 0; i < aux; i++)
		vt[i] = vetor->v[i]; 
	free(vetor->v);
	
	vetor->v = (int*) calloc(vetor->tamanho, sizeof(int));
	for(i = 0; i < aux; i++)
		vetor->v[i] = vt[i]; 
	free(vt);	
}
