#include <stdio.h>
#include <stdlib.h>
#include <time.h> //para usar sorteio

typedef struct nodo {
    int dado;
    struct nodo *prox;
} Celula;

Celula *inserirCircular(int valor, Celula *l) {
    Celula *novo, //para criar novo espaço em memoria, ou novo elemento 
           *p;    //para percorrer a lista

    Celula *pAnterior;
           
  //alocar memoria
  novo = (Celula *)malloc(sizeof(Celula));

  //depositar valores
  novo->dado = valor;

  //percorrer
  //se for o primeiro
  if (!l) {
    novo->prox = novo;
    return novo;
  }

  pAnterior = NULL;
  for (p = l; p->prox != l; p = p->prox) {
    if (novo->dado < p->dado) {
      novo->prox = p;

      if (!pAnterior) {
        //vai ate o final da lista e aponta o ultimo para o novo elemento
        for (; p->prox != l; p = p->prox);
        
        p->prox = novo;
        return novo;
      } else break;

    }
    pAnterior = p;
  }

  //descobrir pq saiu do for
  //chegou ao fim da lista
  if (p->prox == l) {
    if (novo->dado < p->dado) {    
      novo->prox = p;
      //verifica se eh o primeiro na lista
      if (pAnterior) pAnterior->prox = novo;
      else l->prox = novo;
    } else {
      p->prox = novo;
      novo->prox = l;
    } 
  //ainda esta no meio da lista    
  } else {
    pAnterior->prox = novo; 
  }
  return l;
}

void exibirCircular(Celula *l) {
    Celula *p;

    if (l) {
        for (p = l; p->prox != l; p = p->prox) {
            printf("%d\t", p->dado);
        }   
        printf("%d\t", p->dado);
        printf("\n");
    }
}

int contaNosCircular(Celula *l) {
    Celula *p;
    int qtdNos = 0;

    for (p = l; p->prox != l; p = p->prox) {
        qtdNos++; 
    }

    qtdNos++;
    return qtdNos;
}

Celula *elementoMeioCircular(Celula *l) {
    Celula *p;

    int metade = contaNosCircular(l) / 2;

    if (metade == 0) return NULL;

    for (p = l; metade > 0; p = p->prox, metade--);

    return p;
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
        printf("%d - %d\n", i, numeroSorteado);
        lista = inserirCircular(numeroSorteado, lista);
    }
    exibirCircular(lista);
    printf("Quantidade elementos: %d\n", contaNosCircular(lista));
    meio = elementoMeioCircular(lista);

    if (meio) printf("Elemento do meio: %d - %p\n", meio->dado, meio);
    return 1;
}










