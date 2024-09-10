/**
  * @file Ficheiro com modularidade e encapsulamento referente às estruturas de árvores.
  */
#include "data_tree.h"

/**
 * @brief Definição da árvore binária.
 * 
 */
struct tree 
{
    /** inteiro que contém a informação a guardar */
	int value;
    /** apontador para os ramos direito e esquerdo da árvore */
	struct tree *l, *r;
};

/**
 * @brief Definição da árvore binária ordenada por id, com a componente login.
 * 
 */
struct treeUsers
{
    /** inteiro que contém a informação a guardar */
    char * id;
    /** inteiro que contém a informação a guardar */
    char * login;
    /** apontador para os ramos direito e esquerdo da árvore */
    struct treeUsers *l, *r;
};

struct treeUsers9
{
    /** inteiro que contém a informação a guardar */
    char * id;
    /** inteiro que contém a informação a guardar */
    struct users *node;
    /** apontador para os ramos direito e esquerdo da árvore */
    struct treeUsers9 *l, *r;
};

/**
 * @brief Definição da árvore binária ordenada por id, com a componente message.
 * 
 */
struct treeRepos
{
    /** inteiro que contém a informação a guardar */
    char * id;
    /** inteiro que contém a informação a guardar */
    char * message;
    /** apontador para os ramos direito e esquerdo da árvore */
    struct treeRepos *l, *r;
};

/**
 * @brief Função que insere os elementos na árvore binária.
 * 
 * @param tree Árvore binária onde se irá guardar o elemento.
 * 
 * @param x Elemento a guardar na árvore binária.
 * 
 * @return Retorna a árvore com o elemento inserido.
 */
