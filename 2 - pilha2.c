#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
	char sigla[2];
	int x, y, z;
	struct nodo *prox;
} Celula;

Celula *inserir(char sigla[], int x, int y, int z, Celula *topo) {
	Celula *novo;

	//alocar memoria
	novo = (Celula*)malloc(sizeof(Celula));

	//depositar valores
	strcpy(novo->sigla, sigla);
	novo->x = x;
	novo->y = y;
	novo->z = z;
	novo->prox = topo;  //o novo elemento transforma-se no topo
	
	//engatar
	return novo;
}

Celula *remover(Celula *topo) {
	Celula *lixo;

	if (!topo) {
		printf("Pilha vazia\n");
		return topo;
	}

	lixo = topo;
	topo = topo->prox;
	free(lixo);
	return topo;
}


int main(int qtdArgumentos, char *listaArgumentos[]) {
	FILE *arquivoProcurador;
	Celula *pilha = NULL, *tmp;
	char sigla[2];
	int x, y, z;
	char comando;

	if (qtdArgumentos != 2) {
		printf("Falha na passagem do arquivo de entrada\n");
		exit(0);
	}

	arquivoProcurador = fopen(listaArgumentos[1], "r");
	if (!arquivoProcurador) {
		printf("Arquivo não localizado\n");
		exit(0);
	}

	while (!feof(arquivoProcurador)) {
		fscanf(arquivoProcurador,"%s %d %d %d", sigla, &x, &y, &z);
		pilha = inserir(sigla, x, y, z, pilha);
	}


	for (tmp = pilha; tmp != NULL; tmp = tmp->prox) {
		printf("%s %d %d %d\n", tmp->sigla, tmp->x, tmp->y, tmp->z);

	}


	return 1;
}

















