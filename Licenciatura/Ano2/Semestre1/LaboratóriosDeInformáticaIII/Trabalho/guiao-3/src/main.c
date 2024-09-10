/**
 * @file Ficheiro com modularidade e encapsulamento referente à função main
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "HT_users.h"
#include "HT_commits.h"
#include "HT_repos.h"
#include "verification.h"
#include "auxiliarFunc.h"
#include "queries.h"
#include "interface.h"



/**
 * @brief Função que controla o fluxo da execução do programa com ficheiros
 * 
 * @param commands Ficheiro com os comandos a executar
 * 
 * @return Retorna 0
 */
int mainWithFile(FILE *commands)
{
    char c[10240];

    time_t start_t1, end_t1;
    double diff_t1;

    time(&start_t1);

    FILE *users_file = fopen("./entrada/users-g3.csv", "r");
    check_File(users_file);
    fgets(c, 524288, users_file);
    HT_Users users[TABLE_SIZE];
    handle_UsersFile(users_file, users);
    fclose(users_file);
    //print_tableUsers(users);

    FILE *commits_file = fopen("./entrada/commits-g3.csv", "r");
    check_File(commits_file);
    fgets(c, 524288, commits_file);
    HT_Commits commits[TABLE_SIZE];
    handle_CommitsFile(commits_file, commits, users);
    fclose(commits_file);
    //print_tableCommits(commits);

    FILE *repos_file = fopen("./entrada/repos-g3.csv", "r");
    check_File(repos_file);
    fgets(c, 524288, repos_file);
    HT_Repos repos[TABLE_SIZE];
    handle_ReposFile(repos_file, repos, users);
    fclose(repos_file);
    //print_tableRepos(repos);

    filterCommits(commits, repos);
    filterRepos(commits, repos);
    
    time(&end_t1);

    diff_t1 = difftime(end_t1, start_t1);

    time_t start_t2, end_t2;
    float diff_t2;

    check_File(commands);
    int i=1;


    while (fgets(c, 524288, commands) != NULL)
    {
        char *line = strdup(c);
        char *aux = strsep(&line, " ");
        int id = atol(aux);

        time(&start_t2);

        handle_Queries(i,id, line, users, commits, repos);

        time(&end_t2);

        diff_t2 = difftime(end_t2, start_t2);

        printf("\ntempo da query %d: %f", id, diff_t2);

        if(id == 5) resetUsersCounter(users);
        if(id == 6) resetUsersCounter(users);

        i++;
    }
    fclose(commands);

    printf("\ntempo do catalogo : %f\n\n", diff_t1);
    
    //free_TableUsers(users);
    //free_TableCommits(commits);
    //free_TableRepos(repos);
    
    return 0;
}

/**
 * @brief Função que  controla o fluxo da execução do programa sem ficheiros
 * 
 * @return Retorna 0
 */
int mainWithoutFile()
{
    char c[10240];

    FILE *users_file = fopen("./entrada/users-g3.csv", "r");
    check_File(users_file);
    fgets(c, 524288, users_file);
    HT_Users users[TABLE_SIZE];
    handle_UsersFile(users_file, users);
    fclose(users_file);
    //print_tableUsers(users);

    FILE *commits_file = fopen("./entrada/commits-g3.csv", "r");
    check_File(commits_file);
    fgets(c, 524288, commits_file);
    HT_Commits commits[TABLE_SIZE];
    handle_CommitsFile(commits_file, commits, users);
    fclose(commits_file);
    //print_tableCommits(commits);

    FILE *repos_file = fopen("./entrada/repos-g3.csv", "r");
    check_File(repos_file);
    fgets(c, 524288, repos_file);
    HT_Repos repos[TABLE_SIZE];
    handle_ReposFile(repos_file, repos, users);
    fclose(repos_file);
    //print_tableRepos(repos);

    filterCommits(commits, repos);
    filterRepos(commits, repos);
    
    mainMenu(users, commits, repos);

    return 0;
}

/**
 * @brief Função que controla o fluxo do programa
 * 
 * @param argc Argumento a introduzir na linha de comandos
 * 
 * @param argv Array do número de argumentos a introduzir na linha de argumentos
 * 
 * @return Retorna 0
 */

int main(int argc, char const *argv[])
{
    if(argc == 2 && strcmp(argv[1],"commands.txt") == 0)
    {
        FILE *file = fopen(argv[1], "r");
        mainWithFile(file);
    }
    else
    {
        mainWithoutFile();
    }
}