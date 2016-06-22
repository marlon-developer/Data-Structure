#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct nodo {
	int dado;
	struct nodo *esq, *dir;
} Arvore;

Arvore *inserir(int valor, Arvore *r) {
	if (r) {
		if (valor < r->dado) { //ir para esquerda
			r->esq = inserir(valor, r->esq);
		} else { //ir para direita
			r->dir = inserir(valor, r->dir);
		}
		return r;
	} else {
		Arvore *novo;
		novo = (Arvore *)malloc(sizeof(Arvore));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}
}

void exibir(Arvore *r, int nivel) {
	if (r) { //DRE - infixado invertido
		int i;
		//vai tudo para direita
		exibir(r->dir, nivel + 1);

		//visita a raiz
		for (i = 0; i < nivel; i++) {
			printf("  ");
		}
		printf("(%d)%d\n", nivel, r->dado);

		//vai tudo pra esquerda
		exibir(r->esq, nivel + 1);
	}
}

Arvore *remover(int valor, Arvore *r) {
	if (r) {
    	if (valor == r->dado) {
        	//eh folha
        	if (!r->esq && !r->dir) {
				free(r);
				return NULL;
			} else { //nao eh folha
				Arvore *pai, *lixo = r, *temp;

				if (r->esq) { //pegar o filho da esquerda para novo pai
					pai = r->esq;
					temp = pai->dir;
					if (r->dir) {
						pai->dir = r->dir;
						for (r = r->dir; r->esq; r = r->esq);

						r->esq = temp;
					}
				} else { //pegar o filho da direita para novo pai
					pai = r->dir;
				}
				free(lixo);
				return pai;
			}
		}
		if (valor < r->dado) { //avancar para esquerda
			r->esq = remover(valor, r->esq);
      	} else { //avancar para direita
        	r->dir = remover(valor, r->dir);
      	}
      	return r;
	}
   	return NULL;
}


int main() {
	Arvore *raiz = NULL;
	int i, numero;
	srand(time(NULL));

	for (i = 0; i < (rand() % 20) +3; i++) {
		numero = rand() % 30;
		raiz = inserir(numero, raiz);
		printf("%d\t", numero);
	}

	printf("\n\nExibindo a arvore\n\n");
	exibir(raiz, 0);

	printf("Digite numero para pesquisa: ");
	scanf("%d",&numero);

	raiz = remover(numero, raiz);

	printf("Arvore alterada apos remocao do %d\n\n", numero);

	exibir(raiz, 0);

	return 1;
}
