#include <stdio.h>
#include <stdlib.h>

//tipo para a celula, como em pilhas e listas simples
typedef struct nodo {
	int dado;
	struct nodo *prox;
} Celula;

//tipo para armazenar os dois ponteiros da fila
typedef struct {
	Celula *cabeca; //operacao de remocao
	Celula *cauda;  //operacao de insercao
} Fila;

/*
metodo que incializa a fila
*/
void inicializacao(Fila *f) {
	f->cabeca = NULL;
	f->cauda = NULL;
}

/*
metodo que insere um elemento na cauda da fila
*/
void inserirFila(int valor, Fila *f) {
	Celula *novo;

	novo = (Celula *)malloc(sizeof(Celula));
	novo->dado = valor;
	novo->prox = NULL;

	//eh a primeira vez?
	if (!f->cauda) {
		f->cauda = novo;
		f->cabeca = novo;
	} else {
		f->cauda->prox = novo;
		f->cauda = novo;
	}
}

/*
metodo que remove elemento da cabeca da fila
*/
void removerFila(Fila *f) {
	Celula *lixo;

	//fila existe?
	if (f->cabeca) {
		lixo = f->cabeca;
		f->cabeca = f->cabeca->prox;
		free(lixo);

		//caso apague o ultimo elemento
		if (!f->cabeca) {
			f->cauda = NULL;
		}
	} else {
		printf("Fila vazia\n");
	}

}

int main() {

	Fila fila; //observe o tipo Fila utilizado

	inicializacao(&fila); //observe que fila nao eh um ponteiro

	inserirFila(10, &fila);
	inserirFila(45, &fila);
	inserirFila(13, &fila);
	inserirFila(66, &fila);

	printf("Na cabeca: %d\nNa cauda: %d\n", fila.cabeca->dado, fila.cauda->dado);

	removerFila(&fila);
	removerFila(&fila);

	printf("Situacao da fila apos remocoes!\n");
	printf("Na cabeca: %d\nNa cauda: %d\n", fila.cabeca->dado, fila.cauda->dado);
	return 1;
}