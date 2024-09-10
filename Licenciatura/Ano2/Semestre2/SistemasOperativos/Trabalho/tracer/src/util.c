#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "../include/util.h"

long calc_mili(struct timeval begin, struct timeval end)
{
    long seg = end.tv_sec - begin.tv_sec;
    seg *= 1000;

    long micro = end.tv_usec - begin.tv_usec;
    micro /= 1000;

    return seg + micro;
}

int count_char(char* string, char x)
{
    int number_ocrr = 0;

    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == x)
            number_ocrr++;
    }

    return number_ocrr;
}

void build_pipe_name(char** piped_commands, int piped_num_commands, char* name)
{
    int num_commands;

    char *token, *string;
    int args, flag;

    for(int i = 0; i < piped_num_commands - 1; i++)
    {
        if(strcmp(piped_commands[i], "") != 0)
        {
            num_commands = count_char(piped_commands[i], ' ');
            args = flag = 0;

            string = strdup(piped_commands[i]);

            char *command_args[num_commands];

            while((token = strsep(&string, " ")) != NULL)
                command_args[args++] = strdup(token);

            free(string);

            for(int j = 0; j < num_commands && flag == 0; j++)
            {
                if(strcmp(command_args[j], "") != 0)
                {
                    strcat(name, command_args[j]);
                    flag = 1;
                }
                free(command_args[j]);
            }
            strcat(name, " | ");
        }
    }

    num_commands = count_char(piped_commands[piped_num_commands - 1], ' ');
    args = flag = 0;

    string = strdup(piped_commands[piped_num_commands - 1]);

    char *command_args[num_commands];

    while((token = strsep(&string, " ")) != NULL)
        command_args[args++] = strdup(token);

    free(string);

    for(int i = 0; i < num_commands && flag == 0; i++)
    {
        if(strcmp(command_args[i], "") != 0)
        {
            strcat(name, command_args[i]);
            flag = 1;
        }

        free(command_args[i]);
    }
}