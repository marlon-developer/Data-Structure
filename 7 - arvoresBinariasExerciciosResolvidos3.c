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

/*
1. Escreva uma função que receba como parâmetros:
um ponteiro para a raiz de uma árvore binária de pesquisa; e um valor inteiro.
Ao final, esse método deverá retornar quantos nós da árvore são múltiplos do valor do parâmetro.
*/
int quantosMultiplos(int valor, Arvore *r) {
   if (r) {
      if (r->dado % valor == 0) return 1 + quantosMultiplos(valor, r->esq) + quantosMultiplos(valor, r->dir);
      return 0 + quantosMultiplos(valor, r->esq) + quantosMultiplos(valor, r->dir);
   } return 0;
}

/*
2. Escreva uma função que receba dois parâmetros:
um valor inteiro e um ponteiro para o primeiro elemento de uma árvore binária de pesquisa.
A função deverá retornar o nível que se encontra esse valor inteiro na árvore.
Lembrando que o primeiro nível é Zero, segundo é Um e assim por diante.
Caso o valor não esteja na árvore, retornar -1.
*/
int nivel(int valor, Arvore *r) {
   if (r) {
      if (valor == r->dado) return 0;
      else {
         if (valor < r->dado) { //avancando para subarvore esquerda
            int valorDeCima = nivel(valor, r->esq);
            if (valorDeCima == -1) return valorDeCima;
            else return valorDeCima + 1;
         } else { //avancando para subarvore direita
            int valorDeCima = nivel(valor, r->dir);
            if (valorDeCima == -1) return valorDeCima;
            else return valorDeCima + 1;
         }
      }
   }
   return -1; //valor nao localizado, logo sem nivel
}

/*
3. Escreva um método que receba como parâmetro um ponteiro para a raiz de uma árvore binária de pesquisa.
O método deverá retirar todos os nós folhas, ou seja, realizar a poda.
*/
Arvore *podar(Arvore *r) {
   if (r) {
      if (!r->esq && !r->dir) {
         free(r);
         return NULL;
      }
      r->esq = podar(r->esq);
      r->dir = podar(r->dir);
      return r;
   }
   return NULL;
}

/*
4. Escreva uma função que receba como parâmetros:
 um ponteiro apontando para a raiz da árvore binária de pesquisa e um valor inteiro.
 Faça com que a função delete o valor caso localizado na Árvore e se estiver em nodo folha.
*/
Arvore *apagarValorEmFolha(int valor, Arvore *r) {
   if (r) {
      if (valor == r->dado && (!r->esq && !r->dir)) {
         free(r);
         return NULL;
      }
      if (valor < r->dado) { //avancar para esquerda
         r->esq = apagarValorEmFolha(valor, r->esq);
      } else { //avancar para direita
         r->dir = apagarValorEmFolha(valor, r->dir);
      }
      return r;
   }
   return NULL;
}

/*
5. Escreva um método que receba como parâmetro um ponteiro para a raiz de uma árvore binária de pesquisa.
O método deverá retirar todos os nós da árvore.
*/
Arvore *destruirArvore(Arvore *r) {
   if (r) { //abordagem pos-fixado (EDR)
      if (r->esq) r->esq = destruirArvore(r->esq);
      if (r->dir) r->dir = destruirArvore(r->dir);
      free(r);
      return NULL;
   }
   return NULL;
}

/*
6. Construa uma função que receba como parâmetro um ponteiro apontando para a raiz de uma árvore binária
e retorne a altura dessa árvore.
*/
int altura(Arvore *r) {
   if (r) {
      int alturaEsquerda = altura(r->esq);
      int alturaDireita = altura(r->dir);
      if (alturaEsquerda > alturaDireita) return alturaEsquerda + 1;
      return alturaDireita + 1;
   }
   return 0;
}

/*
7. Construa uma função que receba como parâmetro um ponteiro apontando para a raiz de uma árvore binária de pesquisa
e retorne um valor indicando verdadeiro se a árvore existir e se os nós de maior e menor valor da árvore estiverem no mesmo nível.
Por valor do nó, entenda-se o conteúdo armazenado no campo valor.
*/
int mesmoNivel(Arvore *r) {
	if (r) {
		int qtdNiveisEsquerda, qtdNiveisDireita;
		Arvore *rAux;

		for (rAux = r, qtdNiveisEsquerda = 0; rAux->esq; rAux = rAux->esq, qtdNiveisEsquerda++);

		for (rAux = r, qtdNiveisDireita = 0; rAux->dir; rAux = rAux->dir, qtdNiveisDireita++);

		if (qtdNiveisEsquerda == qtdNiveisDireita) return 1;

	}
	return 0; //nao existe ou nao estao no mesmo nivel
}

