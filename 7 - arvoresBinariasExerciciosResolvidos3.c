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
1. Escreva uma fun��o que receba como par�metros:
um ponteiro para a raiz de uma �rvore bin�ria de pesquisa; e um valor inteiro.
Ao final, esse m�todo dever� retornar quantos n�s da �rvore s�o m�ltiplos do valor do par�metro.
*/
int quantosMultiplos(int valor, Arvore *r) {
   if (r) {
      if (r->dado % valor == 0) return 1 + quantosMultiplos(valor, r->esq) + quantosMultiplos(valor, r->dir);
      return 0 + quantosMultiplos(valor, r->esq) + quantosMultiplos(valor, r->dir);
   } return 0;
}

/*
2. Escreva uma fun��o que receba dois par�metros:
um valor inteiro e um ponteiro para o primeiro elemento de uma �rvore bin�ria de pesquisa.
A fun��o dever� retornar o n�vel que se encontra esse valor inteiro na �rvore.
Lembrando que o primeiro n�vel � Zero, segundo � Um e assim por diante.
Caso o valor n�o esteja na �rvore, retornar -1.
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
3. Escreva um m�todo que receba como par�metro um ponteiro para a raiz de uma �rvore bin�ria de pesquisa.
O m�todo dever� retirar todos os n�s folhas, ou seja, realizar a poda.
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
4. Escreva uma fun��o que receba como par�metros:
 um ponteiro apontando para a raiz da �rvore bin�ria de pesquisa e um valor inteiro.
 Fa�a com que a fun��o delete o valor caso localizado na �rvore e se estiver em nodo folha.
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
5. Escreva um m�todo que receba como par�metro um ponteiro para a raiz de uma �rvore bin�ria de pesquisa.
O m�todo dever� retirar todos os n�s da �rvore.
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
6. Construa uma fun��o que receba como par�metro um ponteiro apontando para a raiz de uma �rvore bin�ria
e retorne a altura dessa �rvore.
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
7. Construa uma fun��o que receba como par�metro um ponteiro apontando para a raiz de uma �rvore bin�ria de pesquisa
e retorne um valor indicando verdadeiro se a �rvore existir e se os n�s de maior e menor valor da �rvore estiverem no mesmo n�vel.
Por valor do n�, entenda-se o conte�do armazenado no campo valor.
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
8. Escreva um m�todo que receba um ponteiro para o primeiro elemento de uma �rvore bin�ria (de pesquisa ou n�o).
O m�todo dever� retornar 1 se a �rvore � bin�ria de pesquisa ou 0 (zero) se n�o for bin�ria de pesquisa.
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
9. Escreva uma fun��o que receba como par�metro um ponteiro para a raiz de uma �rvore bin�ria de pesquisa
e retorne um ponteiro para o n� N�O FOLHA de maior valor.
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
10. Escreva uma fun��o que receba como par�metros:
(i) um ponteiro para a raiz de uma �rvore bin�ria de pesquisa;
(ii) valor inteiro em n.
A fun��o dever� contar os n�s da �rvore que N�O est�o na sub�rvore que tem em sua raiz o valor n (se houver esse n�).
Se esse n� n�o existir, devem ser contados todos os n�s da �rvore, e se ele for a raiz recebida como par�metro,
a contagem deve ser 0 (zero).
O resultado da contagem deve ser retornado. N�o use vari�veis globais.
*/
int contaNosForaSubArvore(Arvore *r, int n) {
	 if (r) {
	 	 if (n == r->dado) return 0;
	 	 return 1 + contaNosForaSubArvore(r->esq, n) + contaNosForaSubArvore(r->dir, n);
	 }
	 return 0;
}
/*
11. Escreva uma fun��o que receba como par�metros um ponteiro apontando para a raiz da �rvore bin�ria de pesquisa e dois valores inteiros M e N.
Fa�a com que a fun��o verifique se existe um n� com valor igual a M no caminho entre a raiz e o n� de valor igual a N.
Se existir, a fun��o deve retornar a diferen�a entre os n�veis dos dois n�s. Se N n�o existir na �rvore, ou se M n�o existir no caminho at� N,
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

	if (mesmoNivel(raiz)) printf("Menor e maior elementos no mesmo n�vel\n\n");
	else printf("Menor e maior elementos  n�veis diferentes\n\n");

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
