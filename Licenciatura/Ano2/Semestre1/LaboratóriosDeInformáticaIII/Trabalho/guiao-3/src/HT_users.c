/**
 * @file Ficheiro com modularidade e encapsulamento referente à Hashtable dos users
 */
#include "HT_users.h"
#include "auxiliarFunc.h"
#include "auxiliarStruct.h"
#include "auxiliarTree.h"

/**
 * @brief Definição dos elementos da Hashtable dos users
 */
struct HashTableUser
{
    /** string com o ID do utilizador */
    char *id;
    /** string com o username de login do utilizador */
    char *login;
    /** string com o tipo de utilizador */
    char *type;
    /** string com o número de seguidores */
    char *followers;
    /** string com a lista de seguidores */
    char *followers_list;
    /** string com o número de pessoas a seguir */
    char *following;
    /** string com a lista de pessoas a seguir */
    char *following_list;
    /** inteiro que conta o número de ocorrências de uma determinada informação */
    int auxCount;
    /** apontador para o próximo nodo da lista ligada da Hashtable */
    struct HashTableUser *next;
};

/**
 * @brief Função que inicializa a Hashtable dos users
 * 
 * @param hash Hashtable dos users
 */
void init_HashTableUsers(HT_Users *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
        hash[i] = NULL; 
}

/**
 * @brief Função que imprime no terminal a Hashtable dos users
 * 
 * @param hash Hashtable dos users
 */
void print_tableUsers(HT_Users *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(hash[i] == NULL){
            printf("\t%d\t---\n", i);
        } else {
            printf("\t%d\t ", i);
            HT_Users aux = hash[i];
            while (aux != NULL)
            {
                printf(" %s - %d - ", aux->id, aux->auxCount);
                aux = aux->next;
            }
            printf("\n");
        }
    }
}

/**
 * @brief Função que insere elementos na Hashtable dos users
 * 
 * @param hash Hashtable dos users
 * 
 * @param node Nodo a inserir na Hashtable
 * 
 * @return Retorna 1 quando o nodo é bem inserido
 */
int insert_HashTableUsers(HT_Users *hash, HT_Users node)
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
 * @param hash Hashtable dos users
 * 
 * @param id string com o ID a encontrar
 * 
 * @return Retorna o endereço do nodo
 */
