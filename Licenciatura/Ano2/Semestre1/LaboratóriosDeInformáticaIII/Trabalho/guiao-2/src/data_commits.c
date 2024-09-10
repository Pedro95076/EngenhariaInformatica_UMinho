/**
  * @file Ficheiro com modularidade e encapsulamento referente ao catálogo de Commits.
  */
#include "data_commits.h"

/**
  * @brief Definição da struct commits
  */
struct commits
{
    /** string que contém o id do repositório */
    char *repo_id;
    /** string que contém o id do autor do commit */
    char *author_id;
    /** string que contém o id do commiter */
    char *commiter_id;
    /** string que contém a data que o commit foi feito */
    char *commit_at;
    /** string que contém a mensagem do commit */
    char *message;
    /** struct de commits que aponta para o próximo commit */
    struct commits *next;
};

/**
  * @brief Função que guarda no catálogo os commits do ficheiro "commits-g2.csv".
  * 
  * @param file Ficheiro "commits-g2.csv".
  * 
  * @return Retorna uma lista ligada com os commits - Catálogo de commits.
  */
COMMITS insertDataCommits(FILE *file)
{
    COMMITS commitsList = malloc(sizeof(struct commits));
    COMMITS iniCommits = commitsList;
    char c[524288];
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
                commitsList->repo_id = aux;
                break;
            case 1:
                commitsList->author_id = aux;
                break;
            case 2:
                commitsList->commiter_id = aux;
                break;
            case 3:
                commitsList->commit_at = aux;
                break;
            case 4:
                commitsList->message = aux;
                break;
            default:
                break;
            }
            i++;

            if(i==5) 
            {
                COMMITS n = malloc(sizeof (struct commits));
                commitsList->next = n;
                commitsList = commitsList->next;
            }
            aux = strsep(&str, ";\n\r");
        }    
        i=0;
    }
    commitsList->next = NULL;

    return iniCommits;
}

/**
 * @brief Função que verifica se a lista chegou ao fim.
 * 
 * @param commits Lista ligada com todos os commits.
 * 
 * @return Retorna 1 se a lista chegou o fim.
 */
int isEmptyCommits(COMMITS commits){
    int r = 0;
    if(commits->next==NULL)r = 1;
    return r;
}

/**
 * @brief Função que permite obter o próximo commit do catálogo.
 * 
 * @param commits Catálogo dos commits.
 * 
 * @return Retorna o nodo do próximo commit.
 */
COMMITS obtain_nextCommit(COMMITS commits)
{
    commits = commits->next;
    return commits;
}

/**
 * @brief Função que permite obter o ID do repositório no Catálogo de Commits.
 * 
 * @param commits Catálogo de Commits.
 * 
 * @return Retorna o ID do repositório do commit.
 */
char * obtain_commitsReposId(COMMITS commits)
{
    return strdup(commits->repo_id);
}

/**
 * @brief Função que permite obter o ID do autor do repositório no catálogo.
 * 
 * @param commits Catálogo de Commits.
 * 
 * @return Retorna o ID do autor do repositório.
 */
char * obtain_commitsAuthorId(COMMITS commits)
{
    return strdup(commits->author_id);
}

/**
 * @brief Função que permite obter  a data do commit no catálogo.
 * 
 * @param commits Catálogo de Commits.
 * 
 * @return Retorna a data do commit.
 */
char * obtain_commitsDate(COMMITS commits)
{
    return strdup(commits->commit_at);
}

/**
 * @brief Função que permite obter o ID do commiter no catálogo.
 * 
 * @param commits Catálogo de Commits.
 * 
 * @return Retorna o ID do commiter.
 */
char * obtain_commiterId(COMMITS commits)
{
    return commits->commiter_id;
}

/**
 * @brief Função que permite obter a mensagem do commit no catálogo.
 * 
 * @param commits Catálogo de Commits.
 *
 * @return Retorna a mensagem do commit.
 */
char * obtain_messageCommit(COMMITS commits)
{
    return strdup(commits->message);
}

/**
 * @brief Função que permite libertar o espaço ocupado pelo catálogo de Commits.
 * 
 * @param head Catálogo de Commits.
 *
 */
void freeCommits(COMMITS head)
{
   COMMITS tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}