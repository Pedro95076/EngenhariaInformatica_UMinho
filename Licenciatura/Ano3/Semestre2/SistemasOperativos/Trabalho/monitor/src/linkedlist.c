#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/linkedlist.h"

int lookup_l(LinkedList l, char* x)
{
    // 0 if it's present, 1 otherwise

    LinkedList it;

    for(it = l; it != NULL && strcmp(x, it->info) != 0; it = it->next);

    if(it == NULL)
        return 1;

    return 0;
}

void add(LinkedList *l, char* x)
{
    LinkedList new = (LinkedList) malloc(sizeof(struct linkedlist));
    new->info = strdup(x);
    new->next = *l;
    *l = new;
}

void destroy(LinkedList l)
{
    if(l != NULL)
    {
        free(l->info);
        destroy(l->next);
        free(l);
    }
}

void printList(LinkedList l)
{
    LinkedList it;
    int i;

    for(it = l, i = 0; it != NULL; it = it->next, i++)
        printf("[%d]: %s -> ", i, it->info);

    printf("NULL\n");
}