/**
  * @file Ficheiro header referente à verificação dos ficheiros iniciais.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HT_commits.h"
#include "HT_repos.h"
#include "auxiliarFunc.h"

void filterCommits(HT_Commits *commits, HT_Repos *repos);
void filterRepos(HT_Commits *commits, HT_Repos *repos);