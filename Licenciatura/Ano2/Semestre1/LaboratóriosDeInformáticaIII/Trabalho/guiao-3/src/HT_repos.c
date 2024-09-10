/**
 * @file Ficheiro com modularidade e encapsulamento referente à Hashtable dos repositórios
 */
#include "HT_repos.h"
#include "auxiliarFunc.h"
#include "auxiliarStruct.h"

/**
 * @brief Definição dos elementos da Hashtable dos repositórios
 */
struct HashTableRepos
{
    /** string com o ID do repositório */
    char *id;
    /** string com o ID do owner do repositório */
    char *owner_id;
    /** string com a descrição do repositório */
    char *description;
    /** string com a linguagem de programação utilizada no repositório */
    char *language;
    /** string com a data de criação do repositório */
    char *created_at;
    /** string com a mais recente data de atualização do repositório */
    char *updated_at;
    /** apontador para o próximo nodo da lista ligada da Hashtable */
    struct HashTableRepos *next;
};

/**
 * @brief Função que inicializa a Hashtable dos repositórios
 * 
 * @param hash Hashtable dos repositórios
 */
void init_HashTableRepos(HT_Repos *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash[i] = NULL; 
}

/**
 * @brief Função que imprime no terminal a Hashtable dos repositórios
 * 
 * @param hash Hashtable dos repositórios
 */
void print_tableRepos(HT_Repos *hash)
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
            HT_Repos aux = hash[i];
            while (aux != NULL)
            {
                printf(" %s - ", aux->id);
                aux = aux->next;
            }
            printf("\n");
        }
    }
}

/**
 * @brief Função que insere elementos na Hashtable dos repositórios
 * 
 * @param hash Hashtable dos repositórios
 * 
 * @param node Nodo a inserir na Hashtable
 * 
 * @return Retorna 1 quando o nodo é bem inserido
 */
int insert_HashTableRepos(HT_Repos *hash, HT_Repos node)
{
    if(hash == NULL) return 0;
    int key = hash_key(strdup(node->id));
    node->next = hash[key];
    hash[key] = node;
    return 1;
}

/**
 * @brief Função que encontra o endereço de um determinado elemento da Hashtable
 * 
 * @param hash Hashtable dos repositórios
 * 
 * @param id string com o ID a encontrar
 * 
 * @return Retorna o endereço do nodo
 */
HT_Repos find_HashTableRepos(HT_Repos *hash, char *id)
{
    int key = hash_key(id);
    HT_Repos aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    return aux;
}

/**
 * @brief Função que permite saber se o ID se encontra na Hashtable
 * 
 * @param hash Lista ligada da Hashtable
 * 
 * @param id String com o ID a encontrar
 * 
 * @return Retorna 0 se encontrar
 */
int find_HashTableReposBool(HT_Repos *hash, char *id)
{
    int key = hash_key(id);
    HT_Repos aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return 0;
    return 1;
}

/**
 * @brief Função que encontra um nodo copiado de um determinado elemento na Hashtable
 * 
 * @param hash Hashtable dos repositórios
 *
 * @param key Índice do elemento a encontrar
 * 
 * @return Retorna o endereço do nodo
 */
HT_Repos find_HashTableReposKey(HT_Repos *hash, int key)
{
    HT_Repos aux = listR(hash[key]);

    return aux;
}

/**
 * @brief Função que permite obter a linguagem do repositório do nodo apontado
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @return Retorna a string com a linguagem do repositório
 */
char *obtain_reposLang(HT_Repos repos)
{
    return strdup(repos->language);
}

/**
 * @brief Função que permite obter a data de atualização do repositório do nodo apontado
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @return Retorna a string com a data de atualização do repositório
 */
char *obtain_reposDate(HT_Repos repos)
{
    return strdup(repos->updated_at);
}

/**
 * @brief Função que permite obter o ID do repositório do nodo apontado
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @return Retorna a string com o ID do repositório
 */
char *obtain_reposId(HT_Repos repos)
{
    return strdup(repos->id);
}

/**
 * @brief Função que permite obter a descrição do repositório do nodo apontado
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @return Retorna uma cópia da string com a descrição do repositório
 */
char *obtain_reposDescription(HT_Repos repos)
{
    return strdup(repos->description);
}

/**
 * @brief Função que permite obter o próximo elemento da lista ligada da Hashtable
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @return Retorna o endereço do nodo seguinte
 */
HT_Repos obtain_nextRepos(HT_Repos repos)
{
    repos = repos->next;

    return repos;
}

/**
 * @brief Função que permite eliminar um nodo da Hashtable dos repositórios
 * 
 * @param repos Lista ligada da Hashtable
 * 
 * @param id String com o ID do nodo a eliminar
 */
