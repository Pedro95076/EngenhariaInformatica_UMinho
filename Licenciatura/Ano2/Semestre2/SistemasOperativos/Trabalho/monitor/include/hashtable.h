#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HSIZE 10

#include "message.h"

typedef struct pair
{
    int key; // PID
    Message info;
    struct pair *next;
}* Pair;

typedef Pair HashTable [HSIZE];

int lookup(HashTable h, int k, Message *m);

int update(HashTable h, int k, Message m);

int remove_message(HashTable h, int k, Message *m);

void destroy_table(HashTable h);

void print_table(HashTable h);

#endif // HSGTABLE_H