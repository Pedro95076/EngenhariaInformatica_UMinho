/**
 * @file Ficheiro com modularidade e encapsulamento referente à Hashtable dos commits 
 */
#include "HT_commits.h"
#include "HT_users.h"
#include "auxiliarFunc.h"
#include "auxiliarTree.h"

/**
 * @brief Definição dos elementos da Hashtable dos commits
 */
struct HashTableCommits
{
    /** string com o ID do repositório */
    char *repo_id;
    /** string com o ID do autor do commit */
    char *author_id;
    /** string com o ID da pessoa que realizou o commit */
    char *commiter_id;
    /** string com a data do commit */
    char *commit_at;
    /** inteiro com o tamanho da mensagem do commit */
    int message;
    /** apontador para o próximo nodo da lista ligada da Hashtable */
    struct HashTableCommits *next;
};

/**
 * @brief Função que inicializa a Hashtable dos commits
 * 
 * @param hash Hashtable dos commits
 */
void init_HashTableCommits(HT_Commits *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash[i] = NULL; 
}

/**
 * @brief Função que imprime no terminal a Hashtable dos commits
 * 
 * @param hash Hashtable dos commits
 */
void print_tableCommits(HT_Commits *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash[i] == NULL)
        {
            printf("\t%d\t---\n", i);
        } 
        else 
        {
            printf("\t%d\t ", i);
            HT_Commits aux = hash[i];
            while (aux != NULL)
            {
                printf(" %s - ", aux->repo_id);
                aux = aux->next;
            }
            printf("\n");
        }
    }
}

/**
 * @brief Função que insere elementos na Hashtable dos Commits
 * 
 * @param hash Hashtable dos commits
 * 
 * @param node Nodo a inserir na Hashtable
 * 
 * @return Retorna 1 quando o nodo é bem inserido
 */
int insert_HashTableCommits(HT_Commits *hash, HT_Commits node)
{
    if(hash == NULL) return 0;
    int key = hash_key(strdup(node->repo_id));
    node->next = hash[key];
    hash[key] = node;
    return 1;
}

/**
 * @brief Função que encontra o endereço de um determinado elemento da Hashtable
 * 
 * @param hash Hashtable dos commits
 * 
 * @param id string com o ID a encontrar
 * 
 * @return Retorna o endereço do nodo
 */
HT_Commits find_HashTableCommits(HT_Commits *hash, char *id)
{
    int key = hash_key(id);
    HT_Commits aux = hash[key];
    while (aux != NULL && strcmp(aux->repo_id, id) != 0)
        aux = aux->next;
    return aux;
}

/**
 * @brief Função que encontra um nodo copiado de um determinado elemento na Hashtable
 * 
 * @param hash Hashtable dos commits
 * 
 * @param key Índice do elemento a encontrar
 * 
 * @return Retorna o endereço do nodo
 */
HT_Commits find_HashTableCommitsKey(HT_Commits *hash, int key)
{
    HT_Commits aux = listC(hash[key]);

    return aux;
}

/**
 * @brief Função que permite obter o próximo elemento da lista ligada da Hashtable
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @return Retorna o endereço do nodo seguinte
 */
HT_Commits obtain_nextCommit(HT_Commits commits)
{
    commits = commits->next;

    return commits;
}

/**
 * @brief Função que permite obter o ID do autor do commit do nodo apontado
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @return Retorna a string com o ID do autor
 */
char *obtain_commitsAuthorId(HT_Commits commits)
{
    return strdup(commits->author_id);
}

/**
 * @brief Função que permite obter o ID do commiter do commit do nodo apontado
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @return Retorna a string com o ID do commiter
 */
char *obtain_commitsCommiterId(HT_Commits commits)
{
    return strdup(commits->commiter_id);
}

/**
 * @brief Função que permite obter o ID do repositório do commit do nodo apontado
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @return Retorna a string com o ID do repositório
 */
char *obtain_commitsReposId(HT_Commits commits)
{
    return strdup(commits->repo_id);
}

/**
 * @brief Função que permite obter a data do commit apontado
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @return Retorna a string com a data do commit
 */
char *obtain_commitsDate(HT_Commits commits)
{
    return strdup(commits->commit_at);
}

/**
 * @brief Função que permite saber se o ID se encontra na Hashtable
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @param id String com o ID a encontrar
 * 
 * @return Retorna 0 se encontrar
 */
