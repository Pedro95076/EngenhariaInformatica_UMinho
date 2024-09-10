/**
 * @file Ficheiro com modularidade e encapsulamento referente à interface do programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "queries.h"

/**
 * @brief Função auxiliar que conta o número de linhas de um ficheiro
 * 
 * @param file Ficheiro
 * 
 * @return Retorna o número de linhas do ficheiro
 */
int countLines(FILE *file)
{
    int counter = 0;
    char line[10000];
    while(fgets(line, 10000, file))
    {
        counter++;
    }

    return counter;
}

/**
 * @brief Função que trata da interface da query 1
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void query1_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    handle_Queries(1, 1, NULL, users, commits, repos);
    FILE *file = fopen("./saida/command1_output.txt", "r");

    int bots = 0, organizations = 0, user = 0;
    fscanf(file, "Bots = %d\nOrganizations = %d\nUsers = %d\n", &bots, &organizations, &user);
 
    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|                                  Query 1                                     |");
    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              +");
    printf("\n|                          Bot:                %d                               ", bots);
    printf("\n|                          Organization:       %d                               ", organizations);
    printf("\n|                          User:               %d                               ", user);
    printf("\n|                                                                              +");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|  Insira uma nova query:                                                      |");
    printf("\n|                                                                0 para SAIR   |");
    printf("\n+------------------------------------------------------------------------------+\n");

    fclose(file);

    int i = 0;
    scanf("%d", &i);

    if (i==0) system("clear");
    else
    {
        chooseQuery(i, users, commits, repos);
    }
}

/**
 * @brief Função que trata da interface da query 2 a 4
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query2to4_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    handle_Queries(1, query, NULL, users, commits, repos);
    FILE *file = fopen("./saida/command1_output.txt", "r");

    float avg = 0;
    fscanf(file, "%f\n", &avg);
    
    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|                                  Query %d                                     |", query);
    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              +");
    printf("\n|                                    %.2f                                       ", avg);
    printf("\n|                                                                              +");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|  Insira uma nova query:                                                      |");
    printf("\n|                                                                0 para SAIR   |");
    printf("\n+------------------------------------------------------------------------------+\n"); 

    int i = 0;
    scanf("%d", &i);

    if (i==0) mainMenu(users, commits, repos);
    else
    {
        chooseQuery(i, users, commits, repos);
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 5
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query5_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char N[3];
    char start_date[11];
    char end_date[11];

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira o número de utilizadores                                            |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", N);
    
    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|    Insira a data de início                                                    |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", start_date);

    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|    Insira a data de fim                                                       |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", end_date);

    int n = atoi(N);
    
    char line[100];
    strcpy(line, N);
    strcat(line, " ");
    strcat(line, start_date);
    strcat(line, " ");
    strcat(line, end_date);

    handle_Queries(1, 5, line, users, commits, repos);

    char *login[12];
    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = n;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 100, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((n/12)==0) flag = n/12;
            else flag = (n/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 6
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query6_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char N[3];
    char lang[20];

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira o número de utilizadores                                            |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", N);

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira a linguagem pretendida                                              |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", lang);

    int n = atoi(N);

    char line[100];
    strcpy(line, N);
    strcat(line, " ");
    strcat(line, lang);

    handle_Queries(1, 6, line, users, commits, repos);

    char *login[12];
    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = n;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 100, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((n/12)==0) flag = n/12;
            else flag = (n/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 7
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query7_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char date[11];

    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|    Insira a data pretendida                                                   |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", date);

    handle_Queries(1, 7, date, users, commits, repos);
    
    char *login[12];
    char line[10000];
    FILE *lines = fopen("./saida/command1_output.txt", "r");
    int counter = countLines(lines);
    fclose(lines);

    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = counter;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 10000, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((counter/12)==0) flag = counter/12;
            else flag = (counter/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 8
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query8_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char lang[3];
    char date[11];

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira o número de linguagens pretendidas                                  |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", lang);

    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|    Insira a data pretendida                                                   |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", date);

    char line[100];
    strcpy(line, lang);
    strcat(line, " ");
    strcat(line, date);

    handle_Queries(1, 8, line, users, commits, repos);
    
    char *login[12];
    int n = atoi(lang);

    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = n;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 100, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((n/12)==0) flag = n/12;
            else flag = (n/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 9 e 10
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query9and11_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char N[3];

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira o número de utilizadores                                            |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", N);
    
    if(query==9)
    {
         handle_Queries(1, 9, N, users, commits, repos);
    }
    if(query==11)
    {
         handle_Queries(1, 11, N, users, commits, repos);
    }

    char *login[12];
    char line[100];
    int n = atoi(N);

    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = n;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 100, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((n/12)==0) flag = n/12;
            else flag = (n/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que trata da interface da query 9 e 10
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param int ID da query
 */
