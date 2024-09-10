/**
 * @file Ficheiro com modularidade e encapsulamento referente à função main dos testes
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
 * @brief Imprime os resultados no terminal
 * 
 * @param id Id da query
 * @param flag Bool da função compare
 * @param time_passed Tempo em que a query executou
 */
void printTest(int id, int flag, double time_passed)
{
    char *c = NULL;
    if(flag == 1) c = strdup("A query produziu resultados diferentes do esperado!");
    else c = strdup("A query produziu resultados esperados!");
    printf("\n|-------------------------------------------------------------------------------|");
    printf("\n|                                 Query %d                                       ", id);
    printf("\n|     Time:        %f     segundos                                               ", time_passed);
    printf("\n|     Resultado:   %s                                                            ", c);
    printf("\n|-------------------------------------------------------------------------------|\n");
}

/**
 * @brief Função que verifica se os ficheiros são iguais
 * 
 * @param i Refere-se ao número do arquivo
 *  
 * @return 1 caso sejam diferentes e 0 caso contrário 
 */
int compare(int i)
{
    int flag = 1;
    int status = 0;
    status = status;
    int count = 0;
    char command[1024];
    sprintf(command,"diff -c ./src/tests/entrada/testExpected%d_output.txt ./src/tests/saida/test%d_output.txt > ./src/tests/saida/diff%d.txt", i, i, i);
    status = system(command);
    char testediff[50];
    sprintf(testediff,"./src/tests/saida/diff%d.txt", i);
    FILE *diff = fopen(testediff,"r");
    char c[5242];
    while(fgets(c, 5242, diff)!=NULL) count++;
    if(count==0) flag = 0;
    fclose(diff);
    return flag;
}

/**
 * @brief Função que trata do fluxo de ação das queries e do calculo do seu tempo de execução
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
void test(int i, int id, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos)
{
    int flag = 0;
    clock_t start, end;
    double time_passed = 0.0;

    char fileName[1024];
    sprintf(fileName, "./src/tests/saida/test%d_output.txt", i);
    
    switch(id)
    {
        case 1:
            start = clock();
            query1(fileName, users);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 2:
            start = clock();
            query2(fileName, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
         case 3:
            start = clock();
            query3(fileName, users, commits);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 4:
            start = clock();
            query4(fileName, users, commits);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 5:
            start = clock();
            query5(fileName, line, commits, users);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 6:
            start = clock();
            query6(fileName, line, users, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 7:
            start = clock();
            query7(fileName, line, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 8:
            start = clock();
            query8(fileName, line, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 9:
            start = clock();
            query9(fileName, line, users, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 10:
            start = clock();
            query10(fileName, line, users, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        case 11:
            start = clock();
            query11(fileName, line, users, commits, repos);
            end = clock();
            time_passed += (double) (end-start) / CLOCKS_PER_SEC;
            flag = compare(i);
            printTest(id, flag, time_passed);
            break;
        default:
            break;
    }
}

/**
 * @brief Função que controla o fluxo da execução do testes
 * 
 * @param argc Argumento a introduzir na linha de comandos
 * 
 * @param argv Array do número de argumentos a introduzir na linha de argumentos
 * 
 * @return Retorna 0
 */
int main(int argc, char const *argv[])
{
    char c[10240];

    FILE *users_file = fopen("./entrada/test_users.csv", "r");
    check_File(users_file);
    fgets(c, 524288, users_file);
    HT_Users users[TABLE_SIZE];
    handle_UsersFile(users_file, users);
    fclose(users_file);
    //print_tableUsers(users);

    FILE *commits_file = fopen("./entrada/test_commits.csv", "r");
    check_File(commits_file);
    fgets(c, 524288, commits_file);
    HT_Commits commits[TABLE_SIZE];
    handle_CommitsFile(commits_file, commits, users);
    fclose(commits_file);
    //print_tableCommits(commits);

    FILE *repos_file = fopen("./entrada/test_repos.csv", "r");
    check_File(repos_file);
    fgets(c, 524288, repos_file);
    HT_Repos repos[TABLE_SIZE];
    handle_ReposFile(repos_file, repos, users);
    fclose(repos_file);
    //print_tableRepos(repos);

    filterCommits(commits, repos);
    filterRepos(commits, repos);

    FILE *commands = fopen(argv[1], "r");
    check_File(commands);
    int i=1;


    while (fgets(c, 524288, commands) != NULL)
    {
        char *line = strdup(c);
        char *aux = strsep(&line, " ");
        int id = atol(aux);

        test(i,id, line, users, commits, repos);

        if(id == 5) resetUsersCounter(users);
        if(id == 6) resetUsersCounter(users);

        i++;
    }
    fclose(commands);
    
    //free_TableUsers(users);
    //free_TableCommits(commits);
    //free_TableRepos(repos);
    
    return 0;
}