int find_HashTableCommitsBool(HT_Commits *hash, char *id)
{
    int key = hash_key(id);
    HT_Commits aux = hash[key];
    while (aux != NULL && strcmp(aux->repo_id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return 0;
    return 1;
}

/**
 * @brief Função que permite eliminar um nodo da Hashtable dos commits
 * 
 * @param commits Lista ligada da Hashtable
 * 
 * @param id String com o ID do nodo a eliminar
 */
void delete_tableCommits(HT_Commits *hash, char *id)
{
    int key = hash_key(id);
    HT_Commits aux = hash[key];
    HT_Commits prev = NULL;
    while (aux != NULL && strcmp(aux->repo_id, id) != 0){
        prev = aux;
        aux = aux->next;
    }
    if(prev == NULL)
        hash[key] = aux->next;
    else
        prev->next = aux->next;
}

/**
 * @brief Função que permite copiar a informação de um nodo para outro
 * 
 * @param commits Nodo a copiar
 * 
 * @return Retorna o novo nodo
 */
HT_Commits listC(HT_Commits commits)
{
    if(commits==NULL) return NULL;
    HT_Commits targetList = malloc(sizeof(struct HashTableCommits));
    targetList->commiter_id = strdup(commits->commiter_id);
    targetList->repo_id = strdup(commits->repo_id);
    targetList->author_id = strdup(commits->author_id);
    targetList->commit_at = strdup(commits->commit_at);
    targetList->message = commits->message;
    targetList->next = listC(commits->next);
    return targetList;
}

/**
 * @brief Função que permite fazer a verificação do ficheiros dos commits e a criação do catálogo
 * 
 * @param file Ficheiro a verificar e guardar
 * 
 * @param commits Hashtable onde irá ser guardada a informação
 * 
 * @param users Hashtable dos users para fazer a verificação
 */
void handle_CommitsFile(FILE* file, HT_Commits *commits, HT_Users *users)
{
    init_HashTableCommits(commits);
    char c[1000000];
    char *aux = NULL;

    while(fgets(c, 1000000, file) != NULL)
    {
        HT_Commits tmp = malloc(sizeof(struct HashTableCommits));
        int flag = 0;
        char *str = strdup (c);
        aux = strsep(&str, ";\n\r");

        if(aux!=NULL){
        flag += testInt(aux);
        tmp->repo_id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        flag += testInt(aux);
        flag += find_HashTableUsersBool(users, aux);
        tmp->author_id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testInt(aux);
        flag += find_HashTableUsersBool(users, aux);
        tmp->commiter_id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += isValidDate(aux);
        tmp->commit_at = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        int l = strlen(aux);
        tmp->message = l;
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(flag == 0)
            insert_HashTableCommits(commits, tmp);
    }
}

/**
 * @brief Função que guarda o ID dos repositórios inativos a partir de uma determinada data
 * 
 * @param data Lista ligada onde irão ser guardados os ID's dos repositórios selecionados
 * 
 * @param commits Hashtable dos commits
 * 
 * @param str String com a data a partir da qual os repositórios têm de ser inativos
 * 
 * @return Lista ligada com os ID's dos repositórios respetivos
 */
DATA find_inactiveRepos(DATA data, HT_Commits *commits, char *str)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            char *dateHour = aux->commit_at;
            char *date = strsep(&dateHour, " ");
            if(verifyDate(date, str) == 1)
            {
                char *id = aux->repo_id;
                data = insertData(data, id);
            }

            aux = aux->next;
        }
    }

    return data;
}

/**
 * @brief Função que guarda numa estrutura auxiliar os ID's dos usuários que apresentam commits em repositórios de amigos e o número de commits respetivos
 * 
 * @param string Lista ligada onde irá ser guardada a informação
 * 
 * @param commits Hashtable dos commits
 * 
 * @param users Hashtable dos users
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param count Variável onde será colocado o número de usuários com amigos
 * 
 * @return Retorna a lista ligada com a informação
 */
STRING counter_AllCommiters(STRING string, HT_Commits *commits, HT_Users *users, HT_Repos *repos, int *count)
{
    
    TREE friends = NULL;
    int test, flag;

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            flag = 0;
            char *commiterId = aux->commiter_id;
            char *reposId = aux->repo_id;
            char *ownerId = find_reposOwnerId(repos, reposId);
            int ownerID = atoi(ownerId);
            friends = friendsTree(users, commiterId, &test);
            flag = search(friends, ownerID);
            if(flag == 1) 
            {
                string = countInfoStr(string, commiterId, count);
            }

            aux = aux->next;
        }
    }

    //free(friends);
    return string;

}

/**
 * @brief Função que guarda numa árvore binária os ID's dos usuários que são colaboradores
 * 
 * @param commits Hashtable dos commits
 * 
 * @param colabs Árvore onde irá ser guardada a informação
 * 
 * @return Retorna a árvore com a informação guardada
 */
TREE getAllColabs(HT_Commits *commits, TREE colabs)
{

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            char *idAuthor = aux->author_id;
            char *idCommiter = aux->commiter_id;
            if(strcmp(idAuthor, idCommiter) == 0)
            {
                int IdAuthor = atoi(idAuthor);
                int flag = search(colabs, IdAuthor);
                if(flag == 0) colabs = insert(colabs, IdAuthor);
            }
            else
            {
                int IdAuthor = atoi(idAuthor);
                int flagAuthor = search(colabs, IdAuthor);
                if(flagAuthor == 0) colabs = insert(colabs, IdAuthor);
                int IdCommiter = atoi(idCommiter);
                int flagCommiter = search(colabs, IdCommiter);
                if(flagCommiter == 0) colabs = insert(colabs, IdCommiter);
            }

            aux = aux->next;
        }
    }

    return colabs;
}

