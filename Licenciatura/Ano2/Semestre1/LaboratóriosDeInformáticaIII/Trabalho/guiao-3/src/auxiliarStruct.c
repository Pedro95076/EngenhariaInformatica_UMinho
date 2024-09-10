/**
  * @file Ficheiro com modularidade e encapsulamento referente às estruturas auxiliares
  */
#include "auxiliarStruct.h"

/**
 * @brief Definição da estrutura data
 */
struct data
{
    /** string que contém a informação a guardar */
    char *info;
    /** apontador da estrutura data que aponta para o próximo nodo */
    struct data *next;
};

/**
 * @brief Definição da estrutura string
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
 * @brief Definição da estrutura topUsersStruct
 */
struct topUsersStruct
{
    /** string que contém o login a guardar */
    char* login;
    /** string que contém o id a guardar */
    char* id;
    /** inteiro que contém o número de ocorrências da informação */
    int counter;
};

/**
 * @brief Função que permite inserir dados na lista ligada
 * 
 * @param data Lista ligada onde irá ser guardada a informação
 * 
 * @param info string com a informação a guardar
 * 
 * @return Lista ligada com a informação guardada
 */
DATA insertData(DATA data, char *info)
{
    DATA new = malloc(sizeof(struct data));
    new->info = info;
    new->next = data;
    data = new;

    return data;
}

/**
 * @brief Função que guarda a informação dada numa determinada posição do array
 * 
 * @param a Array com topUsersStruct como elementos
 * 
 * @param k Indice a utilizar no array
 * 
 * @param id string com o ID a guardar
 * 
 * @param login string com o login a guardar
 * 
 * @param counter inteiro com o counter a guardar
 */
void topUsersSave (TOPUSERSSTRUCT a, int k, char *id, char*login, int counter)
{
    a[k].counter = counter;
    a[k].id = strdup(id);
    a[k].login = strdup(login);
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
 * @brief Função que permite testar se a lista ligada se encontra vazia
 * 
 * @param data Lista ligada
 * 
 * @return Retorna 1 quando a lista chega ao fim
 */
int isEmptyData(DATA data)
{
    int r=0;
    if(data->next == NULL) r = 1;
    return r;
}

/**
 * @brief Funçao que verifica se a estrutura chegou ao fim.
 * 
 * @param top Lista ligada com toda a informação necessária.
 * 
 * @return Retorna 1 no final caso a lista tenha chegado ao fim.
 */
int isEmptyTopUsersStruct(TOPUSERSSTRUCT a, int i)
{
    int r=0;
    if(a[i].login == NULL && a[i].id == NULL) r = 1;
    return r;
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
 * @brief Função que permite obter o próximo nodo da lista ligada
 * 
 * @param data Lista ligada
 * 
 * @return Retorna o endereço do próximo nodo
 */
DATA obtain_nextData(DATA data)
{
    data = data->next;
    return data;
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
 * @brief Função que permite obter a informação guardada na lista ligada
 * 
 * @param data Lista ligada com a informação
 * 
 * @return Retorna a string pretendida
 */
char *obtain_dataInfo(DATA data)
{
    return strdup(data->info);
}

/**
 * @brief Função que permite obter o valor do counter da estrutura numa determinada posição
 * 
 * @param a Array com topUserStruc como elementos
 * 
 * @param i Indice a procurar no array
 * 
 * @return Retorna o valor do counter na posição i
 */
int obtain_TopUsersCount (TOPUSERSSTRUCT a, int i)
{
    return (a[i].counter);
}

/**
 * @brief Função que permite obter a string login da estrutura numa determinada posição
 * 
 * @param a Array com topUserStruc como elementos
 * 
 * @param i Indice a procurar no array
 * 
 * @return Retorna a string login na posição i
 */
char *obtain_TopUsersLogin (TOPUSERSSTRUCT a, int i)
{
    return strdup(a[i].login);
}

/**
 * @brief Função que permite obter a string ID da estrutura numa determinada posição
 * 
 * @param a Array com topUserStruct como elementos
 * 
 * @param i Indice a procurar no array
 * 
 * @return Retorna a string ID na posição i
 */
char *obtain_TopUsersId (TOPUSERSSTRUCT a, int i)
{
    return strdup(a[i].id);
}

/**
 * @brief Função que obtém os valores presentes num determinado índice do array
 *  
 * @param a Array com topUsersStruct como elementos
 * 
 * @param i Indice a utilizar no array
 * 
 * @param login Variável onde irá ser guardada a string login
 * 
 * @param id Variável onde irá ser guardada a string ID
 * 
 * @param count Variável onde irá ser guardado o valor do counter
 */
void obtain_topUsers(TOPUSERSSTRUCT a, int i, char *login, char *id, int *count)
{
    *count = a[i].counter;
    login = strdup(a[i].login);
    id = strdup(a[i].id);
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
 * @brief Função que permite libertar o espaço ocupado pela estrutura Data
 * 
 * @param head Lista Ligada
 */
void freeData(DATA head)
{
    DATA tmp;

    while(head != NULL)
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
 * @param count Variável onde será guardado o número de valores da lista ligada
 * 
 * @return Retorna a lista ligada com a informação e o respetivo número de ocorrências.
 */
STRING countInfoStr(STRING top, char *info, int *count)
{
   STRING aux = top;
    STRING nova;
    STRING ant = NULL;
    
    while (aux != NULL && strcmp(aux->info,info)!=0) 
    { 
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
 * @brief Função que permite obter o valor máximo de ocorrências de uma lista ligada.
 * 
 * @param string Lista ligada com a informação.
 * 
 * @return Retorna a string com a informação relativa ao maior número de ocorrências da lista ligada.
 */
char *mostFreqString(STRING string)
{
    STRING freq = NULL;
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
 * @brief Função que inicializa o array da estrutura de dados topUsersStruct
 * 
 * @param N Tamanho do array com elementos do tipo topUsersStruct
 * 
 * @return Retorna o endereço para o início do array
 */
TOPUSERSSTRUCT initTopUsersStruct (int N) 
{
    TOPUSERSSTRUCT topUsers = malloc (N * sizeof (struct topUsersStruct));
    for(int i = 0; i < N; i++) 
    {
        topUsers[i].counter = 0;
        topUsers[i].login = NULL;
        topUsers[i].id = NULL;
    }

    return topUsers;
}

/**
 * @brief Função que organiza os elementos do array de topUsersStruct
 * 
 * @param a Array com topUsersStruct como elementos
 * 
 * @param f Indíce a utilizar no array
 */
void topUsersSort (TOPUSERSSTRUCT a, int f)
{
    a[f].counter = a[f-1].counter;
    a[f].id = strdup(a[f-1].id);
    a[f].login = strdup(a[f-1].login);
}

/**
 * @brief Função que elimina os elementos do array de topUsersStruct
 * 
 * @param topUsers Array com topUsersStruct como elementos
 * 
 * @param N Tamanho do array
 */
void freeTopUsersStructs(TOPUSERSSTRUCT topUsers, int N)
{
    for(int i=0; i < N; i++)
    {
        free(topUsers[i].id);
        free(topUsers[i].login);
    }

    free(topUsers);
}