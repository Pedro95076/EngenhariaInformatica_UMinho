/**
  * @file Ficheiro header referente às estruturas de árvores.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct tree *TREE;
TREE insert (TREE tree, int x);
int search (TREE tree, int x);
void printTree(TREE tree);
void freeTree(TREE node);
int countnodes(TREE tree);