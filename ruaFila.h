#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;
} TipoCarro;

typedef struct {
    TipoCarro item;
    TipoApontador prox;
} Celula;

typedef struct {
    TipoApontador frente;
    TipoApontador tras;
} TipoFila;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCarro {
    char chave;
} TipoCarro;

typedef struct TipoCelula {
    TipoCarro item;
    TipoApontador prox;
} TipoCelula;

typedef struct TipoFila {
    TipoApontador frente, tras;
} TipoFila;

void FFVazia(TipoFila *Fila) {
    Fila->frente = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->tras = Fila->frente;
    Fila->frente->prox = NULL;
}

int Vazia(TipoFila Fila) {
    return (Fila.frente == Fila.tras);
}

void Enfileira(TipoCarro x, TipoFila *Fila) {
    Fila->tras->prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Fila->tras = Fila->tras->prox;
    Fila->tras->item = x;
    Fila->tras->prox = NULL;
}

void Desenfileira(TipoFila *Fila, TipoCarro *item) {
    TipoApontador q;
    if (Vazia(*Fila)) {
        printf("Erro fila esta vazia\n");
        return;
    }
    q = Fila->frente;
    Fila->frente = Fila->frente->prox;
    *item = Fila->frente->item;
    free(q);
}

void exibe(TipoFila fila) {
    TipoApontador aux = fila.frente->prox;
    while (aux != NULL) {
        printf("\n%c", aux->item.chave);
        aux = aux->prox;
    }
}
