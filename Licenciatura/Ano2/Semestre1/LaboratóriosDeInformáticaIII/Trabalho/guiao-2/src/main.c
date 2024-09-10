/**
  * @file Ficheiro principal.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_users.h"
#include "data_commits.h"
#include "data_repos.h"
#include "data_tpll.h"
#include "data_tree.h"
#include "data.h"
#include "query.h"

/**
  * @brief Função que testa se o ficheiro passado como argumento existe.
  *
  * @param file Ficheiro a ser testado.
  */
void check_File(FILE *file)
{
    if(file == NULL)
    {
        perror("Unable to open file\n");
        exit(1);
    }
}

/**
 * @brief Função main que abre os ficheiros, cria os catálogos e trata das queries
 * 
 * @param argc Quantidade de argumentos utilizados no momento da execução
 * 
 * @param argv String que determina o exercício a ser executado
 * 
 */
int main(int argc, char const *argv[])
{
    char c[10240];

    //Cria o catálogo dos Utilizadores e uma árvore a partir do mesmo
    FILE *users_file = fopen("./entrada/users-g2.csv", "r");
    check_File(users_file);
    fgets(c, 524288, users_file);
    USERS users = insertDataUsers(users_file);
    TREEUSERS usersArv = iniUsersTREE(users);
    TREEUSERS9 usersArv9 = iniUsersTREE9(users);
    fclose(users_file);

    //Cria o catálogo dos Commits
    FILE *commits_file = fopen("./entrada/commits-g2.csv", "r");
    check_File(commits_file);
    fgets(c, 524288, commits_file);
    COMMITS commits = insertDataCommits(commits_file);
    fclose(commits_file);

    //Cria o catálogo dos Repositórios e uma árvore a partir do mesmo
    FILE *repos_file = fopen("./entrada/repos-g2.csv", "r");
    check_File(repos_file);
    fgets(c, 524288, repos_file);
    REPOS repos = insertDataRepos(repos_file);
    TREEREPOS reposArv = iniReposTREE(repos);
    TREEREPOS reposArv9 = iniReposTREE9(repos);
    fclose(repos_file);

    //Faz o tratamento das queries e cria os ficheiros finais
    FILE *commands = fopen(argv[1], "r");
    check_File(commands);
    int i=1;
    while (fgets(c, 524288, commands) != NULL)
    {
        char *line = strdup(c);
        char *aux = strsep(&line, " ");
        int id = atol(aux);
        queryID(i,id, line, users, commits, repos, usersArv, reposArv, usersArv9, reposArv9);
        i++;
    }
    fclose(commands);
    freeUsers(users);
    freeCommits(commits);
    freeRepos(repos);
    return 0;
}
