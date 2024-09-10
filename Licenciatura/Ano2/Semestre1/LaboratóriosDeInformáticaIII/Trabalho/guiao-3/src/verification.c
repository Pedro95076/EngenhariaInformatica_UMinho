/**
  * @file Ficheiro com modularidade e encapsulamento referente à verificação dos ficheiros iniciais
  */
#include "verification.h"

/**
 * @brief Função que permite a filtração dos commits considerando os repositórios existentes
 * 
 * @param commits Hashtable com a informação dos commits
 * 
 * @param repos Hashtable com a informação dos repositórios
 */
void filterCommits(HT_Commits *commits, HT_Repos *repos)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HT_Commits aux = find_HashTableCommitsKey(commits, i);
        while(aux != NULL)
        {
            char *repoID = obtain_commitsReposId(aux);
            if (find_HashTableReposBool(repos, repoID) == 1)
            {
                delete_tableCommits(commits,repoID);
            }
        
            aux = obtain_nextCommit(aux);
        }
    }
}

/**
 * @brief Função que permite a filtração dos repositórios considerando o número de commits existentes
 * 
 * @param commits Hashtable com a informação dos commits
 * 
 * @param repos Hashtable com a informação dos repositórios
 */
void filterRepos(HT_Commits *commits, HT_Repos *repos)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HT_Repos aux = find_HashTableReposKey(repos, i);
        while(aux != NULL)
        {
            char *repoID = obtain_reposId(aux);
            if (find_HashTableCommitsBool(commits, repoID) == 1)
            {
                delete_tableRepos(repos,repoID);
            }
        
            aux = obtain_nextRepos(aux);
        }
    }   
}