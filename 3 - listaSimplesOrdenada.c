#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	int dado;
	struct nodo *prox;
}Celula;


Celula *inserirSimplesOrdenado(int valor, Celula *l) {
	Celula *novo, *p, *pAnterior;

	//alocar memoria
	novo = (Celula *)malloc(sizeof(Celula));

	//depositar valores
	novo->dado = valor;
	novo->prox = NULL; //se fosse circular seria diferente

	//percorrer lista
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
	if (l) {
		for (;l; l = l->prox) {
			printf("%d\t",l->dado);
		}
		printf("\n");
	}
}

int main(int argc, char  *argv[] ) {
	FILE *arquivo;
	Celula *lista = NULL;
	char nomearquivo[100];
	int num;

    if (argc != 2) {
		printf("Falha na passagem do arquivo de entrada\n");
		exit(0);
	}

    arquivo=fopen(argv[1],"r");

	if(!arquivo) {
		printf("Arquivo inexistente\n");
	}

	while (!feof(arquivo)) {	
		fscanf(arquivo,"%d",&num);
		lista = inserirSimplesOrdenado(num,lista);
	}

	exibirSimples(lista);
	return 1;
}
