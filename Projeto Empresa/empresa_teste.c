#include <stdio.h>
#include <string.h>
#include "empresa.h"

void main() {
	Empresa* e = empresa_novo("Samsung", 5);
	cadastrarProduto(e, "123", "Aparelho Celular", 450);
	cadastrarProduto(e, "aaa", "Tablet", 500);
	incluirEstoque(e, "123", 9);
	removerEstoque(e, "123", 8);
	removerEstoque(e, "aaa", 3);
	empresa_imprimir(e);
	descadastrarProduto(e,"123");
	incluirEstoque(e, "aaa", 9);
	empresa_imprimir(e);
}
