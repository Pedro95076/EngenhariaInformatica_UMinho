/**
  * @file Ficheiro principal.
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "MAIN.h"

/**
  * @brief Função que testa se o parâmetro recebido é um tipo válido de int.
  *
  * @param str Parâmetro (no tipo string) a ser testado.
  *
  * @return Retorna 0 se for do tipo Int e 1 se não for.
  */
int testInt(char *str)
{
    int r = 0, i = 0;

    if(str[i] == '\0' || str[i] == '\n' || str[i] == '\r') r = 1;

    for (i=0; str[i]!='\0' && r==0; i++)
    {
        if(str[i]>=48 && str[i]<=57) r = 0;
        else r=1;
    }

    return r;
}

/**
  * @brief Função que testa se o parâmetro recebido é um tipo válido de string.
  *
  * @param str Parâmetro (no tipo string) a ser testado.
  *
  * @return Retorna 0 se for do tipo String e 1 se não for.
  */
int testString(char *str)
{
    int r = 0, i = 0;

    if (str[i] == '\0') r=1;
    else r = 0;

    return r;
}

/**
  * @brief Função que testa se a string dada represanta uma data válida. \n
  * Foi usada a libraria "time.h", para a verificação da data.
  * 
  * @param str Parâmetro (no tipo string) a ser testado.
  * 
  * @return Retorna 0 se for uma data válida e 1 se não for.
  */
int testDateHour(char *str) 
{
    int r = 0;
    
    if(str[0] == '\0') r=1;


    if (r==0) 
    { 
        char *strcopy = strdup(str);
        
        int ano;
        int mes;
        int dia;
        int hora;
        int minuto;
        int segundo;
        int a, b, c;

    if (sscanf(strcopy,"%d-%d-%d %d:%d:%d+%d:%d",&ano,&mes,&dia,&hora,&minuto,&segundo,&a,&b) == 8) {
        if(a==0 && b==0) r = 0;
            else r = 1;
    }
    else if (sscanf(strcopy,"%d-%d-%d %d:%d:%d-%d:%d",&ano,&mes,&dia,&hora,&minuto,&segundo,&a,&b) == 8) {
        if(a==0 && b==0) r = 0;
            else r = 1;
    }
    else if (sscanf(strcopy,"%d-%d-%d %d:%d:%d.%d",&ano,&mes,&dia,&hora,&minuto,&segundo,&c) == 7) r = 1;
    else if (sscanf(strcopy,"%d-%d-%d %d:%d:%d",&ano,&mes,&dia,&hora,&minuto,&segundo) != 6) r=1;

    if(r==0)
    {
        // Usa a struct tm da biblioteca time.h para armazenar a data
        struct tm createdAt;
        createdAt.tm_year = ano - 1900;
        createdAt.tm_mon = mes - 1;
        createdAt.tm_mday = dia;
        createdAt.tm_hour = hora;
        createdAt.tm_min = minuto;
        createdAt.tm_sec = segundo;
        createdAt.tm_isdst = -1;

        if (createdAt.tm_year + 1900 == ano &&
        createdAt.tm_mon + 1 == mes &&
        createdAt.tm_mday == dia &&
        createdAt.tm_hour == hora &&
        createdAt.tm_min == minuto &&
        createdAt.tm_sec == segundo) r = 0;
        else r = 1;
        
        // Data limite minimo
        struct tm minimumDeadline;
        minimumDeadline.tm_year = 2005 - 1900;
        minimumDeadline.tm_mon = 4 - 1;
        minimumDeadline.tm_mday = 7;
        minimumDeadline.tm_hour = 0;
        minimumDeadline.tm_min = 0;
        minimumDeadline.tm_sec = 1;
        minimumDeadline.tm_isdst = -1;
        
        // Testa se a data recebida é anterior à data de hoje e superior a data minimumDeadline
        time_t today = time(NULL);
        time_t givenDate = mktime(&createdAt);
        time_t minimum = mktime(&minimumDeadline);
        if(r == 0 && (givenDate - today <= 0) && (minimum - givenDate <= 0)) r = 0;
        else r = 1;
        }
    } 

    return r;
}

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
  * @brief Função main que executa o exercicio 1 e 2.
  *
  * @param argc Quantidade de argumentos usados no momento da execução.
  *
  * @param argv String que determina o exercicio a ser executado.
  */
int main(int argc, char *argv[])
{
      if(argc == 2 && strcmp(argv[1],"exercicio-1") == 0) 
    {
        // --> USERS FILE
        USERS users = malloc(sizeof (struct users));
        USERS head1 = users;
        char headline_users[1024];

        FILE *users_file = fopen("../guiao-1/entrada/users.csv", "r");
        check_File(users_file);
        fgets(headline_users, sizeof(headline_users), users_file);
        handle_UsersFile(users_file, users, head1, headline_users);

        // --> COMMITS FILE
        COMMITS commits = malloc(sizeof (struct commits));
        COMMITS head2 = commits;
        char headline_commits[1024];

        FILE *commits_file = fopen("../guiao-1/entrada/commits.csv", "r");
        check_File(commits_file);
        fgets(headline_commits, sizeof(headline_commits), commits_file);
        handle_CommitsFile(commits_file, commits, head2, headline_commits);

        // --> REPOS FILE
        REPOS repos = malloc(sizeof (struct repos));
        REPOS head3 = repos;
        char headline_repos[1024];

        FILE *repos_file = fopen("../guiao-1/entrada/repos.csv", "r");
        check_File(repos_file);
        fgets(headline_repos, sizeof(headline_repos), repos_file);
        handle_ReposFile(repos_file, repos, head3, headline_repos);
    }
    
    if(argc == 2 && strcmp(argv[1],"exercicio-2") == 0)
    {
        //Armazena os ids dos users
        FILE *usersok_file = fopen("../guiao-1/saida/users-ok.csv", "r");
        char headline_usersok[1024];
        fgets(headline_usersok, sizeof(headline_usersok), usersok_file);
        TREE idStore = handle_id(usersok_file);

        //Armazena os ids dos users
        FILE *reposok_file = fopen("../guiao-1/saida/repos-ok.csv", "r");
        char headline_reposok[1024];
        fgets(headline_reposok, sizeof(headline_reposok), reposok_file);
        TREE reposIdStore = handle_id(reposok_file);

        //Filtrar o file commits
        FILE *commitsok_file = fopen("../guiao-1/saida/commits-ok.csv", "r");
        char headline_commitsok[1024];
        fgets(headline_commitsok, sizeof(headline_commitsok), commitsok_file);
        filterCommits(commitsok_file, idStore, reposIdStore, headline_commitsok);

        //Filtrar o file repos
        FILE *commitsfinal_file = fopen("../guiao-1/saida/commits-final.csv", "r");
        FILE *usersfinal_file = fopen("../guiao-1/saida/users-ok.csv", "r");
        FILE *reposfinal_file = fopen("../guiao-1/saida/repos-ok.csv", "r");
        char headline_reposfinal[1024];
        fgets(headline_reposfinal, sizeof(headline_reposfinal), reposfinal_file);

        TREE commitsReposId = handle_id(commitsfinal_file);
        TREE idStore2 = handle_id(usersfinal_file);

        filterRepos(reposfinal_file, idStore2, commitsReposId, headline_reposfinal);
    }

    if(argc != 2 || ((strcmp(argv[1],"exercicio-1") != 0) && (strcmp(argv[1],"exercicio-2") != 0))) {
        printf("Invalid arguments\n");
    }  

    return 0;
}