//1. Construa uma funcao que receba uma Arvore Binária de Pesquisa e um valor inteiro qualquer. A funcao deve exibir todos os valores menores que o inteiro passado no parametro.

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct nodo{
    int dado;
    struct nodo *esquerda, *direita;
}Arvore;

Arvore *inserir(Arvore *raiz, int valor) {
    if (raiz) {
        if (valor < raiz -> dado) raiz -> esquerda = inserir(raiz -> esquerda, valor);
        else raiz -> direita = inserir(raiz -> direita, valor);
        return raiz;
    } else {
        Arvore *novo;
        novo = (Arvore *)malloc(sizeof(Arvore));
        novo -> dado = valor;
        novo -> esquerda = NULL;
        novo -> direita = NULL;
        return novo;
    }
}

void exibir(Arvore *raiz, int nivel) {
    if (raiz) {
        int i;
        exibir(raiz -> direita, nivel + 1);
        for (i = 0; i < nivel; i++) {
            printf("  ");
        }
        
        printf("(%d)%d\n", nivel, raiz -> dado);
        exibir(raiz -> esquerda, nivel + 1);
    }
}

Arvore *localizar(Arvore *raiz, int valor){
    if(raiz){
        if(valor > raiz -> dado){
            localizar(raiz -> direita, valor);
            localizar(raiz -> esquerda, valor);
            printf("%d\t", raiz -> dado);
        }
    }
    return raiz;
}

int main(){
    Arvore *raiz = NULL;
    int i, num, valor;
    
    system("cls");
    
    srand(time(NULL));
    for (i = 0; i < (rand() % 30); i++) {
        num = rand() % 30;
        raiz = inserir(raiz, num);
    }
    printf("Arvore:\n\n");
    exibir(raiz, 0);
    printf("Digite um valor: ");
    scanf("%d", &valor);
    localizar(raiz, valor);
}