/*
8. Escreva um método que receba um ponteiro para o primeiro elemento de uma árvore binária (de pesquisa ou não).
O método deverá retornar 1 se a árvore é binária de pesquisa ou 0 (zero) se não for binária de pesquisa.
*/
int ehABP(Arvore *r) {
	if (r) {
		if ( (r->esq && r->dado < r->esq->dado) || (r->dir && r->dado > r->dir->dado) ) return 0; //desordenada
		return ehABP(r->esq) && ehABP(r->dir); //observem... foi tratado como uma expressao logica
		                                       //os dois lados devem estar ordenados = lado esquerdo E lado direito
	}
	return 1; //se chegou aqui, pq o ramo da arvore esta ordenado
}

/*
9. Escreva uma função que receba como parâmetro um ponteiro para a raiz de uma árvore binária de pesquisa
e retorne um ponteiro para o nó NÃO FOLHA de maior valor.
*/
Arvore *maiorNaoFolha(Arvore *r) {
	if (r) {
		Arvore *rAux, *rAuxAnterior = NULL;

		//ir tudo para direita
		for (rAux = r; rAux->dir; rAuxAnterior = rAux, rAux = rAux->dir);

		if (rAux->esq) return rAux;
		else return rAuxAnterior;

	}
	return NULL;
}

/*
10. Escreva uma função que receba como parâmetros:
(i) um ponteiro para a raiz de uma árvore binária de pesquisa;
(ii) valor inteiro em n.
A função deverá contar os nós da árvore que NÃO estão na subárvore que tem em sua raiz o valor n (se houver esse nó).
Se esse nó não existir, devem ser contados todos os nós da árvore, e se ele for a raiz recebida como parâmetro,
a contagem deve ser 0 (zero).
O resultado da contagem deve ser retornado. Não use variáveis globais.
*/
int contaNosForaSubArvore(Arvore *r, int n) {
	 if (r) {
	 	 if (n == r->dado) return 0;
	 	 return 1 + contaNosForaSubArvore(r->esq, n) + contaNosForaSubArvore(r->dir, n);
	 }
	 return 0;
}
/*
11. Escreva uma função que receba como parâmetros um ponteiro apontando para a raiz da árvore binária de pesquisa e dois valores inteiros M e N.
Faça com que a função verifique se existe um nó com valor igual a M no caminho entre a raiz e o nó de valor igual a N.
Se existir, a função deve retornar a diferença entre os níveis dos dois nós. Se N não existir na árvore, ou se M não existir no caminho até N,
deve ser retornado o valor -1.
*/


int main() {
	Arvore *raiz = NULL;
	int i, numero;
	srand(time(NULL));

	for (i = 0; i < (rand() % 20) +3; i++) {
		numero = rand() % 20;
		raiz = inserir(numero, raiz);
		printf("%d\t", numero);
	}

	printf("\n\nExibindo a arvore\n\n");
	exibir(raiz, 0);
	/*
	printf("Digite numero para pesquisa: ");
	scanf("%d",&numero);

	printf("Multiplos de %d sao %d\n", numero, quantosMultiplos(numero, raiz));
	printf("Nivel de %d na arvore eh %d\n", numero, nivel(numero, raiz));

	raiz = podar(raiz);
	printf("\n\nExibindo a arvore sem folhas\n\n");
	exibir(raiz, 0);

	printf("Digite numero para pesquisa: ");
	scanf("%d",&numero);

	raiz = apagarValorEmFolha(numero, raiz);
	printf("\n\nExibindo a arvore sem valor (caso esteja em folha)\n\n");
	exibir(raiz, 0);
	*/
	printf("A altura da arvore resultante eh %d\n\n", altura(raiz));

	if (mesmoNivel(raiz)) printf("Menor e maior elementos no mesmo nível\n\n");
	else printf("Menor e maior elementos  níveis diferentes\n\n");

	if (ehABP(raiz)) printf("Arvore Binaria de Pesquisa\n");
	else printf("Arvore Binaria, mas nao de pesquisa (desordenada)\n");

	printf("Maior elemento nao folha: %d\n\n", maiorNaoFolha(raiz)->dado);

	printf("Digite numero para pesquisa: ");
	scanf("%d",&numero);

	printf("Quantidade de nos fora da subArvore de %d: %d\n\n", numero, contaNosForaSubArvore(raiz, numero));
	/*
	raiz = destruirArvore(raiz);
	printf("\n\nExibindo a arvore destruida\n\n");
	exibir(raiz, 0);
	*/
	system("pause");
	return 1;
}
