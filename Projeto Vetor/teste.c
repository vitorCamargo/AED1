#include <stdlib.h>
#include <stdio.h>

#include "Vetor.h"

int main() {
    Vetor* v1 = vetor_criar();
    vetor_inserirFim(v1, 1);
    vetor_inserirPosicao(v1, 2, 2);
    vetor_imprimir(v1);
    vetor_inserirPosicao(v1, 1, 2);
    vetor_imprimir(v1);
    vetor_ordenar(v1);
    vetor_imprimir(v1);
    vetor_removerFim(v1);
    vetor_imprimir(v1);
}
