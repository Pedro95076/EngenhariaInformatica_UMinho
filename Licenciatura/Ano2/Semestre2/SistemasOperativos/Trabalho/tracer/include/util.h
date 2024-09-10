#ifndef UTIL_H
#define UTIL_H

long calc_mili(struct timeval begin, struct timeval end);

int count_char(char* string, char x);

void build_pipe_name(char** piped_commands, int piped_num_commands, char* name);

#endif // UTIL_H