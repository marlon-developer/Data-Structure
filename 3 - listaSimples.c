#include <stdio.h>
#include <stdlib.h>
#include <time.h> //para usar sorteio

typedef struct nodo {
	int dado;
	struct nodo *prox;
} Celula;

Celula *inserirSimples(int valor, Celula *l) {
	Celula *novo, //para criar novo espaço em memoria, ou novo elemento 
	       *p,    //para percorrer a lista
	       *pAnterior; //para garantir a ordenacao
	//alocar memoria
  novo = (Celula *)malloc(sizeof(Celula));
	//depositar valores
  novo->dado = valor;
  novo->prox = NULL;
	//percorrer
  if (!l) return novo;

  pAnterior = NULL;
	for (p = l; p; p = p->prox) {
		if (novo->dado < p->dado) {
			novo->prox = p;
			if (!pAnterior) {
				return novo;
			} else break;		
		}
		pAnterior = p;
	}

	//engatar o novo elemento
	pAnterior->prox = novo;
	return l;
}

void exibirSimples(Celula *l) {
	Celula *p;

	if (l) {
		for (p = l; p; p = p->prox) {
			printf("%d\t", p->dado);
		}	
		printf("\n");
	}
}

int contaNosSimples(Celula *l) {
	Celula *p;
	int qtdNos = 0;

	for (p = l; p; p = p->prox, qtdNos++); 

	return qtdNos;
}

Celula *elementoMeioSimples(Celula *l) {
	Celula *p;

	int metade = contaNosSimples(l) / 2;

	if (metade == 0) return NULL;

	for (p = l; metade > 0; p = p->prox, metade--);

	return p;
}

Celula *retiraPrimeiroElemento(Celula *l) {
	Celula *lixo;

	if (!l) return NULL;

	lixo = l;
	l = l->prox;
	free(lixo);
	return l;
}

Celula *retiraUltimoElemento(Celula *l) {
	Celula *lixo;

	if (!l) return NULL;


	return l;
}

int main() {
	int tamanhoLista;
	int numeroSorteado;
	int i;
	Celula *lista = NULL;
	Celula *meio;

	srand(time(NULL)); //para gerar a semente do sorteio

	tamanhoLista = rand() % 10; //sortear numeros entre 0 - 9

	//popular a lista simples
	for (i = 0; i < tamanhoLista; i++) {
		numeroSorteado = rand() % 100;
		lista = inserirSimples(numeroSorteado, lista);
	}
	exibirSimples(lista);
	printf("Quantidade elementos: %d\n", contaNosSimples(lista));
	meio = elementoMeioSimples(lista);

	if (meio) printf("Elemento do meio: %d - %p\n", meio->dado, meio);

	lista = retiraPrimeiroElemento(lista);
	exibirSimples(lista);
	return 1;
}




















