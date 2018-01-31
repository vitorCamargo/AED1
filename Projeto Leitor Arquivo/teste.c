#include <stdio.h>
#include <string.h>

typedef struct{
	FILE* arquivo;
	char delimitador;
	char* buffer;
	int posicao;
	int tamBuffer;
} LeitorArquivo;

LeitorArquivo* leitor_novo(char* arquivo, char delimitador, int tamBuffer);
char* leitor_ler1(LeitorArquivo* leitor);
void leitor_ler2(LeitorArquivo* leitor, char* endereco);
int leitor_temMaisToken(LeitorArquivo* leitor);

LeitorArquivo* leitor_novo(char* arquivo, char delimitador, int tamBuffer) {
	LeitorArquivo* leitor = (LeitorArquivo*) malloc(sizeof(LeitorArquivo));
	if(leitor->arquivo == NULL) printf("Erro ao abrir arquivo");
	
	leitor->arquivo = fopen(arquivo, "r");
	
	leitor->delimitador = delimitador;
	
	leitor->buffer = (char*) calloc(tamBuffer, sizeof(char));
	fgets(leitor->buffer, tamBuffer, leitor->arquivo);
	
	leitor->posicao = 0;
	leitor->tamBuffer = tamBuffer;
	
	return leitor;
}

char* leitor_ler1(LeitorArquivo* leitor) {
	int aux = leitor->posicao, i, j = 0, f;
	char* l;
	f = leitor_temMaisToken(leitor);
	
	if(f != 0) {
				
		if(f == 1)
			while(leitor->buffer[aux] != leitor->delimitador)
				aux++;
				
		if(f == 2)
			while(leitor->buffer[aux] != '\0')
				aux++;
		
		l = (char*) calloc(aux+1, sizeof(char));
		
		for(i = leitor->posicao; i < aux; i++){
			l[j] = leitor->buffer[i];
			j++;
		}
		l[i] = '\0';
		leitor->posicao = i+1;
		
		if(f == 2){
			aumenta_buffer(leitor);
			leitor->posicao = 0;
		}	
	}
	
	if(f == 0)
		printf("\nAcabou o arquivo");
	return l;
}

void leitor_ler2(LeitorArquivo* leitor, char* endereco) {
	int aux = leitor->posicao, i, j = 0, f;
	f = leitor_temMaisToken(leitor);
	free(endereco);
	
	if(f != 0) {
				
		if(f == 1)
			while(leitor->buffer[aux] != leitor->delimitador)
				aux++;
				
		if(f == 2)
			while(leitor->buffer[aux] != '\0')
				aux++;
		
		endereco = (char*) calloc(aux+1, sizeof(char));
		for(i = leitor->posicao; i < aux; i++){
			endereco[j] = leitor->buffer[i];
			j++;
		}
		endereco[i] = '\0';
		leitor->posicao = i+1;
		
		if(f == 2){
			aumenta_buffer(leitor);
			leitor->posicao = 0;
		}	
	}
	
	if(f == 0)
		printf("\nAcabou o arquivo");	
}

int leitor_temMaisToken(LeitorArquivo* leitor) {
	int i;
	for(i = leitor->posicao; i <= leitor->tamBuffer; i++){
		if(leitor->buffer[i] == leitor->delimitador){
			return 1;
		} else if(leitor->buffer[i] == '\0'){
			return 2;
		}
	}
	return 0;
}

int aumenta_buffer(LeitorArquivo* leitor){
	if(fgets(leitor->buffer, leitor->tamBuffer, leitor->arquivo) != NULL)
		return 1;
	
	return 0;
}

void main() {
	char *o;
	LeitorArquivo* l = leitor_novo("arquivo.txt", ';', 100);
	
	leitor_ler2(l,o);
	printf("%s ", o);
	leitor_ler2(l,o);
	printf("%s ", o);
	leitor_ler2(l,o);
	printf("%s ", o);
	leitor_ler2(l,o);
	printf("%s ", o);
}
