#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct nodescritor {
    struct elemento *ini;
    struct elemento *fim;
    int qtd;
};

struct elemento {
    int peca;
    struct elemento *prox;
};

typedef struct elemento Elem;

Pilha *criar_pilha(){
    Pilha *pi;
    pi = (Pilha*)malloc(sizeof(Pilha));
    if(pi != NULL){
        pi->ini = NULL;
        pi->fim = NULL;
        pi->qtd = 0;
    }
    return pi;
}

int inserir_pilha(Pilha *pi, int num){
    if(pi == NULL){
        return 0;
    }
    else{
        Elem *novo;
        novo = (Elem*)malloc(sizeof(Elem));
        if(pi->ini == NULL){
            pi->fim = novo;
        }
        novo->peca = num;
        novo->prox = pi->ini;
        pi->ini = novo;
        pi->qtd++;
        return 1;
    }
}

int tamanho_pilha(Pilha *pi){
    if(pi == NULL){
        return -1;
    }
    return pi->qtd;
}

int primeiro_pilha(Pilha *pi){
    if(pi == NULL || pi->qtd == 0){
        return -1;
    }
    return pi->ini->peca;
}
