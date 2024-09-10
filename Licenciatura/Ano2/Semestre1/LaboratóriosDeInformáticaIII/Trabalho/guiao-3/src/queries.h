/**
 * @file Ficheiro header referente às funções das queries
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "HT_users.h"
#include "HT_commits.h"
#include "HT_repos.h"

void handle_Queries(int i, int id, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos);
void query1(char *n_file, HT_Users *users);
void query2(char *n_file, HT_Commits *commits, HT_Repos *repos);
void query3(char *n_file, HT_Users *users, HT_Commits *commits);
void query4(char *n_file, HT_Users *users, HT_Commits *commits);
void query5(char *n_file, char *line, HT_Commits *commits, HT_Users *users);
void query6(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos);
void query7(char *n_file, char *line, HT_Commits *commits, HT_Repos *repos);
void query8(char *n_file, char *line, HT_Repos *repos);
void query9(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos);
void query10(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos);
void query11(char *n_file, char *line, HT_Users *users, HT_Commits *commits, HT_Repos *repos);