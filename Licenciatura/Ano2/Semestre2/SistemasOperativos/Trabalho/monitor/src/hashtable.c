#include <stdlib.h>
#include <stdio.h>

#include "../include/hashtable.h"

int hash(int key)
{
    return key % HSIZE;
}

void init_table(HashTable h)
{
    for (int i = 0; i < HSIZE; h[i++] = NULL);
}

int lookup(HashTable h, int k, Message *m)
{
    int p = hash(k);
    int found;

    Pair it;

    for ( it = h[p]; it != NULL && it->key != k; it = it->next);
    
    if(it != NULL)
    {
        *m = it->info;
        found = 1;
    }
    else
        found = 0;

    return found;
}

int update(HashTable h, int k, Message m)
{
    int p = hash(k);
    int new;
    Pair it;

    for(it = h[p]; it != NULL && it->key != k; it = it->next);

    if(it != NULL)
    {
        it->info = m;
        new = 0;
    }
    else
    {
        it = (Pair) malloc(sizeof(struct pair));
        it->info = m;
        it->key = k;
        it->next = h[p];
        h[p] = it;
        new = 1;
    }

    return new;
}

int remove_message(HashTable h, int k, Message *m)
{
    int p = hash(k);
    int removed = 0;
    Pair *it, tmp;

    for(it = h + p; *it != NULL && (*it)->key != k; it = &((*it)->next));

    if(*it != NULL)
    {
        tmp = *it;
        *it = (*it)->next;
        *m = tmp->info;
        free(tmp);
        removed = 1;
    }

    return removed;
}

void destroy_pair(Pair p)
{
    if(p != NULL)
    {
        destroy_pair(p->next);
        free(p);
    }
}

void destroy_table(HashTable h)
{
    for(int i = 0; i < HSIZE; i++)
    {
        destroy_pair(h[i]);
    }
}

void print_table(HashTable h)
{
    for(int i = 0; i < HSIZE; i++)
    {
        printf("%d: ", i);

        for(Pair it = h[i]; it != NULL; it = it->next)
        {
            printf("( key: %d, value: { pid: %d, name: %s, tv_sec: %ld, tv_usec: %d }) -> ", 
            it->key, 
            it->info.pid, 
            it->info.name, 
            it->info.timestamp.tv_sec, 
            it->info.timestamp.tv_usec);
        }

        printf("NULL\n");
    }
}