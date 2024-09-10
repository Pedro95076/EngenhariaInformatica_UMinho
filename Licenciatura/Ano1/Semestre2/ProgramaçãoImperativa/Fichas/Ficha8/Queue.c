#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void initQueue (Queue *q){
    q->inicio = NULL;
    q->fim = NULL;
}

int QisEmpty (Queue q){
    return (q.inicio == NULL);
}

int enqueue (Queue *q, int x){
    LInt aux = malloc(sizeof(struct slist));
    if (aux == NULL) return 1;
    aux->valor = x;
    aux->prox = NULL;
    
    if(q->inicio == NULL){
        q->inicio = aux;
        q->fim = aux;
    } else {
        q->fim->prox = aux;
        q->fim = aux;
    }
    
    return 0;
}

int dequeue (Queue *q, int *x){
    return -1;
}

int frontQ (Queue q, int *x){
    if(q.inicio == NULL) return 1;
    
    *x = (q.inicio)->valor;
    
    return 0;
}

typedef LInt QueueC;

void initQueueC (QueueC *q);
int QisEmptyC (QueueC q){
    return -1;
}

int enqueueC (QueueC *q, int x){
    return -1;
}

int dequeueC (QueueC *q, int *x){
    return -1;
}

int frontC (QueueC q, int *x){
    return -1;
}
