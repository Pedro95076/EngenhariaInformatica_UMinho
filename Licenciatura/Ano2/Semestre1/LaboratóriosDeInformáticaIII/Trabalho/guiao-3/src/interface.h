#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HT_users.h"
#include "HT_commits.h"
#include "HT_repos.h"

void mainMenu(HT_Users *users, HT_Commits *commits, HT_Repos *repos);
void chooseQuery(int query, HT_Users *users, HT_Commits *commits, HT_Repos *repos);