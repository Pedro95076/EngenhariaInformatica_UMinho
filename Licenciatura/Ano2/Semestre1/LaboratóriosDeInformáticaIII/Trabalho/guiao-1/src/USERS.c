/**
  * @file Ficheiro referente ao exercicio 1 do ficheiro "users.csv".
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "MAIN.h"

/**
  * @brief Função que imprime as linhas que estão corretas no ficheiro "users-ok.csv".
  * 
  * @param file Ficheiro "users.csv".
  *
  * @param usersList Struct que armazena os usuários corretos.
  *
  * @param headline Headline do documento "users.csv".
  */
void printUsersFile(FILE *file, USERS usersList, char *headline) 
{
    fprintf(file,"%s", headline);

    while (usersList->next != NULL) 
    {
        fprintf(file, "%s", usersList->line);
        // Avança para o próximo usuário
        usersList = usersList->next;
        }
}

/**
  * @brief Função que testa se a lista dos Followers está correta.
  * 
  * @param users Usuário da linha que está a ser testada.
  *
  * @param str Parâmetro (no tipo string) a ser testado.
  *
  * @return Retorna 0 se o parâmetro estiver correto e 1 se não tiver.
  */
int testFollowersList(USERS users, char *str)
{
    int r;
    int count=0;
    int followers = atol(users->followers);

    if (str[0] != '[') r = 1;
    else if (strcmp(str,"[]") == 0 && followers == 0) r = 0;
    else 
    {
        if (strcmp(str,"[]") == 0 && followers != 0) r=1;
        else 
        {
           int i;

           for(i=0; str[i]!='\0'; i++) 
           {
               if(str[i] == ',') count++;
           }
           count++;
           
           if(followers==count) r = 0;
           else r=1;
        }
    }

    return r;
}

/**
  * @brief Função que testa se a lista dos Following está correta.
  * 
  * @param users Usuário da linha que está a ser testada.
  *
  * @param str Parâmetro (no tipo string) a ser testado.
  *
  * @return Retorna 0 se o parâmetro estiver correto e 1 se não tiver.
  */
int testFollowingList(USERS users, char *str)
{
    int r;
    int count=0;
    int following = atol(users->following);

    if (str[0] != '[') r = 1;
    else if (strcmp(str,"[]") == 0 && following == 0) r = 0;
    else 
    {
        if (strcmp(str,"[]") == 0 && following != 0) r=1;
        else 
        {
           int i;

           for(i=0; str[i]!='\0'; i++) 
           {
               if(str[i] == ',') count++;
           }
           count++;
           
           if(following==count) r = 0;
           else r=1;
        }
    }

    return r;
}

/**
  * @brief Função que testa se o parâmetro recebido tem o tipo correto.
  * 
  * @param str Parâmetro (no tipo string) a ser testado.
  *
  * @return Retorna 0 se o parametro estiver correto e 1 se não tiver.
  */
int testType(char *str)
{
    int r;

    if(strcmp(str, "Bot") == 0 || strcmp(str, "Organization")==0 || strcmp(str,"User")==0) r=0;
    else r=1;

    return r;
}

/**
  * @brief Função que filtra os repositórios do ficheiro "users.csv".
  * 
  * @param file Ficheiro "users.csv".
  *
  * @param usersList Struct que armazena os usuários corretos.
  * 
  * @param head Apontador para a cabeça da struct usersList.
  *
  * @param headline Headline do documento "users.csv".
  */
void handle_UsersFile(FILE *file, USERS usersList, USERS head, char *headline)
{
    char c[524288]; //2^19
    char *aux = NULL;
    int i=0;

    while(fgets(c, 524288, file) != NULL)
    {
        int flag = 0;
        char *str = strdup (c);
        char *line = strdup (c);
        usersList->line = line;
        aux = strsep(&str, ";\n\r");
        while (aux != NULL && flag == 0)
        {
            switch (i)
            {
            case 0:
                flag = testInt(strdup(aux));
                usersList->id = aux;
                break;
            case 1:
                flag = testString(strdup(aux));
                usersList->login = aux;
                break;
            case 2:
                flag = testType(strdup(aux));
                usersList->type = aux;
                break;
            case 3:
                flag = testDateHour(strdup(aux));
                usersList->created_at = aux;
                break;
            case 4:
                flag = testInt(strdup(aux));
                usersList->followers = aux;
                break;
            case 5:
                flag = testFollowersList(usersList, strdup(aux));
                usersList->followers_list = aux;
                break;
            case 6:
                flag = testInt(strdup(aux));
                usersList->following = aux;
                break;
            case 7:
                flag = testFollowingList(usersList, strdup(aux));
                usersList->following_list = aux;
                break;
            case 8:
                flag = testInt(strdup(aux));
                usersList->public_gists = aux;
                break;
            case 9:
                flag = testInt(strdup(aux));
                usersList->public_repos = aux;
                break;
            default:
                break;
            }
            i++;

            if(i == 10 && flag == 0)
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
    
    fclose(file);

    FILE *final_file = fopen("./saida/users-ok.csv", "w");
    printUsersFile(final_file, head, headline);
    fclose(final_file);
}