void delete_tableRepos(HT_Repos *hash, char *id)
{
    int key = hash_key(id);
    HT_Repos aux = hash[key];
    HT_Repos prev = NULL;
    while (aux != NULL && strcmp(aux->id, id) != 0){
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
 * @param repos Nodo a copiar
 * 
 * @return Retorna o novo nodo
 */
HT_Repos listR(HT_Repos repos)
{
    if(repos==NULL) return NULL;
    HT_Repos targetList = malloc(sizeof(struct HashTableRepos));
    targetList->id = strdup(repos->id);
    targetList->language = strdup(repos->language);
    targetList->owner_id = strdup(repos->owner_id);
    targetList->updated_at = strdup(repos->updated_at);
    targetList->created_at = strdup(repos->created_at);
    targetList->description = strdup(repos->description);
    targetList->next = listR(repos->next);
    return targetList;
}

/**
 * @brief Função que permite saber se o repositório apresenta a linguagem dada
 * 
 * @param hash Lista ligada da Hashtable
 * 
 * @param id String com o ID do repositório
 * 
 * @param lang String com a linguagem a procurar
 * 
 * @return Retorna 0 se encontrar
 */
int find_reposLanguageBOOL(HT_Repos *hash, char *id, char *lang)
{
    int key = hash_key(id);
    HT_Repos aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        if (strcasecmp(aux->language,lang)==0)
            return 1;
    return 0;
}

/**
 * @brief Função que permite fazer a verificação do ficheiros dos repositórios e a criação do catálogo
 * 
 * @param file Ficheiro a verificar e guardar
 * 
 * @param repos Hashtable onde irá ser guardada a informação
 * 
 * @param users Hashtable dos users para fazer a verificação
 */
void handle_ReposFile(FILE* file, HT_Repos *repos, HT_Users *users)
{
    init_HashTableRepos(repos);
    char c[1000000];
    char *aux = NULL;

    while(fgets(c, 1000000, file) != NULL)
    {
        HT_Repos tmp = malloc(sizeof(struct HashTableRepos));
        int flag = 0;
        char *str = strdup (c);
        aux = strsep(&str, ";\n\r");
       
        if(aux!=NULL){
        flag += testInt(aux);
        tmp->id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        flag += testInt(aux);
        flag += find_HashTableUsersBool(users, aux);
        tmp->owner_id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        flag += testString(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        flag += testString(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        flag += testBool(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(aux!=NULL){
        tmp->description = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testString(aux);
        tmp->language = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testString(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += isValidDate(aux);
        tmp->created_at = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += isValidDate(aux);
        tmp->updated_at = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testInt(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testInt(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testInt(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
       
        if(aux!=NULL){
        flag += testInt(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;
        
        if(flag == 0)
            insert_HashTableRepos(repos, tmp);
    }
}

/**
 * @brief Função que retorna a descrição do repositório com o ID dado
 * 
 * @param hash Hashtable dos repositórios
 * 
 * @param id String com o ID do repositório
 * 
 * @return Retorna a string com a descrição do repositório
 */
char *find_reposDescription(HT_Repos *hash, char *id)
{
    int key = hash_key(id);
    HT_Repos aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->description);
    return NULL;
}

/**
 * @brief Função que retorna o ID do owner do repositório
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param id String com o ID do repositório
 * 
 * @return Retorna a string com o ID do owner do repositório
 */
char *find_reposOwnerId(HT_Repos *repos, char *id)
{
    int key = hash_key(id);
    HT_Repos aux = repos[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->owner_id);
    return NULL;

}


/**
 * @brief Função que filtra os repositórios com a linguagem especificada.
 * 
 * @param lang Linguagem de programação a procurar nos repositórios.
 * 
 * @param repos Catálogo de Repositórios.
 * 
 * @param tree Árvore a inserir os ID's dos repositórios com a linguagem especificada.
 * 
 * @return Árvore dos ID's dos repositórios com a linguagem especificada.
 */
TREE filterRepos_Lang(char *lang, HT_Repos *repos, TREE tree)
{
    int t = 0;
    
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = find_HashTableReposKey(repos, i);

        while(aux != NULL)
        {
            char *langRep = obtain_reposLang(aux);
            if(strcasecmp(lang, langRep) == 0)
            {
                char *idRep = obtain_reposId(aux);
                int k = atoi(idRep);
                t++;
                tree = insert(tree, k);

            }

            aux = obtain_nextRepos(aux);
        }
    }

    return tree;
}

/**
 * @brief Função que conta o número de repositórios existentes
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @return Retorna o número de repositórios
 */
float countRepos(HT_Repos *repos)
{
    float counter = 0.0;

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = repos[i];

        while(aux != NULL)
        {
            counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que conta o número de vezes que uma determinada linguagem é utilizada a partir de uma data
 * 
 * @param repos Hashtable dos repositórios
 * 
 * @param start_date String com a data de início
 * 
 * @param langTop String com a linguagem
 * 
 * @param count Variável onde será guardada o número de vezes que a linguagem é utilizada
 * @return STRING 
 */
STRING countLanguageRepos(HT_Repos *repos, char *start_date, STRING langTop, int *count)
{
    for (int i=0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = repos[i];

        while(aux != NULL)
        {
            char *date = aux->updated_at;
            if(strcmp(start_date, date) < 0)
            {
                char *lang = aux->language;
                if(strcmp(lang, "None") != 0)
                {
                    langTop = countInfoStr(langTop, lang, count);
                }
            }

            aux = aux->next;
        }
    }

    return langTop;

}

/**
 * @brief Função que liberta a memória ocupada pela Hashtable dos repositórios
 * 
 * @param repos Hashtable dos repositórios
 */
void free_TableRepos(HT_Repos *repos)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = repos[i];
        HT_Repos prev = NULL;

        while(aux!=NULL)
        {
            prev = aux;
            free(aux->id);
            free(aux->owner_id);
            free(aux->description);
            free(aux->language);
            free(aux->created_at);
            free(aux->updated_at);
            free(prev);
            aux = aux->next;
        }
    }
}