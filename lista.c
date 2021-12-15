#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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

Lista *criar_lista(){
    Lista *li;
    li = (Lista*)malloc(sizeof(Lista));
    if(li != NULL){
        li->ini = NULL;
        li->fim = NULL;
        li->qtd = 0;
    }
    return li;
}

int inserir_lista(Lista *li, int num){
    if(li == NULL){
        return 0;
    }
    else{
        Elem *novo;
        novo = (Elem*)malloc(sizeof(Elem));
        novo->peca = num;
        novo->prox = NULL;
        if(li->ini){
            li->fim->prox = novo;
        }
        else{
            li->ini = novo;
        }
        li->fim = novo;
        li->qtd++;
        return 1;
    }
}

int remover_lista(Lista *li, int num){
    if(li == NULL || li->ini == NULL){
        return 0;
    }
    Elem *ant, *aux;
    aux = li->ini;
    while(aux != NULL && aux->peca != num){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL){
        return 0;
    }
    if(aux == li->ini){
        li->ini = aux->prox;
    }
    else{
        if(aux == li->fim){
            li->fim = ant;
        }
        ant->prox = aux->prox;
    }
    if(li->ini == NULL){
        li->fim = NULL;
    }

    free(aux);
    li->qtd--;
    return 1;
}

