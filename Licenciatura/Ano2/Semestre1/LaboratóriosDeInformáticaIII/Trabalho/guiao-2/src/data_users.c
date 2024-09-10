/**
  * @file Ficheiro com modularidade e encapsulamento referente ao catálogo de Users.
  */
#include "data_users.h"

/**
  * @brief Definição da struct users
  */
struct users
{
    /** string que contém o id */
    char *id; 
    /** string que contém o login */
    char *login;
    /** string que contém o tipo de user */
    char *type;
    /** string que contém a data */
    char *created_at;
    /** string que contém o número de seguidores */
    char *followers;
    /** string que contém a lista dos seguidores */
    char *followers_list;
    /** string que contém o número de seguidores que o user segue */
    char *following;
    /** string que contém a lista dos seguidores que o user segue */
    char *following_list;
    /** string que contém o número de gists */
    char *public_gists;
    /** string que contém o número de repositórios publicos */
    char *public_repos;
    /** struct de users que aponta para o próximo user */
    struct users *next;
};

/**
  * @brief Função que guarda no catálogo os utilizadores do ficheiro "users-g2.csv".
  * 
  * @param file Ficheiro "users-g2.csv".
  * 
  * @return Retorna uma lista ligada com os utilizadores - Catálogo de Utilizadores.
  */
USERS insertDataUsers(FILE *file)
{
    USERS usersList = malloc(sizeof(struct users));
    USERS iniUsers = usersList;
    char c[524288]; //2^19
    char *aux = NULL;
    int i=0;

    while(fgets(c, 524288, file) != NULL)
    {
        char *str = strdup (c);
        aux = strsep(&str, ";\n\r");
        while (aux != NULL)
        {
            switch (i)
            {
            case 0:
                usersList->id = aux;
                break;
            case 1:
                usersList->login = aux;
                break;
            case 2:
                usersList->type = aux;
                break;
            case 3:
                usersList->created_at = aux;
                break;
            case 4:
                usersList->followers = aux;
                break;
            case 5:
                usersList->followers_list = aux;
                break;
            case 6:
                usersList->following = aux;
                break;
            case 7:
                usersList->following_list = aux;
                break;
            case 8:
                usersList->public_gists = aux;
                break;
            case 9:
                usersList->public_repos = aux;
                break;
            default:
                break;
            }
            i++;

            if(i == 10)
            {
                USERS n = malloc(sizeof (struct users));
                usersList->next = n;
                usersList = usersList->next;
            }
            aux = strsep(&str, ";\n\r");
        }    
        i=0;
    }
    usersList->next = NULL;
    
    return iniUsers;
}

/**
 * @brief Função que verifica se a lista chegou ao fim.
 * 
 * @param users Lista ligada com todos os utilizadores.
 * 
 * @return Retorna 1 se a lista chegou o fim.
 */
int isEmptyUsers(USERS users){
    int r = 0;
    if(users->next==NULL)r = 1;
    return r;
}

/**
 * @brief Função que permite obter o próximo utilizador no catálogo.
 * 
 * @param users Catálogo dos utilizadores.
 * 
 * @return Retorna o nodo do próximo utilizador.
 */
USERS obtain_nextUser(USERS users){
    users = users->next;
    return users;
}

/**
 * @brief Função que permite obter qual o tipo do utilizador no catálogo.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna o tipo de utilizador.
 */
char * obtain_typeUsers(USERS users)
{
    return strdup(users->type);
}

/**
 * @brief Função que permite obter qual o ID do utilizador no catálogo.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna o ID do utilizador.
 */
char * obtain_IdUsers(USERS users)
{
    return strdup(users->id);
}

/**
 * @brief Função que permite obter qual o login do utilizador no catálogo.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna o login do utilizador.
 */
char * obtain_LoginUsers(USERS users)
{
    return strdup(users->login);
}

/**
 * @brief Função que permite obter qual o número de followers.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna o número de followers.
 */
char * obtain_followersUsers(USERS users)
{
    return strdup(users->followers);
}

/**
 * @brief Função que permite obter a lista de followers.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna a lista de followers.
 */
char * obtain_followersListUsers(USERS users)
{
    return strdup(users->followers_list);
}

/**
 * @brief Função que permite obter qual o número de following.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna o número de following.
 */
char * obtain_followingUsers(USERS users)
{
    return strdup(users->following);
}

/**
 * @brief Função que permite obter a lista de following.
 * 
 * @param users Catálogo de Utilizadores.
 * 
 * @return Retorna a lista de following.
 */
char * obtain_followingListUsers(USERS users)
{
    return strdup(users->following_list);
}

/**
 * @brief Função que permite libertar o espaço ocupado pelo catálogo de Users.
 * 
 * @param head Catálogo de Users.
 */
void freeUsers(USERS head)
{
   USERS tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}