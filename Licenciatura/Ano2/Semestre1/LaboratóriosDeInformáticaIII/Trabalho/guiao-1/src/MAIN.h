/**
  * @file Headfile do parser.c.
  */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


/**
  * @brief Definição do tipo enum do type do ficheiro "users.csv".
  */
typedef enum {
    /** enum tipo Bot */
    Bot, 
    /** enum tipo Organization */
    Organization, 
    /** enum tipo User */
    User
} TYPE;

/**
  * @brief Definição do tipo enum booleano.
  */
typedef enum {
    /** enum tipo True */
    True = 1, 
    /** enum tipo False */
    False = 0
} BOOL;

/**
  * @brief Definição da struct users
  */
typedef struct users
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
    /** string que contém a linha lida do ficheiro referente a este user */
    char *line;
    /** struct de users que aponta para o próximo user */
    struct users *next;
    
} *USERS;

/**
  * @brief Definição da struct commits
  */
typedef struct commits
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
    /** string que contém a linha lida do ficheiro referente a este commit  */
    char *line;
    /** struct de commits que aponta para o próximo commit */
    struct commits *next;
} *COMMITS;

/**
  * @brief Definição da struct repos
  */
typedef struct repos
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
    /** string que contém a linha lida do ficheiro referente a este repositório */
    char *line;
    /** struct de repositórios que aponta para o próximo repositório */
    struct repos * next;
} *REPOS;

/**
  * @brief Definição da struct tree
  */
typedef struct tree 
{
    /** valor inteiro do nodo */
	int value;
    /** struct das árvores que aponta para os nodos da esquerda e da direita */
	struct tree *l, *r;
} *TREE;


void handle_UsersFile(FILE *file, USERS user, USERS head, char *headline);
void handle_CommitsFile(FILE *file, COMMITS commit, COMMITS head, char *headline);
void handle_ReposFile(FILE *file, REPOS reposList, REPOS head, char *headline);
int testDateHour(char *string);
int testInt(char *string);
int testString(char *string);
TREE handle_id(FILE *file);
void filterCommits(FILE *file, TREE idStore, TREE reposIdStore, char *headline);
void filterRepos(FILE *file, TREE idStore, TREE commitsReposId, char *headline);
int search(TREE a, int x);