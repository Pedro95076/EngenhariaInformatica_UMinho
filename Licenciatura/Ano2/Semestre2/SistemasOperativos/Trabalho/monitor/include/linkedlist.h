#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct linkedlist
{
    char* info;
    struct linkedlist *next;
}* LinkedList;

int lookup_l(LinkedList l, char* x);

void add(LinkedList *l, char* x);

void destroy(LinkedList l);

void printList(LinkedList l);

#endif // LINKEDLIST_H