HT_Users find_HashTableUsers(HT_Users *hash, char *id)
{
    int key = hash_key(id);
    HT_Users aux = hash[key];
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
int find_HashTableUsersBool(HT_Users *hash, char *id)
{
    int key = hash_key(id);
    HT_Users aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return 0;
    return 1;
}

/**
 * @brief Função que incrementa o valor do contador de ocorrências de um nodo da Hashtable dos users
 * 
 * @param hash Hashtable dos users
 * 
 * @param id String que contém o ID do auxCount do usuário a incrementar
 */
void incrementAuxCount (HT_Users *hash, char *id)
{
    int key = hash_key(id);
    HT_Users aux = hash[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL) {
        aux->auxCount++;
    }
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
HT_Users find_HashTableUsersKey(HT_Users *hash, int key)
{
    HT_Users aux = listU(hash[key]);

    return aux;
}

/**
 * @brief Função que permite obter o próximo elemento da lista ligada da Hashtable
 * 
 * @param user Lista ligada da Hashtable
 * 
 * @return Retorna o endereço do nodo seguinte
 */
HT_Users obtain_nextUser(HT_Users user)
{
    user = user->next;

    return user;
}

/**
 * @brief Função que permite obter o tipo de utilizador 
 * 
 * @param user Lista ligada da Hashtable
 * 
 * @return Retorna uma cópia da string com o tipo de utilizador
 */
char *obtain_userType(HT_Users user)
{
    return strdup(user->type);
}

/**
 * @brief Função que permite obter o ID do utilizador 
 * 
 * @param user Lista ligada da Hashtable
 * 
 * @return Retorna uma cópia da string com o ID de utilizador
 */
char *obtain_userId(HT_Users user)
{
    return strdup(user->id);
}

/**
 * @brief Função que permite obter o login de utilizador 
 * 
 * @param user Lista ligada da Hashtable
 * 
 * @return Retorna uma cópia da string com o login de utilizador
 */
char *obtain_userLogin(HT_Users user)
{
    return strdup(user->login);
}

/**
 * @brief Função que permite obter o campo auxCount do utilizador
 * 
 * @param user Lista ligada da Hashtable
 * 
 * @return Retorna o valor do auxCount do utilizador
 */
int obtain_userAuxCount(HT_Users user)
{
    return (user->auxCount);
}

/**
 * @brief Função que permite copiar a informação de um nodo para outro
 * 
 * @param users Nodo a copiar
 * 
 * @return Retorna o novo nodo
 */
HT_Users listU(HT_Users users)
{
    if(users==NULL) return NULL;
    HT_Users targetList = malloc(sizeof(struct HashTableUser));
    targetList->id = strdup(users->id);
    targetList->login = strdup(users->login);
    targetList->type = strdup(users->type);
    targetList->followers = strdup(users->followers);
    targetList->followers_list = strdup(users->followers_list);
    targetList->following = strdup(users->following);
    targetList->following_list = strdup(users->following_list);
    targetList->auxCount = users->auxCount;
    targetList->next = listU(users->next);
    return targetList;
}

/**
 * @brief Função que permite fazer a verificação do ficheiros dos users e a criação do catálogo
 * 
 * @param file Ficheiro a verificar e guardar
 * 
 * @param users Hashtable dos users para fazer a verificação
 */
void handle_UsersFile(FILE* file, HT_Users *users)
{
    init_HashTableUsers(users);
    char c[524288]; //2^19
    char *aux = NULL;

    while(fgets(c, 524288, file) != NULL)
    {
        HT_Users tmp = malloc(sizeof(struct HashTableUser));
        int flag = 0;
        char *str = strdup (c);
        aux = strsep(&str, ";\n\r");

        if(aux!=NULL){
        flag += testInt(aux);
        tmp->id = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testString(aux);
        tmp->login = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++; 

        if(aux!=NULL){
        flag += testType(aux);
        tmp->type = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += isValidDate(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testInt(aux);
        tmp->followers = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testFollowersList(tmp->followers, aux);
        tmp->followers_list = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testInt(aux);
        tmp->following = strdup(aux);
        aux = strsep(&str, ";\n\r");
        } else flag++;

        if(aux!=NULL){
        flag += testFollowingList(tmp->following, aux);
        tmp->following_list = strdup(aux);
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
        {
            tmp->auxCount = 0;
            insert_HashTableUsers(users, tmp);
        }
    }
}

/**
 * @brief Função que permite o reset do campo auxCount
 * 
 * @param hash Hashtable dos users
 */
void resetUsersCounter(HT_Users *hash)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        
        HT_Users aux = hash[i];
        while (aux != NULL)
            {
                aux->auxCount = 0;
                aux = aux->next;
            }
    }
}

/**
 * @brief Função que permite obter o número de seguidores de um utilizador em específico
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID do utilizador
 * 
 * @return Retorna uma cópia da string com o número de seguidores
 */
char *find_userFollowers(HT_Users *users, char *id)
{
    int key = hash_key(id);
    HT_Users aux = users[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->followers);
    return NULL;

}

/**
 * @brief Função que permite obter o número de pessoas a seguir de um utilizador em específico
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID do utilizador
 * 
 * @return Retorna uma cópia da string com o número de pessoas a seguir
 */
char *find_userFollowing(HT_Users *users, char *id)
{
    int key = hash_key(id);
    HT_Users aux = users[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->following);
    return NULL;
}

/**
 * @brief Função que permite obter a lista de seguidores de um usuário em específico
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID de utilizador
 * 
 * @return Retorna uma cópia da string com a lista de seguidores
 */
char *find_userFollowersList(HT_Users *users, char *id)
{
    int key = hash_key(id);
    HT_Users aux = users[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->followers_list);
    return NULL;
}

/**
 * @brief Função que permite obter a lista de pessoas a seguir de um usuário em específico
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID de utilizador
 * 
 * @return Retorna uma cópia da string com a lista de pessoas a seguir
 */
char *find_userFollowingList(HT_Users *users, char *id)
{
    int key = hash_key(id);
    HT_Users aux = users[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->following_list);
    return NULL;
}

/**
 * @brief Função que permite obter o login de um utilizador em específico
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID de utilizador
 * 
 * @return Retorna uma cópia da string com o login do utilizador
 */
char *find_userLogin(HT_Users *users, char *id)
{
    int key = hash_key(id);
    HT_Users aux = users[key];
    while (aux != NULL && strcmp(aux->id, id) != 0)
        aux = aux->next;
    if(aux!=NULL)
        return strdup(aux->login);
    return NULL;
}

/**
 * @brief Função que conta o número de utilizadores do tipo Bot
 * 
 * @param users Hashtable dos users
 * 
 * @return Retorna o número de utilizadores do tipo Bot
 */
int countTypeBots(HT_Users *users)
{
    int counter = 0;

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        while(aux != NULL)
        {
            char *type = aux->type;

            if(strcmp("Bot",type)==0) counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que conta o número de utilizadores do tipo Organization
 * 
 * @param users Hashtable dos users
 * 
 * @return Retorna o número de utilizadores do tipo Organization
 */
int countTypeOrganizations(HT_Users *users)
{
    int counter = 0;

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        while(aux != NULL)
        {
            char *type = aux->type;

            if(strcmp("Organization",type)==0) counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que conta o número de utilizadores do tipo User
 * 
 * @param users Hashtable dos users
 * 
 * @return Retorna o número de utilizadores do tipo User
 */
int countTypeUsers(HT_Users *users)
{
    int counter = 0;

    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        while(aux != NULL)
        {
            char *type = aux->type;

            if(strcmp("User",type)==0) counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que guarda numa árvore binária os ID's dos utilizadores do tipo Bot
 * 
 * @param users Hashtable dos users
 * 
 * @param bots Árvore onde irão ser guardados os ID's
 * 
 * @return Retorna a árvore com a informação pretendida
 */
TREE countBotsTree(HT_Users *users, TREE bots)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        while (aux != NULL)
        {
            char *type = aux->type;
            char *idUser = aux->id;
            int id = atoi(idUser);
            if(strcmp(type, "Bot") == 0)
            {
                bots = insert(bots, id);
            }

            //free(type);
            //free(idUser);

            aux = aux->next;
        }
    }
    
    return bots;
}

/**
 * @brief Função que cria uma árvore com os amigos de um determinado user.
 * 
 * @param users Hashtable dos users
 * 
 * @param id String com o ID do utilizador
 * 
 * @param k Flag para o caso de o número de followers ou following ser 0
 *
 * @return Retorna a árvore dos amigos.
 */
TREE friendsTree(HT_Users *users, char *id, int *k)
{
    char *followersList = find_userFollowers(users, id);
    int followers = atoi(followersList);
    char *followingList = find_userFollowing(users, id);
    int following = atoi(followingList);

    TREE followersTree = NULL;
    TREE friendsTree = NULL;

    if(followers == 0 || following == 0) (*k) = 0;
    else {
            //followersTree = NULL;
            int i;
            char *aux = find_userFollowersList(users, id);
            char *followersList = aux + 1;
            for(i = 0; i < followers; i++) {
                char *aux2 = strsep(&followersList, ",]\n");
                int l = atoi(aux2);
                followersTree = insert(followersTree,l);
            }

            //friendsTree = NULL;
            *k = 0;
            char *aux3 = find_userFollowingList(users, id);
            char *followingList = aux3 + 1;
            for(i = 0; i < following; i++) {
                char *aux4 = strsep(&followingList, ",]\n");
                int t = atoi(aux4);
                int flag = search(followersTree,t);
                if(flag == 1) {
                    friendsTree = insert(friendsTree,t);
                    (*k)++;
                }
            }
    }

    return friendsTree;
}

/**
 * @brief Função que conta o número de utilizadores existentes no catálogo
 * 
 * @param users Hashtable de users
 * 
 * @return Retorna o número de utilizadores existentes
 */
float countUsers(HT_Users *users)
{
    float counter = 0;

    for (int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        while(aux != NULL)
        {
            counter++;

            aux = aux->next;
        }
    }

    return counter;
}

/**
 * @brief Função que guarda num array de topUsersStruct os top N utilizadores mais ativos(mais commits)
 * 
 * @param users Hashtable dos users
 * 
 * @param topUsers Array de topUsersStruct onde irá ser guardada a informação
 * 
 * @param N Tamanho do array/Top N utilizadores mais ativos
 * 
 * @return Retorna o array com a informação guardada
 */
TOPUSERSSTRUCT activeUsers(HT_Users *users, TOPUSERSSTRUCT topUsers, int N)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];

        int flag = 0;

        while(aux != NULL)
        {
            int count = aux->auxCount;
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
                    
                    char *a = aux->id;
                    char *b = aux->login;
                    topUsersSave (topUsers, k, a, b, count);
                    flag++;
                }

            aux = aux->next;
        }
    }
    
    return topUsers;
}

/**
 * @brief Função que liberta a memória ocupada pela Hashtable dos users
 * 
 * @param users Hashtable dos users
 */
void free_TableUsers(HT_Users *users)
{
    for(int i=0; i < TABLE_SIZE; i++)
    {
        HT_Users aux = users[i];
        HT_Users prev = NULL;

        while(aux!=NULL)
        {
            prev = aux;
            free(aux->id);
            free(aux->login);
            free(aux->type);
            free(aux->followers);
            free(aux->followers_list);
            free(aux->following);
            free(aux->following_list);
            free(prev);
            aux = aux->next;
        }
    }
}