TREE insert (TREE tree, int x) 
{
    TREE *place;
	place = &tree;

	while (*place != NULL)
		if (x < (*place)->value)
				 place = &((*place)->l);
		else place = &((*place)->r);

	(*place) = malloc (sizeof (struct tree));
	(*place)->value = x;
	(*place)->l = (*place)->r = NULL;

	return tree;
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
TREE filterRepos_Lang(char *lang, REPOS repos, TREE tree)
{
    int i = 0;
    REPOS temp = repos;

    while (isEmptyRepos(temp)==0)
    {
        //strcmpi para comparar com case insentitivity
        char *langRep = obtain_langRepos(temp);
        if (strcasecmp(lang,langRep)==0)
        {
            char *idRep = obtain_reposID(temp);
            int k=atoi(idRep);
            i++;
            tree = insert(tree,k);
        }
        temp = obtain_nextRepos(temp);
    }
    return tree;
}

/**
 * @brief Função que adiciona nodos a uma árvore de users.
 * 
 * @param tree Árvore a inserir os ID's dos users.
 * 
 * @param id String com o id a ser guardado.
 * 
 * @param login String com o login associado ao id.
 * 
 * @return Árvore com o user adicionado.
 */
TREEUSERS addUsersTREE(TREEUSERS tree, char *id, char *login)
{
    TREEUSERS *place;
    place = &tree;

    while (*place != NULL)
    {
        if (strcmp(id,(*place)->id) < 0)
                 place = &((*place)->l);
        else place = &((*place)->r);
    }

    (*place) = malloc (sizeof (struct treeUsers));
    (*place)->id = strdup(id);
    (*place)->login = strdup(login);
    (*place)->l = (*place)->r = NULL;

    return tree;
}

/**
 * @brief Função que inicializa a árvore de users.
 * 
 * @param users Catálogo de users.
 * 
 * @return Retorna a árvore criada apartir da lista de users.
 */
TREEUSERS iniUsersTREE(USERS users)
{
    TREEUSERS place = malloc(sizeof(struct treeUsers));
    place = NULL;

    while (isEmptyUsers(users) == 0)
    {
        char * id = obtain_IdUsers(users);
        char * login = obtain_LoginUsers(users);
        place = addUsersTREE(place, id, login);
        users = obtain_nextUser(users);
    }

    return place;
}

/**
 * @brief Função que adiciona nodos a uma árvore de users da query 9.
 * 
 * @param tree Árvore a inserir os ID's dos users.
 * 
 * @param id String com o id a ser guardado.
 * 
 * @param login String com o login associado ao id.
 * 
 * @return Árvore com o user adicionado.
 */
TREEUSERS9 addUsersTREE9(TREEUSERS9 tree, char *id, USERS user)
{
    TREEUSERS9 *place;
    place = &tree;

    while (*place != NULL)
    {
        if (strcmp(id,(*place)->id) < 0)
                 place = &((*place)->l);
        else place = &((*place)->r);
    }

    (*place) = malloc (sizeof (struct treeUsers9));
    (*place)->id = strdup(id);
    (*place)->node = user;
    (*place)->l = (*place)->r = NULL;

    return tree;
}

/**
 * @brief Função que inicializa a árvore de users da query 9.
 * 
 * @param users Catálogo de users.
 * 
 * @return Retorna a árvore criada apartir da lista de users.
 */
TREEUSERS9 iniUsersTREE9(USERS users)
{
    TREEUSERS9 place = malloc(sizeof(struct treeUsers9));
    place = NULL;

    while (isEmptyUsers(users) == 0)
    {
        char * id = obtain_IdUsers(users);
        place = addUsersTREE9(place, id, users);
        users = obtain_nextUser(users);
    }

    return place;
}

/**
 * @brief Função que adiciona nodos a uma árvore de repositórios.
 * 
 * @param tree Árvore a inserir os ID's dos repositórios.
 * 
 * @param id String com o id a ser guardado.
 * 
 * @param message String com a menssagem associado ao id.
 * 
 * @return Árvore com o repositório adicionado.
 */
TREEREPOS addReposTREE(TREEREPOS tree, char *id, char *message)
{
    TREEREPOS *place;
    place = &tree;

    while (*place != NULL)
    {
        if (strcmp(id,(*place)->id) < 0)
                 place = &((*place)->l);
        else place = &((*place)->r);
    }

    (*place) = malloc (sizeof (struct treeRepos));
    (*place)->id = strdup(id);
    (*place)->message = strdup(message);
    (*place)->l = (*place)->r = NULL;

    return tree;
}

/**
 * @brief Função que inicializa a árvore de repositórios.
 * 
 * @param repos Catálogo de repositórios.
 * 
 * @return Retorna a árvore criada apartir da lista de repositórios.
 */
TREEREPOS iniReposTREE(REPOS repos)
{
    TREEREPOS place = malloc(sizeof(struct treeRepos));
    place = NULL;

    while (isEmptyRepos(repos) == 0)
    {
        char * id = obtain_reposID(repos);
        char * login = obtain_reposDescription(repos);
        place = addReposTREE(place, id, login);
        repos = obtain_nextRepos(repos);
    }

    return place;
}

/**
 * @brief Função que inicializa a árvore de repositórios da query 9.
 * 
 * @param repos Catálogo de repositórios.
 * 
 * @return Retorna a árvore criada apartir da lista de repositórios.
 */
TREEREPOS iniReposTREE9(REPOS repos)
{
    TREEREPOS place = malloc(sizeof(struct treeRepos));
    place = NULL;

    while (isEmptyRepos(repos) == 0)
    {
        char * id = obtain_reposID(repos);
        char * login = obtain_reposOwnerID(repos);
        place = addReposTREE(place, id, login);
        repos = obtain_nextRepos(repos);
    }

    return place;
}

/**
 * @brief Função que procura numa árvore binária o elemento especificado
 * 
 * @param tree Árvore binária aonde se irá procurar o elemento
 * 
 * @param x Elemento a encontrar na árvore binária.
 *
 * @return Retorna 1 se o elemento for encontrado.
 */
int search (TREE tree, int x) 
{
	while (tree != NULL && tree->value != x)
    {
        if (tree->value > x) tree = tree->l;
		else tree = tree->r;
    }

	return (tree!=NULL);
}

/**
 * @brief Função que permite a impressão in order da árvore binária.
 * 
 * @param tree Árvore binária a imprimir.
 */
void printTree(TREE tree)
{
    if(tree!=NULL)
    {
        printTree(tree->l);
        printf("valor %d\n", tree->value);
        printTree(tree->r);
    }
}

/**
 * @brief Função que permite libertar o espaço ocupado pela árvore binária.
 * 
 * @param node Árvore.
 */
void freeTree(TREE node){
       if (node != NULL) {
        freeTree(node->r);
        freeTree(node->l);
        free(node);
     }
}

/**
 * @brief Função que permite libertar o espaço ocupado pela árvore de users.
 * 
 * @param node Árvore.
 */
void freeTreeUsers(TREEUSERS node){
       if (node != NULL) {
        freeTreeUsers(node->r);
        freeTreeUsers(node->l);
        free(node);
     }
}

/**
 * @brief Função que permite libertar o espaço ocupado pela árvore binária.
 * 
 * @param node Árvore.
 */
void freeTreeRepos(TREEREPOS node){
       if (node != NULL) {
        freeTreeRepos(node->r);
        freeTreeRepos(node->l);
        free(node);
     }
}

/**
 * @brief Função que o número de nodos de uma árvore binária.
 * 
 * @param node Árvore.
 *
 */
int countnodes(TREE tree)
{
    if(tree!=NULL) return (1+countnodes(tree->l)+countnodes(tree->r));
    else return 0;
}

/**
 * @brief Função que procura numa árvore de users o elemento especificado
 * 
 * @param tree Árvore de users aonde se irá procurar o elemento
 * 
 * @param x Elemento a encontrar na árvore de users.
 *
 * @return Retorna o elemento encontrado.
 */
char * searchUsers (TREEUSERS tree, char * x) 
{
	while (tree != NULL && strcmp(tree->id,x)!=0)
    {
        if (strcmp(tree->id,x) > 0) tree = tree->l;
		else tree = tree->r;
    }

	return strdup(tree->login);
}

/**
 * @brief Função que procura numa árvore de users da query 9 o elemento especificado
 * 
 * @param tree Árvore de users aonde se irá procurar o elemento
 * 
 * @param x Elemento a encontrar na árvore de users da query 9.
 *
 * @return Retorna o elemento encontrado.
 */
USERS searchUsers9 (TREEUSERS9 tree, char * x) 
{
	while (tree != NULL && strcmp(tree->id,x)!=0)
    {
        if (strcmp(tree->id,x) > 0) tree = tree->l;
		else tree = tree->r;
    }

	return (tree->node);
}

/**
 * @brief Função que procura numa árvore de repositórios o elemento especificado
 * 
 * @param tree Árvore de repositórios aonde se irá procurar o elemento
 * 
 * @param x Elemento a encontrar na árvore de repositórios.
 *
 * @return Retorna o elemento encontrado.
 */
char * searchRepos (TREEREPOS tree, char * x) 
{
	while (tree != NULL && strcmp(tree->id,x)!=0)
    {
        if (strcmp(tree->id,x) > 0) tree = tree->l;
		else tree = tree->r;
    }

	return strdup(tree->message);
}

/**
 * @brief Função que cria uma árvore com os amigos de um determinado user.
 * 
 * @param users Nodo do catalogo users.
 * 
 * @param x Número de amigos.
 *
 * @return Retorna a árvore dos amigos.
 */
TREE friendsTreeF(USERS users,int *k) 
{
    USERS temp = users;

    char *follestr = obtain_followersUsers(temp);
    int folleint = atoi(follestr);
    char *follistr = obtain_followingUsers(temp);
    int folliint = atoi(follistr);

    TREE followersTree = NULL;
    TREE friendsTree = NULL;

    if(folleint == 0 || folliint == 0) (*k) = 0;
    else {
            //followersTree = NULL;
            int i;
            char *aux = obtain_followersListUsers(temp);
            char *followersList = aux + 1;
            for(i = 0; i < folleint; i++) {
                char *aux2 = strsep(&followersList, ",]\n");
                int l = atoi(aux2);
                followersTree = insert(followersTree,l);
            }

            //friendsTree = NULL;
            *k = 0;
            char *aux3 = obtain_followingListUsers(temp);
            char *followingList = aux3 + 1;
            for(i = 0; i < folliint; i++) {
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
