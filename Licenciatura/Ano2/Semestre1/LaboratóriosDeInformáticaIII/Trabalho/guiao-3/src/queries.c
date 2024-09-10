/**
 * @file Ficheiro com modularidade e encapsulamento referente às queries
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queries.h"
#include "auxiliarFunc.h"
#include "auxiliarStruct.h"
#include "HT_users.h"

/**
 * @brief Função referente à query 1(quantidade de bots, organization e users)
 * 
 * @param n_file Ficheiro onde irão ser imprimidos os resultados da query
 * 
 * @param users Hashtable dos users
 */
void query1(char *n_file, HT_Users *users)
{
    int countBot = countTypeBots(users);
    int countOrganization = countTypeOrganizations(users);
    int countUser = countTypeUsers(users);


    FILE *file = fopen(n_file,"w");
    fprintf(file, "Bots = %d\nOrganizations = %d\nUsers = %d\n", countBot, countOrganization, countUser);

    fclose(file);
}

/**
 * @brief Função referente à query 2(número médio de colaboradores por repositório)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query2(char *n_file, HT_Commits *commits, HT_Repos *repos)
{
    TREE colabs = NULL;

    float counterRepos = countRepos(repos);

    colabs = getAllColabs(commits, colabs);

    float colab = countnodes(colabs);
    float avg = colab/counterRepos;

    FILE *file = fopen(n_file, "w");
    fprintf(file, "%0.2f\n", avg);

    //freeTree(colabs);
    fclose(file);

}

/**
 * @brief Função referente à query 3(quantidade de repositórios com bots)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 */
void query3(char *n_file, HT_Users *users, HT_Commits *commits)
{
    TREE bots = NULL;
    TREE repos = NULL;

    bots = countBotsTree(users, bots);

    repos = countAllBotsColabs(commits, bots, repos);

    int count = countnodes(repos);

    FILE *file = fopen(n_file,"w");
    fprintf(file, "%d\n", count);

    fclose(file);
}

/**
 * @brief Função referente à query 4(quantidade média de commits por utilizador)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 */
void query4(char *n_file, HT_Users *users, HT_Commits *commits)
{
    float counterUsers = countUsers(users);
    float counterCommits = countCommits(commits);

    float avg = counterCommits/counterUsers;

    FILE *file = fopen(n_file,"w");
    fprintf(file, "%0.2f\n", avg);

    fclose(file);
}

/**
 * @brief Função referente à query 5(top N utilizadores mais ativos num intervalo de datas)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param commits Hashtable dos commits
 * 
 * @param users Hashtable dos users
 */
void query5(char *n_file, char *line, HT_Commits *commits, HT_Users *users)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *start_date = strsep(&line, " ");
    char *end_date = strsep(&line, " ");

    compareAllDates(commits, users, end_date, start_date);

    TOPUSERSSTRUCT topUsers = NULL;
    topUsers = initTopUsersStruct (N);

    topUsers = activeUsers(users, topUsers, N);

    FILE *file = fopen(n_file,"w");

    for(int i = 0; i < N; i++) 
    {

        char *auxID = obtain_TopUsersId (topUsers, i);
        char *auxLOGIN = obtain_TopUsersLogin (topUsers, i);
        int auxCOUNTER = obtain_TopUsersCount (topUsers, i);

        fprintf(file,"%s;%s;%d\n", auxID, auxLOGIN, auxCOUNTER);

        //free(auxID);
        //free(auxLOGIN);
    }

    //freeTopUsersStruct(topUsers);
    fclose(file);
}