void query10_interface(HT_Users *users, HT_Commits *commits, HT_Repos *repos, int query)
{
    char N[3];

    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|    Insira o número de utilizadores                                            |");
    printf("\n|------------------------------------------------------------------------------|\n");
    scanf("%s", N);

    handle_Queries(1, 10, N, users, commits, repos);

    char *login[12];
    char line[100];
    int n = atoi(N);
    int counter = countRepos(repos);

    FILE *file = fopen("./saida/command1_output.txt", "r");

    int flag = counter*n;
    while(flag!=0)
    {
        for(int i=0; i < 12 && flag != 0; i++)
        {
            fgets(line, 100, file);
            char *str = strdup(line);
            login[i] = strsep(&str, "\n");
            if(feof(file) != 0) login[i] = " ";
        }

        printf("\n+------------------------------------------------------------------------------+");
        printf("\n|                                  Query %d                                    |", query);
        printf("\n|------------------------------------------------------------------------------|");
        printf("\n|                                                                              +");
        printf("\n|                   %s                                                          ", login[0]);
        printf("\n|                   %s                                                          ", login[1]);
        printf("\n|                   %s                                                          ", login[2]);
        printf("\n|                   %s                                                          ", login[3]);
        printf("\n|                   %s                                                          ", login[4]);
        printf("\n|                   %s                                                          ", login[5]);
        printf("\n|                   %s                                                          ", login[6]);
        printf("\n|                   %s                                                          ", login[7]);
        printf("\n|                   %s                                                          ", login[8]);
        printf("\n|                   %s                                                          ", login[9]);
        printf("\n|                   %s                                                          ", login[10]);
        printf("\n|                   %s                                                          ", login[11]);
        printf("\n|                                                                               ");
        printf("\n|                                 A -> Avançar                                 +");
        printf("\n|  Insira uma nova query:                                                      |");
        printf("\n|                                                                0 para SAIR   |");
        printf("\n+------------------------------------------------------------------------------+\n");

        char a[1];
        scanf("%s", a);

        if(strcmp(a, "A")==0)
        {
            if((counter*n/12)==0) flag = counter*n/12;
            else flag = (counter*n/12)+1;
        }
        else if(strcmp(a, "0")==0)
        {
            mainMenu(users, commits, repos);
        }
        else
        {
            int i = atoi(a);
            chooseQuery(i, users, commits, repos);
        }
    }

    fclose(file);
}

/**
 * @brief Função que seleciona a interface a utilizar consoante a query
 * 
 * @param query ID da query
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void chooseQuery(int query, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    switch(query)
    {
        case 0:
            system("clear");
            //free_TableUsers(users);
            //free_TableCommits(commits);
            //free_TableRepos(repos);
            break;
        case 1:
            query1_interface(users, commits, repos);
            break;
        case 2:
            query2to4_interface(users, commits, repos, query);
            break;
        case 3: 
            query2to4_interface(users, commits, repos, query);
            break;
        case 4:
            query2to4_interface(users, commits, repos, query);
            break;
        case 5:
            query5_interface(users, commits, repos, query);
            break;
        case 6:
            query6_interface(users, commits, repos, query);
            break;
        case 7:
            query7_interface(users, commits, repos, query);
            break;
        case 8:
            query8_interface(users, commits, repos, query);
            break;
        case 9:
            query9and11_interface(users, commits, repos, query);
            break;
        case 10:
            query10_interface(users, commits, repos, query);
            break;
        case 11:
            query9and11_interface(users, commits, repos, query);
        default:
            break;
    }

}

/**
 * @brief Função do menu principal
 * 
 * @param users Hashtable dos users
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 */
void mainMenu(HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    printf("\n+------------------------------------------------------------------------------+");
    printf("\n|                    Das queries abaixo escolha uma:                           |");
    printf("\n|------------------------------------------------------------------------------|");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|  Query 1   |  Quantidade de bots, organizações e utilizadores                |");
    printf("\n|  Query 2   |  Número médio de colaboradores por repositório                  |");
    printf("\n|  Query 3   |  Quantidade de repositórios com bots                            |");
    printf("\n|  Query 4   |  Quantidade média de commits por utilizador                     |");
    printf("\n|  Query 5   |  Top N de utilizadores mais ativos num intervalo de datas       |");
    printf("\n|  Query 6   |  Top N de users com mais commits em repositórios de umlinguagem |");
    printf("\n|  Query 7   |  Repositórios inativos a partir de uma determinada data         |");
    printf("\n|  Query 8   |  Top N de linguagens a partir de uma determinada data           |");
    printf("\n|  Query 9   |  Top N de users com mais commits em repos. cujo owner é amigo   |");
    printf("\n|  Query 10  |  Top N de users com as maiores mensagens por repositório        |");
    printf("\n|  Query 11  |  Top N de users com as maiores mensagens num repositório        |");
    printf("\n|                                                                              |");
    printf("\n|                                                                              |");
    printf("\n|                                                                0 para SAIR   |");
    printf("\n+------------------------------------------------------------------------------+\n");  

    int queryID = 0;
    scanf("%d", &queryID);

    chooseQuery(queryID, users, commits, repos);
}