/**
 * @brief Função que conta todos os bots que são colaboradores e guarda o repositório associado aos commits
 * 
 * @param commits Hashtable dos commits
 * 
 * @param bots Árvore com os ID's dos usuários que são bots
 * 
 * @param repos Árvore onde irá ser guardado o número de repositórios
 * 
 * @return TREE 
 */
TREE countAllBotsColabs(HT_Commits *commits, TREE bots, TREE repos)
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            char *idAuthor = aux->author_id;
            int iDAuthor = atoi(idAuthor);
            char *idCommiter = aux->commiter_id;
            int iDCommiter = atoi(idCommiter);
            int flagAuthor = search(bots, iDAuthor);
            int flagCommiter = search(bots, iDCommiter);
            if(flagAuthor == 1 || flagCommiter == 1)
            {
                char *idRepo = aux->repo_id;
                int iDRepo = atoi(idRepo);
                repos = insert(repos, iDRepo);
            }

            //free(idAuthor);
            //free(idCommiter);

            aux = aux->next;
        }
    }

    return repos;
}

/**
 * @brief Função que conta o número de commits
 * 
 * @param commits Hashtable dos commits
 * 
 * @return Retorna o valor total de commits
 */
float countCommits(HT_Commits *commits)
{
    float counter = 0.0;

    for (int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que compara as datas obtidas a partir da query com a data do commit e conta o número de commits realizados
 * 
 * @param commits Hashtable dos commits
 * 
 * @param users Hashtable dos users
 * 
 * @param end_date String com a data final
 * 
 * @param start_date String com a data inicial
 */
void compareAllDates(HT_Commits *commits, HT_Users *users, char *end_date, char *start_date)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            char *commiterId = aux->commiter_id;
            char *dateHour = aux->commit_at;
            char *date = strsep(&dateHour, " ");

            if(compareDates(start_date, end_date, date) == 1)
            {
                incrementAuxCount (users, commiterId);
            }
            
            aux = aux->next;
        }
    }
}

/**
 * @brief Função que conta os commits associados a um determinado repositório filtrado através da linguagem
 * 
 * @param commits Hashtable dos commits
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param users Hashtable dos users
 * 
 * @param language String com a linguagem que filtra os repositórios
 * 
 * @param flag Flag que permite verificar se o ID do repositório corresponde ao da linguagem em questão
 */
void countCommitsReposLanguage(HT_Commits *commits, HT_Repos *repos, HT_Users *users, char *language, int flag)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        while(aux != NULL)
        {
            char *reposId = aux->repo_id;
            int flag = find_reposLanguageBOOL(repos, reposId, language);
            if(flag == 1)
            {
                char *authorId = aux->author_id;
                incrementAuxCount (users, authorId);
                flag = 0;

            }

            aux = aux->next;
        }
    }
}

/**
 * @brief Função que permite obter um top de repositórios consoante o tamanho de mensagem por repositório
 * 
 * @param repoID String com o ID do repositório
 * 
 * @param users Hashtable com os users
 * 
 * @param commits Hashtable com os commits
 * 
 * @param file Ficheiro onde irá ser imprimido o resultado da query
 * 
 * @param N Valor inteiro que indica o top N
 */
void topNrepo(char *repoID, HT_Users *users, HT_Commits *commits, FILE *file, int N)
{
    TOPUSERSSTRUCT topUsers = NULL;
    topUsers = initTopUsersStruct (N);

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];

        int flag = 0;

        while(aux != NULL)
        {
            char *repos = aux->repo_id;
            int count = aux->message;
            if(strcmp(repoID, repos) == 0)
            {
                if (count != 0) 
                {
                    int k = 0;
                    for(int i = 0; i < N; i++) 
                    {
                        int c1 = obtain_TopUsersCount (topUsers, i);
                    if(count < c1) k++;
                    }

                    if (k<N) 
                    {
                        for(int j = 0; flag-j > k; j++) 
                        {
                            int f = flag-j;
                            topUsersSort (topUsers,f);
                        }

                        char *a = aux->commiter_id;
                        char *b = find_userLogin(users,a);

                        topUsersSave (topUsers, k, a, b, count);

                        flag++;
                    }
                }
            }

            aux = aux->next;
        }
    }

    for(int i = 0; i < N; i++) 
    {
        if(isEmptyTopUsersStruct(topUsers, i) == 0)
        {
             char *auxID = obtain_TopUsersId (topUsers, i);
            char *auxLOGIN = obtain_TopUsersLogin (topUsers, i);
            int auxCOUNTER = obtain_TopUsersCount (topUsers, i);

            fprintf(file,"%s;%s;%d;%s\n", auxID, auxLOGIN, auxCOUNTER, repoID);
        }

    }
}

/**
 * @brief Função que liberta a memória ocupada pela Hashtable dos commits
 * 
 * @param commits Hashtable dos commits
 */
void free_TableCommits(HT_Commits *commits)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = commits[i];
        HT_Commits prev = NULL;

        while(aux!=NULL)
        {
            prev = aux;
            free(aux->repo_id);
            free(aux->author_id);
            free(aux->commit_at);
            free(aux->commiter_id);
            free(prev);
            aux = aux->next;
        }
    }
}