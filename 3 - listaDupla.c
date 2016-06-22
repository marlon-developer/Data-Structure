#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo {
	int dado;
	struct nodo *ant, *prox;
} CelulaD;

CelulaD *inserirD(int valor, CelulaD *l) {
	CelulaD *novo;

	//alocar memoria
	novo = (CelulaD *)malloc(sizeof(CelulaD));

	//depositar valores
	novo->dado = valor;
	novo->ant = NULL;
	novo->prox = NULL;

	//percorrer a lista

	//1o - verificar se eh o primeiro elemento
	if (!l) return novo;

	//2o - posiciona l no inicio da lista
	for (;l->ant; l = l->ant);

	//3o - percorrer até o final
	for (;l->prox; l = l->prox); //aqui é colocado o código para inserir ordenado

	l->prox = novo;
	novo->ant = l;

	return l;
}

void exibirD(CelulaD *l) {
	if (!l) printf("\nLista vazia\n");
	else {
		//posiciona l no inicio da lista
		for (;l->ant; l = l->ant);

		//percorre a lista exibindo
		for(;l; l = l->prox) {
			printf("%d\t", l->dado);
		}

		printf("\n");
	}
}

int contaNosD(CelulaD *l) {
	int qtd = 0;

	if (!l) return qtd;

	//posiciona l no início da lista
	for (; l->ant; l = l->ant);

	for (; l; l = l->prox, qtd++);

	return qtd;
}

CelulaD *elementoMeioD(CelulaD *l) {
	int qtd = contaNosD(l);

	if (qtd < 3) {
		printf("Quantidade de nós menor que 3. Sem meio.\n");
		return NULL;
	}

	//posiciona l no início da lista
	for (; l->ant; l = l->ant);

	//posiciona l no meio da lista
	for (qtd/=2; qtd > 0; l = l->prox, qtd--);

	return l;
}

CelulaD *retiraUltimoElementoD(CelulaD *l) {
	if (!l) return l;

	if (!l->ant && !l->prox) { //somente um elemento
		free(l);
		return NULL;
	}

	for (;l->prox->prox; l = l->prox);

	free(l->prox);
	l->prox = NULL;

	return l;
}

int main() {
	int tamanhoLista;
	int numeroSorteado;
	int i;
	CelulaD *lista = NULL;
	CelulaD *meio;

	srand(time(NULL)); //para gerar a semente do sorteio

	tamanhoLista = rand() % 10; //sortear numeros entre 0 - 9

	//popular a lista duplamente encadeada
	for (i = 0; i < tamanhoLista; i++) {
		numeroSorteado = rand() % 100;
		lista = inserirD(numeroSorteado, lista);
	}
	exibirD(lista);
	printf("Quantidade elementos: %d\n", contaNosD(lista));
	meio = elementoMeioD(lista);

	if (meio) printf("Elemento do meio: %d\n", meio->dado);

	lista = retiraUltimoElementoD(lista);

	printf("Ultimo elemento retirado da lista\n");
	exibirD(lista);
	return 1;
}





