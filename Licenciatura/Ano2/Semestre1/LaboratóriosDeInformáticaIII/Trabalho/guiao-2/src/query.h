/**
  * @file Ficheiro header referente ás querys.
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "data_users.h"
#include "data_commits.h"
#include "data_repos.h"
#include "data_tpll.h"
#include "data_tree.h"
#include "data.h"

void queryID(int n_file, int id, char *line, USERS users, COMMITS commits, REPOS repos, TREEUSERS usersArv, TREEREPOS reposArv, TREEUSERS9 usersArv9, TREEREPOS reposArv9);
void query1(char *n_file, USERS users);
void query2(char *n_file, REPOS repos, COMMITS commits);
void query3(char *n_file, USERS users, COMMITS commits);
void query4(char *n_file, USERS users, COMMITS commits);
void query5(char *n_file, char *line, COMMITS commits, TREEUSERS usersArv);
void query6(char *n_file, char *line, COMMITS commits, REPOS repos, TREEUSERS usersArv);
void query7(char *n_file, char *line, REPOS repos, COMMITS commits, TREEREPOS reposArv);
void query8(char *n_file, char *line, REPOS repos);
void query9(char *n_file, char *line, COMMITS commits, REPOS repos, TREEUSERS usersArv, TREEREPOS reposArv9, TREEUSERS9 usersArv9);
void query10(char *n_file, char *line, COMMITS commits, TREEUSERS usersArv);
