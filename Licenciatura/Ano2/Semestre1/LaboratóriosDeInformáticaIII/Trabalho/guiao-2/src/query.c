/**
  * @file Ficheiro referente ás querys.
  */
#include "query.h"

/**
 * @brief Função que faz o tratamento da query 1
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 1
 * 
 * @param users Catálogo dos Utilizadores
 */
void query1(char *n_file, USERS users)
{
    int countBot = 0;
    int countOrganization = 0;
    int countUser = 0;

    while(isEmptyUsers(users)==0) 
    {
        char *type = obtain_typeUsers(users);

        if(strcmp("Bot",type)==0) countBot++;
        if(strcmp("Organization",type)==0) countOrganization++;
        if(strcmp("User",type)==0) countUser++;

        free(type);
        users = obtain_nextUser(users);

    }

    FILE *file = fopen(n_file,"w");
    fprintf(file, "Bots = %d\nOrganizations = %d\nUsers = %d\n", countBot, countOrganization, countUser);
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 2
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 2
 * 
 * @param repos Catálogo de Repositórios
 * 
 * @param commits Catálogo de Commits
 */
void query2(char *n_file, REPOS repos, COMMITS commits)
{
    float countRepos = 0;
    TREE colabs = NULL;

    while(isEmptyRepos(repos) == 0)
    {
        countRepos++;
        repos = obtain_nextRepos(repos);
    }

    while(isEmptyCommits(commits) == 0)
    {
        char *idAuthor = obtain_commitsAuthorId(commits);
        char *idCommiter = obtain_commiterId(commits);
        if(strcmp(idAuthor, idCommiter) == 0)
        {
            int iDAuthor = atoi(idAuthor);
            int flag = search(colabs, iDAuthor);
            if(flag == 0) colabs = insert(colabs, iDAuthor);
        }
        else
        {
            int iDAuthor = atoi(idAuthor);
            int flagAuthor = search(colabs, iDAuthor);
            if(flagAuthor == 0) colabs = insert(colabs, iDAuthor);
            int iDCommiter = atoi(idCommiter);
            int flagCommiter = search(colabs, iDCommiter);
            if(flagCommiter == 0) colabs = insert(colabs, iDCommiter);
        }
        free(idAuthor);
        commits = obtain_nextCommit(commits);
    }

    float colab = countnodes(colabs);
    float avg = colab/countRepos;

    FILE *file = fopen(n_file,"w");
    fprintf(file, "%0.2f\n", avg);
    
    freeTree(colabs);
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 3
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 3
 * 
 * @param users Catálogo de Utilizadores
 * 
 * @param commits Catálogo de Commits
 */
void query3(char *n_file, USERS users, COMMITS commits)
{
    char *type = NULL;
    char *idUser = NULL;
    char *idAuthor = NULL;
    char *idCommiter = NULL;
    char *idRepo = NULL;
    TREE bots = NULL;
    TREE repos = NULL;

    while(isEmptyUsers(users) == 0)
    {
        type = obtain_typeUsers(users);
        idUser = obtain_IdUsers(users);
        int id = atoi(idUser);
        if(strcmp(type, "Bot") == 0)
        {
            bots = insert(bots, id);
        }
        free(idUser);
        users = obtain_nextUser(users);
    }

    while(isEmptyCommits(commits) == 0)
    {
        idAuthor = obtain_commitsAuthorId(commits);
        int iDAuthor = atoi(idAuthor);
        idCommiter = obtain_commiterId(commits);
        int iDCommiter = atoi(idCommiter);
        int flagAuthor = search(bots, iDAuthor);
        int flagCommiter = search(bots, iDCommiter);
        if(flagAuthor == 1 || flagCommiter == 1)
        {
            idRepo = obtain_commitsReposId(commits);
            int iDRepo = atoi(idRepo);
            repos = insert(repos, iDRepo);
        }
        free(idAuthor);
        commits = obtain_nextCommit(commits);
    }

    int count = countnodes(repos);

    FILE *file = fopen(n_file,"w");
    fprintf(file, "%d\n", count);

    free(type);
    free(idRepo);
    freeTree(bots);
    freeTree(repos);
    fclose(file);
   
}

/**
 * @brief Função que faz o tratamento da query 4
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 4
 * 
 * @param users Catálogo de Utilizadores
 * 
 * @param commits Catálogo de Commits
 */
void query4(char *n_file, USERS users, COMMITS commits)
{
    float countUsers = 0;
    float countCommits = 0;
    while(isEmptyUsers(users) == 0)
    {
        countUsers++;
        users = obtain_nextUser(users);
    }
    while(isEmptyCommits(commits) == 0)
    {
        countCommits++;
        commits = obtain_nextCommit(commits);
    }

    float avg = countCommits/countUsers;

    FILE *file = fopen(n_file,"w");
    fprintf(file, "%0.2f\n", avg);
    fclose(file);

}

/**
 * @brief Função que faz o tratamento da query 5
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 5
 * 
 * @param line Linha de comando da query 5
 * 
 * @param commits Catálogo de Commits
 * 
 * @param usersArv Árvore de Users
 */
void query5(char *n_file, char *line, COMMITS commits, TREEUSERS usersArv)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *start_date = strsep(&line, " ");
    char *end_date = strsep(&line, " ");
    COMMITS head = commits;
    TOP idTop = NULL;
    int id, counter;
    
    FILE *file = fopen(n_file,"w");

    while(isEmptyCommits(head) == 0)
    {
        char *commitId = obtain_commiterId(head);
        id = atoi(commitId);
        char *dateHour = obtain_commitsDate(head);
        char *date = strsep(&dateHour, " ");

        if(compareDates(start_date, end_date, date) == 1)
        {
            idTop = countInfo(idTop, id);
        }
        free(date);
        head = obtain_nextCommit(head);
    }

    char User[1024];

    for (int i = 0; i < N; i++)
    {
        char *login = NULL;
        mostFreq(idTop, &id, &counter);
        sprintf(User, "%d", id);
        login = searchUsers(usersArv, User);
        fprintf(file,"%d;%s;%d\n",id, login, counter);
    }      
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 6
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 6
 * 
 * @param line Linha de comando da query 6
 * 
 * @param commits Catálogo dos Commits
 * 
 * @param repos Catálogo dos Repositórios
 * 
 * @param usersArv Árvore de Users
 */
void query6(char *n_file, char *line, COMMITS commits, REPOS repos, TREEUSERS usersArv)
{
    char *N = strsep(&line, " ");
    int n = atoi(N);
    char *aux = strsep(&line, " ");
    char *lang = strsep(&aux, "\n\r");
    TREE reposIDtree = NULL;
    reposIDtree = filterRepos_Lang(lang, repos, reposIDtree);
    TOP l = NULL;
    COMMITS temp = commits;

    while(isEmptyCommits(temp)==0)
    {
        char *reposId = obtain_commitsReposId(temp);
        int a = atoi(reposId);
        free(reposId);
        int flag = search(reposIDtree,a);
        if(flag == 1) {
            char *authorId = obtain_commitsAuthorId(temp);
            int b = atoi(authorId);
            l = countInfo(l, b);
            free(authorId);
        }
        temp = obtain_nextCommit(temp);
    }

    int id;
    int counter;
    char User[1024];
    

    FILE *file = fopen(n_file,"w");

    if(l==NULL) fprintf(file, "%s", "The language doesn't exist in the repos");
    else
    {
        for (int i = 0; i < n; i++)
        {
            char *login = NULL;
            mostFreq(l, &id, &counter);
            sprintf(User, "%d", id);
            login = searchUsers(usersArv, User);
            fprintf(file,"%d;%s;%d\n",id, login, counter);
        } 
    }
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 7
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 7
 * 
 * @param line Linha de comando da query 7
 * 
 * @param repos Catálogo de Repositórios
 * 
 * @param commits Catálogo dos Commits
 * 
 * @param reposArv Árvore de Repositórios
 */
void query7(char *n_file, char *line, REPOS repos, COMMITS commits, TREEREPOS reposArv)
{
    char *aux = strsep(&line, " ");
    char *start_date = strsep(&aux, "\n");
    char *id;
    STRING repList = NULL;
    int a = 0;

    while(isEmptyCommits(commits) == 0)
    {
        char *dateHour = obtain_commitsDate(commits);
        char *date = strsep(&dateHour, " ");
        if(verifyDate(date, start_date) == 1)
        {
            id = obtain_commitsReposId(commits);    
            repList = countInfoStr(repList, id, &a);
        }
        commits = obtain_nextCommit(commits);
    }

    FILE *file = fopen(n_file,"w");

    while(isEmptyString(repList) == 0)
    {
        id = obtain_stringID(repList);
        char *message = searchRepos(reposArv, id);
        fprintf(file, "%s;%s\n", id, message);   
        repList = obtain_nextString(repList);
    }        
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 8
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 8
 * 
 * @param line Linha de comando da query 8
 * 
 * @param repos Catálogo de Repositórios
 */
void query8(char *n_file, char *line, REPOS repos)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char *aux = strsep(&line, " ");
    char *start_date = strsep(&aux, "\n");
    STRING langTop = NULL;
    int a = 0;

    while(isEmptyRepos(repos) == 0)
    {
        char *date = obtain_reposDate(repos);
        
        if(strcmp(start_date, date) < 0)
        {
            char *lang = obtain_langRepos(repos);
            if(strcmp(lang,"None") != 0)
            {
                langTop = countInfoStr(langTop, lang, &a);
            }
        }
        repos = obtain_nextRepos(repos);
    }

    char * langFinal = NULL;

    FILE *file = fopen(n_file, "w");

    for(int i=0; i < N; i++)
    {
        langFinal = mostFreqString(langTop);
        if(i!=N)
        {
            fprintf(file,"%s\n",langFinal);   
        }
    }
    freeString(langTop);
    fclose(file);
}


/**
 * @brief Função que faz o tratamento da query 9
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 9
 * 
 * @param line Linha de comando da query 9
 * 
 * @param commits Catálogo dos Commits
 * 
 * @param repos Catálogo dos Repositórios
 * 
 * @param usersArv Árvore de Users
 *
 * @param reposArv9 Árvore de Repositórios especifica para a query 9
 *
 * @param usersArv9 Árvore de Users especifica para a query 9
 */
void query9(char *n_file, char *line, COMMITS commits, REPOS repos, TREEUSERS usersArv, TREEREPOS reposArv9, TREEUSERS9 usersArv9)
{
    char *N = strsep(&line, " ");
    int n = atoi(N);
    TREE friends = NULL;
    USERS temp = NULL;
    int teste, flag;
    STRING top = NULL;
    int count = 0;

    while (isEmptyCommits(commits)==0)
    {
        flag = 0;
        char *idCommiter = obtain_commiterId(commits);
        char *repos = obtain_commitsReposId(commits);
        char *idOwner = searchRepos(reposArv9,repos);
        int IDOWNER = atoi(idOwner);
        temp = searchUsers9(usersArv9, idCommiter);
        friends = friendsTreeF(temp, &teste);
        flag = search(friends,IDOWNER);
        if (flag == 1)
            top = countInfoStr(top, idCommiter, &count);
        commits = obtain_nextCommit(commits);
    }

    char * id;

    FILE *file = fopen(n_file,"w");
    for(int i = 0; i < n && count > 1; i++)
    {
        char *login = NULL;
        id = mostFreqString(top);
        login = searchUsers(usersArv, id);
        fprintf(file,"%s;%s\n",id, login);
        count--;
    }
    fclose(file);
}

/**
 * @brief Função que faz o tratamento da query 10
 * 
 * @param n_file Ficheiro onde irá guardar as informações pedidas na query 10
 * 
 * @param line Linha de comando da query 10
 * 
 * @param commits Catálogo de Commits
 * 
 * @param usersArv Árvore de Users
 */
void query10(char *n_file, char *line, COMMITS commits, TREEUSERS usersArv)
{
    char *n = strsep(&line, " ");
    int N = atoi(n);
    char * idCommiter;
    int counter;
    TOP messList = NULL;

    while(isEmptyCommits(commits) == 0)
    {
        idCommiter = obtain_commiterId(commits);
        int id = atoi(idCommiter);
        char *message = obtain_messageCommit(commits);
        counter = utf8_strlen(message);
        messList = countInfoLen(messList, id, counter);

        free(message);
        commits = obtain_nextCommit(commits);
    }

    int id;
    int count;
    char User[1024];

    FILE *file = fopen(n_file, "w");

    for(int i=0; i < N; i++)
    {
        char *login = NULL;
        mostFreq(messList, &id, &count);
        sprintf(User, "%d", id);
        login = searchUsers(usersArv, User);
        fprintf(file,"%d;%s;%d\n",id, login, count);
    }
    freeTop(messList);
    fclose(file);
}

/**
 * @brief Função que faz o tratamento das diferentes queries, através das linhas do ficheiro de comandos
 * 
 * @param i Número que determina a ordem e o nome dos ficheiros finais
 * 
 * @param id Número de dentificação da query
 * 
 * @param line Linha de comando da query
 * 
 * @param users Catálogo dos Utilizadores
 * 
 * @param commits Catálogo dos Commits
 * 
 * @param repos Catálogo dos Repositórios
 * 
 * @param usersArv Árvore de Users
 * 
 * @param reposArv Árvore de Repositórios
 * 
 * @param usersArv9 Árvore de Users especifica para a query 9
 * 
 * @param reposArv9 Árvore de Repositórios especifica para a query 9
 */
void queryID(int i, int id, char *line, USERS users, COMMITS commits, REPOS repos, TREEUSERS usersArv, TREEREPOS reposArv, TREEUSERS9 usersArv9, TREEREPOS reposArv9)
{
    char fileName[1024];
    sprintf(fileName, "./saida/command%d_output.txt", i);
    switch (id)
    {
    case 1:
        query1(fileName, users);
        break;
    case 2:
        query2(fileName, repos, commits);
        break;
    case 3:
        query3(fileName, users, commits);
        break;
    case 4:
        query4(fileName, users, commits);
        break;
    case 5:
        query5(fileName, line, commits, usersArv);
        break;
    case 6:
        query6(fileName, line, commits, repos, usersArv);
        break;
    case 7:
        query7(fileName, line, repos, commits, reposArv);
        break;
    case 8:
        query8(fileName, line, repos);
        break;
    case 9:
        query9(fileName, line, commits, repos, usersArv, reposArv9, usersArv9);
        break;
    case 10:
        query10(fileName, line, commits, usersArv);
        break;
    default:
        break;
    }
}

