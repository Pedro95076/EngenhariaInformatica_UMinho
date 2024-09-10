/**
  * @file Ficheiro com modularidade e encapsulamento referente ao catálogo de Repositórios.
  */
#include "data_repos.h"

/**
  * @brief Definição da struct repos
  */
struct repos
{
    /** string que contém o id do repositório */
    char *id;
    /** string que contém o id do dono repositório */
    char *owner_id;
    /** string que contém o nome do repositório */
    char *full_name;
    /** string que contém a licensa do repositório */
    char *license;
    /** string que verifica se o repositório tem wiki */
    char *has_wiki;
    /** string que contém a descrição do repositório */
    char *description;
    /** string que contém o idioma do repositório */
    char *language;
    /** string que refere o default branch */
    char *default_branch;
    /** string que contém a data de criação do repositório */
    char *created_at;
    /** string que contém a data do último update do repositório */
    char *updated_at;
    /** string que contém o número de cópias do repositório */
    char *forks_count;
    /** string que contém o número de problemas em aberto */
    char *open_issues;
    /** string que contém o númerod de stargazers */
    char *stargazers_count;
    /** string que contém o tamanho do repositório */
    char *size;
    /** struct de repositórios que aponta para o próximo repositório */
    struct repos * next;
};

/**
  * @brief Função que guarda no catálogo os repositórios do ficheiro "repos-g2.csv".
  * 
  * @param file Ficheiro "repos-g2.csv".
  *
  * @return Retorna uma lista ligada com os repositórios - Catálogo de Repositórios.
  */
REPOS insertDataRepos(FILE *file)
{
    REPOS reposList = malloc(sizeof(struct repos));
    REPOS iniRepos = reposList;
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
                reposList->id = aux;
                break;
            case 1:
                reposList->owner_id = aux;
                break;
            case 2:
                reposList->full_name = aux;
                break;
            case 3:
                reposList->license = aux;
                break;
            case 4:
                reposList->has_wiki = aux;
                break;
            case 5:
                reposList->description = aux;
                break;
            case 6:
                reposList->language = aux;
                break;
            case 7:
                reposList->default_branch = aux;
                break;
            case 8:
                reposList->created_at = aux;
                break;
            case 9:
                reposList->updated_at = aux;
                break;
            case 10:
                reposList->forks_count = aux;
                break;
            case 11:
                reposList->open_issues = aux;
                break;
            case 12:
                reposList->stargazers_count = aux;
                break;
            case 13:
                reposList->size = aux;
                break;
            default:
                break;
            }
            i++;

            if(i==14) 
            {
                REPOS n = malloc(sizeof (struct repos));
                reposList->next = n;
                reposList = reposList->next;
            }

            aux = strsep(&str, ";\n\r");
        }    
        i=0;
    }
    reposList->next = NULL;
    
    return iniRepos;
}

/**
 * @brief Função que verifica se a lista chegou ao fim.
 * 
 * @param repos Lista ligada com todos os repositórios.
 * 
 * @return Retorna 1 se a lista chegou o fim.
 */
int isEmptyRepos(REPOS repos){
    int r = 0;
    if(repos->next==NULL)r = 1;
    return r;
}

/**
 * @brief Função que permite obter o próximo repositório do catálogo.
 * 
 * @param repos Catálogo dos repositórios.
 * 
 * @return Retorna o nodo do próximo repositório.
 */
REPOS obtain_nextRepos(REPOS repos)
{
    repos = repos->next;
    return repos;
}

/**
 * @brief Função que permite obter a linguagem utilizada no repositório no catálogo.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @return Retorna a linguagem do repositório.
 */
char * obtain_langRepos(REPOS repos)
{
    return strdup(repos->language);
}

/**
 * @brief Função que permite obter a data de update do repositório no catálogo.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @return Retorna a data de update do repositório.
 */
char * obtain_reposDate(REPOS repos)
{
    return strdup(repos->updated_at);
}

/**
 * @brief Função que permite obter o ID do repositório no catálogo.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @return Retorna o ID do repositório.
 */
char * obtain_reposID(REPOS repos)
{
    return strdup(repos->id);
}

/**
 * @brief Função que permite obter o ID do dono do repositório no catálogo.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @return Retorna o ID do dono do repositório.
 */
char * obtain_reposOwnerID(REPOS repos)
{
    return strdup(repos->owner_id);
}

/**
 * @brief Função que permite obter a descrição do repositório no catálogo.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @return Retorna a descrição do repositório.
 */
char * obtain_reposDescription(REPOS repos)
{
    return strdup(repos->description);
}

/**
 * @brief Função que permite libertar o espaço ocupado pelo catálogo de Repositórios.
 * 
 * @param head Catálogo de Commits.
 *
 */
void freeRepos(REPOS head)
{
   REPOS tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}