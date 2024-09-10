/**
  * @file Ficheiro com modularidade e encapsulamento referente às estruturas de tuplos.
  */
#include "data_tpll.h"

/**
 * @brief Definição da struct top
 * 
 */
struct top
{
    /** inteiro que contém a informação a guardar */
    int info;
    /** inteiro que contém o número de ocorrências da informação */
    int counter;
    /** apontador da struct top que aponta para o próximo nodo */
    struct top * next;
};

/**
 * @brief Definição da struct string
 * 
 */
struct string
{
    /** string que contém a informação a guardar */
    char *info;
    /** inteiro que contém o número de ocorrências da informação */
    int counter;
    /** apontador da struct string que aponta para o próximo nodo */
    struct string * next;
};

/**
 * @brief Função que insere os elementos especificados na lista ligada top.
 * 
 * @param top Lista ligada aonde se irão guardar os elementos.
 * 
 * @param info Informação a guardar na lista ligada.
 * 
 * @param counter Contador a guardar na lista ligada.
 * 
 * @return Retorna a lista ligada com os elementos inseridos.
 */
TOP insertDataTop(TOP top, int info, int counter)
{
    TOP new = malloc(sizeof(struct top));
    new->info = info;
    new->counter = counter;
    new->next = top;
    top = new;

    return top;
}

/**
 * @brief Funçao que verifica se a estrutura chegou ao fim.
 * 
 * @param top Lista ligada com toda a informação necessária.
 * 
 * @return Retorna 1 no final caso a lista tenha chegado ao fim.
 */
int isEmptyTop(TOP top)
{
    int r=0;
    if(top->next == NULL) r = 1;
    return r;
}

/**
 * @brief Funçao que verifica se a estrutura chegou ao fim.
 * 
 * @param top Lista ligada com toda a informação necessária.
 * 
 * @return Retorna 1 no final caso a lista tenha chegado ao fim.
 */
int isEmptyString(STRING top)
{
    int r=0;
    if(top->next == NULL) r = 1;
    return r;
}

/**
 * @brief Função que permite obter o próximo nodo do top.
 * 
 * @param top Lista ligada com a informação necessária.
 * 
 * @return Retorna o próximo nodo do top.
 */

TOP obtain_nextTop(TOP top)
{
    top = top->next;
    return top;
}

/**
 * @brief Função que permite obter o próximo nodo do string.
 * 
 * @param top Lista ligada com a informação necessária.
 * 
 * @return Retorna o próximo nodo do string.
 */
STRING obtain_nextString(STRING top)
{
    top = top->next;
    return top;
}

/**
 * @brief Função que permite obter o número de ocorrências do valor no top.
 * 
 * @param top Lista ligada com a informação necessária.
 * 
 * @return Retorna o número de ocorrências da informação no nodo.
 */
int obtain_CountTop(TOP top)
{
    return (top->counter);
}

/**
 * @brief Função que acrescenta um valor ao counter caso a informação já se encontre na lista ligada.
 * 
 * @param top Lista ligada com a informação.
 * 
 * @param info Informação a procurar ou inserir na lista ligada.
 * 
 * @return Retorna a lista ligada com a informação e o respetivo número de ocorrências.
 */
TOP countInfo(TOP top, int info){
    
    TOP aux = top;
    TOP nova;
    TOP ant = NULL;
    
    while (aux != NULL && aux->info != info) { 
        ant = aux;
        aux = aux->next;
    }
    
    if (aux && aux->info == info) {
        aux->counter++;
    } else {
        nova = malloc(sizeof(struct top));
        if(nova == NULL) return NULL;
        nova->info = info;
        nova->counter = 1;
        nova->next = aux;
        if(ant) {
        ant->next = nova;
        } else 
        {
            top = nova;
        }
    }
    
    return top;
}

/**
 * @brief Função que acrescenta um valor ao counter caso a informação já se encontre na lista ligada.
 * 
 * @param top Lista ligada com a informação.
 * 
 * @param info Informação a procurar ou inserir na lista ligada.
 * 
 * @return Retorna a lista ligada com a informação e o respetivo número de ocorrências.
 */