/**
 * @brief Função referente à query 6(top N de utilizadores com mais commits em repositórios de uma determinada linguagem)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query6(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *aux = strsep(&line, " ");
    char *lang = strsep(&aux, " \n\r");
    int flag = 0;
    
    countCommitsReposLanguage(commits, repos, users, lang, flag);

    TOPUSERSSTRUCT topUsers = NULL;
    topUsers = initTopUsersStruct (N);

    topUsers = activeUsers(users, topUsers, N);

    FILE *file = fopen(n_file,"w");

    for(int i = 0; i < N; i++) 
    {

        char *auxID = obtain_TopUsersId (topUsers, i);
        char *auxLOGIN = obtain_TopUsersLogin (topUsers, i);
        int auxCOUNTER = obtain_TopUsersCount (topUsers, i);

        fprintf(file,"%s;%s;%d\n", auxID, auxLOGIN, auxCOUNTER);

        //free(auxID);
        //free(auxLOGIN);
    }

    //freeTopUsersStruct(topUsers);
    fclose(file);
}

/**
 * @brief Função referente à query 7(repositórios inativos a partir de uma determinada data)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query7(char *n_file, char *line, HT_Commits *commits, HT_Repos *repos)
{
    char *aux = strsep(&line, " ");
    char *start_date = strsep(&aux, "\n");
    DATA reposId = NULL;
    char *idAnt = "a";

    reposId = find_inactiveRepos(reposId, commits, start_date);

    FILE *file = fopen(n_file, "w");

    if(reposId == NULL) fprintf(file, "%s\n", "There aren't repos inactive after that date");
    else
    {
        while(isEmptyData(reposId) == 0)
        {
            char *description = NULL;
            char *id = obtain_dataInfo(reposId);

            if(strcmp(id, idAnt) != 0)
            {
                description = find_reposDescription(repos, id);
                fprintf(file, "%s;%s\n", id, description);
            }

            idAnt = obtain_dataInfo(reposId);

            //free(description);
            //free(id);
        
            reposId = obtain_nextData(reposId);
        }
    }


    //free(idAnt);
    //freeData(reposId);
    fclose(file);
}

/**
 * @brief Função referente à query 8(top N de linguagens mais utilizadas a partir de uma determinada data)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param repos Hashtable dos repositórios
 */
void query8(char *n_file, char *line, HT_Repos *repos)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *aux = strsep(&line, " ");
    char *start_date = strsep(&aux, "\n");
    STRING langTop = NULL;
    int count = 0;

    langTop = countLanguageRepos(repos, start_date, langTop, &count);

    char *finalLang = NULL;

    FILE *file = fopen(n_file, "w");

    for (int i=0; i < N; i++)
    {
        finalLang = mostFreqString(langTop);
        if(i!=N)
        {
            fprintf(file, "%s\n", finalLang);
        }
    }

    //freeString(langTop);
    fclose(file);
}

/**
 * @brief Função referente à query 9(top N de utilizadores com mais commits em repositórios cujo owner é um amigo seu)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query9(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    STRING string = NULL;
    int count = 0;

    string = counter_AllCommiters(string, commits, users, repos, &count);
    
    char *id, *login;

    FILE *file = fopen(n_file, "w");
    for(int i=0; i< N && count > 1; i++)
    {
        id = mostFreqString(string);
        login = find_userLogin(users, id);
        fprintf(file, "%s;%s\n", id, login);
        count--;
    }

    //freeString(string);
    fclose(file);
}

/**
 * @brief Função referente à query 10(top N de utilizadores com as maiores mensagens de commit por repositório)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query10(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);

    FILE *file = fopen(n_file,"w");

    for (int i=0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = find_HashTableReposKey(repos, i);

        while(aux != NULL)
        {
            char *repoID = obtain_reposId(aux);
            topNrepo(repoID, users, commits, file, N);

            aux = obtain_nextRepos(aux);
        }
    }

    fclose(file);

}

/**
 * @brief Função referente à query 11(top N utilizadores mais ativos num repositório específico)
 * 
 * @param n_file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query11(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos){
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *aux = strsep(&line, " ");
    char *repoID = strsep(&aux, "\n\r");

    FILE *file = fopen(n_file,"w");
    topNrepo(repoID, users, commits, file, N);
    fclose(file);
}

/**
 * @brief Função que trata do fluxo de ação das queries
 * 
 * @param i Variável com o valor a atribuir ao ficheiro de resultados
 * 
 * @param id ID da query
 * 
 * @param line Linha de comando com as informações necessárias
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void handle_Queries(int i, int id, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    char fileName[1024];
    sprintf(fileName, "./saida/command%d_output.txt", i);
    switch (id)
    {
    case 1:
        query1(fileName, users);
        break;
    case 2:
        query2(fileName, commits, repos);
        break;
    case 3:
        query3(fileName, users, commits);
        break;
    case 4:
        query4(fileName, users, commits);
        break;
    case 5:
        query5(fileName, line, commits, users);
        break;
    case 6:
        query6(fileName, line, users, commits, repos);
        break;
    case 7:
        query7(fileName, line, commits, repos);
        break;
    case 8:
        query8(fileName, line, repos);
        break;
    case 9:
        query9(fileName, line, users, commits, repos);
        break;
    case 10:
        query10(fileName, line, users, commits, repos);
        break;
    case 11:
        query11(fileName, line, users, commits, repos);
        break;
    default:
        break;
    }
}