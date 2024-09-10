/**
  * @file Ficheiro com modularidade e encapsulamento referente às estruturas de árvores.
  */
#include "auxiliarTree.h"
#include "auxiliarFunc.h"

/**
 * @brief Definição da árvore binária.
 */
struct tree 
{
    /** inteiro que contém a informação a guardar */
	int value;
    /** apontador para os ramos direito e esquerdo da árvore */
	struct tree *l, *r;
};

/**
 * @brief Função que insere os elementos na árvore binária.
 * 
 * @param tree Árvore binária onde se irá guardar o elemento.
 * 
 * @param x Elemento a guardar na árvore binária.
 * 
 * @return Retorna a árvore com o elemento inserido.
 */
TREE insert (TREE tree, int x) 
{
    TREE *place;
	place = &tree;

	while (*place != NULL)
		if (x < (*place)->value)
				 place = &((*place)->l);
		else place = &((*place)->r);

	(*place) = malloc (sizeof (struct tree));
	(*place)->value = x;
	(*place)->l = (*place)->r = NULL;

	return tree;
}

/**
 * @brief Função que procura numa árvore binária o elemento especificado
 * 
 * @param tree Árvore binária aonde se irá procurar o elemento
 * 
 * @param x Elemento a encontrar na árvore binária.
 *
 * @return Retorna 1 se o elemento for encontrado.
 */
int search (TREE tree, int x) 
{
	while (tree != NULL && tree->value != x)
    {
        if (tree->value > x) tree = tree->l;
		else tree = tree->r;
    }

	return (tree!=NULL);
}

/**
 * @brief Função que permite a impressão in order da árvore binária.
 * 
 * @param tree Árvore binária a imprimir.
 */
void printTree(TREE tree)
{
    if(tree!=NULL)
    {
        printTree(tree->l);
        printf("valor %d\n", tree->value);
        printTree(tree->r);
    }
}

/**
 * @brief Função que permite libertar o espaço ocupado pela árvore binária.
 * 
 * @param node Árvore.
 */
void freeTree(TREE node){
       if (node != NULL) {
        freeTree(node->r);
        freeTree(node->l);
        free(node);
     }
}

/**
 * @brief Função que o número de nodos de uma árvore binária.
 * 
 * @param node Árvore.
 */
int countnodes(TREE tree)
{
    if(tree!=NULL) return (1+countnodes(tree->l)+countnodes(tree->r));
    else return 0;
}