STRING countInfoStr(STRING top, char *info, int *count){
    
    STRING aux = top;
    STRING nova;
    STRING ant = NULL;
    
    while (aux != NULL && strcmp(aux->info,info)!=0) { 
        ant = aux;
        aux = aux->next;
    }
    
    if (aux && strcmp(aux->info,info)==0) {
        aux->counter++;
    } else {
        nova = malloc(sizeof(struct string));
        if(nova == NULL) return NULL;
        nova->info = info;
        nova->counter = 1;
        (*count)++;
        nova->next = aux;
        if(ant) {
        ant->next = nova;
        } else 
        {
            top = nova;
        }
    }
    
    return top;
}

/**
 * @brief Função que permite obter o id do nodo.
 * 
 * @param head Lista ligada com a informação.
 *
 * @return Retorna o id do nodo.
 */
int obtain_topID(TOP head)
{
    return head->info;
}

/**
 * @brief Função que permite obter o id do nodo.
 * 
 * @param head Lista ligada com a informação.
 *
 * @return Retorna o id do nodo.
 */
char * obtain_stringID(STRING head)
{
    return strdup(head->info);
}

/**
 * @brief Função que permite obter o valor máximo de ocorrências de uma lista ligada.
 * 
 * @param top Lista ligada com a informação.
 * 
 * @param info Apontador para a variável info.
 * 
 * @param count Apontador para a variável count.
 */
void mostFreq(TOP top, int *info, int *count)
{
    TOP freq = malloc(sizeof(struct top));
    TOP temp = top;
    int r = 0;


    while (temp->next!=NULL)
    {
        if(temp->counter>r)
        {
            freq = temp;
            r = temp->counter;
        }
        temp = temp->next;
    }
    top = temp;

    *info = freq->info;
    *count = freq->counter;
    freq->counter = -1;
}

/**
 * @brief Função que permite obter o valor máximo de ocorrências de uma lista ligada.
 * 
 * @param string Lista ligada com a informação.
 * 
 * @return Retorna a string com a informação relativa ao maior número de ocorrências da lista ligada.
 */
char * mostFreqString(STRING string){
    STRING freq;
    int r = 0;
    while (string->next!=NULL)
    {
        if(string->counter>r)
        {
            freq = string;
            r = string->counter;
        }
        string = string->next;
    }
    
    freq->counter = -1;

    return (freq->info);
}

/**
 * @brief Função que permite a impressão da lista ligada top.
 * 
 * @param top Lista ligada a imprimir.
 */
void printTop(TOP top)
{
    while(top!=NULL)
    {
        printf("info %d\n", top->info); 
        printf("counter %d\n", top->counter);  
        top = top->next;    
    }
}

/**
 * @brief Função que permite a impressão da lista ligada string.
 * 
 * @param string Lista ligada a imprimir.
 */
void printString(STRING string)
{
    while(string!=NULL)
    {
        printf("info %s\n", string->info);
        printf("counter %d\n", string->counter);
        string = string->next;
    }

}

/**
 * @brief Função que permite libertar o espaço ocupado pela estrutura Top.
 * 
 * @param head Lista ligada.
 *
 */
void freeTop(TOP head)
{
   TOP tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

/**
 * @brief Função que permite libertar o espaço ocupado pela estrutura String.
 * 
 * @param head Lista ligada.
 *
 */
void freeString(STRING head)
{
   STRING tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

/**
 * @brief Função que acrescenta um valor ao counter caso a informação já se encontre na lista ligada.
 * 
 * @param top Lista ligada com a informação.
 * 
 * @param info Informação a procurar ou inserir na lista ligada.
 * 
 * @param count Informação a adicionar no campo counter.
 * 
 * @return Retorna a lista ligada com a informação e o respetivo número de ocorrências.
 */
TOP countInfoLen(TOP top, int info, int count){
    
    TOP aux = top;
    TOP nova;
    TOP ant = NULL;
    
    while (aux != NULL && aux->info != info) { 
        ant = aux;
        aux = aux->next;
    }
    
    if (aux && aux->info == info) {
        aux->counter = count;
    } else {
        nova = malloc(sizeof(struct top));
        if(nova == NULL) return NULL;
        nova->info = info;
        nova->counter = count;
        nova->next = aux;
        if(ant) {
        ant->next = nova;
        } else 
        {
            top = nova;
        }
    }
    
    return top;
}