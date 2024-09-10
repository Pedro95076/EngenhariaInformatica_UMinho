#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../include/util.h"
#include "../include/message.h"
#include "../include/pipeline.h"

char* fifo_p = "/tmp/monitor";

int pipeline(char* pipe_command)
{
    // Abrir FIFO de comunicação com o monitor
    int fd = open(fifo_p, O_WRONLY);

    if(fd == -1)
    {
        perror("Open error");
        exit(-1);
    }

    // Para guardar os timestamps.
    struct timeval start, end;

    int num_piped_commands = count_char(pipe_command, '|') + 1;

    char *piped_commands[num_piped_commands];
    char *token, *string, name[1024];   
    int args = 0;

    // Dar parse ao comando e guardar os argumentos em execvp_argss.
    string = strdup(pipe_command);

    while((token = strsep(&string, "|")) != NULL)
        piped_commands[args++] = strdup(token);

    free(string);

    int pid[num_piped_commands], p[num_piped_commands - 1][2];

    for(int i = 0; i < num_piped_commands - 1; i++)
        pipe(p[i]);

    // Timestamp imediatamente antes de executar o comando.
    int time_ret = gettimeofday(&start, NULL);

    if(time_ret == -1)
    {
        perror("Timestamp error");
        exit(-1);
    }

    for(int i = 0; i < num_piped_commands; i++)
    {
        if((pid[i] = fork()) == -1)
        {
            perror("Fork");
            exit(-1);
        }

        if(pid[i] == 0)
        {
            // Primeiro processo tem de:
            // - Fechar extremo de leitura p[i][0]
            // - Fechar todos os restantes pipes exceto extremo de escrita do pipe i
            // - Associar próprio extremo de escrita ao pipe de escrita do pipe i
            if(i == 0)
            {
                close(p[i][0]);

                for(int j = 0; j < num_piped_commands - 1; j++)
                {
                    if(j != i)
                    {
                        close(p[j][0]);
                        close(p[j][1]);
                    }
                }

                build_pipe_name(piped_commands, num_piped_commands, name);

                printf("Running PID %d\n", getpid());

                dup2(p[i][1], 1);

                Message message;

                message.type = CREATE;
                message.pid = getpid();
                message.timestamp = start;
                strcpy(message.name, name);

                write(fd, &message, sizeof(Message));
            }
            // Último processo tem de:
            // - Fechar extremo de escrita do último pipe p[i - 1][1]
            // - Fechar todos os restantes pipes exceto extremo de leitura do pipe i - 1
            // - Associar próprio extremo de leitura ao pipe de leitura do pipe i - 1
            else if(i == num_piped_commands - 1)
            {
                close(p[i - 1][1]);

                for(int j = 0; j < num_piped_commands - 1; j++)
                {
                    if(j != (i - 1))
                    {
                        close(p[j][0]);
                        close(p[j][1]);
                    }
                }

                dup2(p[i - 1][0], 0);
            }
            // Processos intermediários tm de:
            // - Fechar extremos de escrita exceto do pipe i
            // - Fechar extremos de leitura exceto do pipe i - 1
            // - Associar próprio extremo de leitura ao pipe de leitura do pipe i - 1
            // - Associar próprio extremo de escrita ao pipe de escrita do pipe i
            else
            {
                for(int j = 0; j < num_piped_commands - 1; j++)
                {
                    if(j != i)
                        close(p[j][1]);
                }

                for(int j = 0; j < num_piped_commands - 1; j++)
                {
                    if(j != (i - 1))
                        close(p[j][0]);
                }

                dup2(p[i - 1][0], 0);
                dup2(p[i][1], 1);
            }

            int num_argsv = count_char(piped_commands[i], ' ') + 2;

            char *argsv[num_argsv];
            args = 0;

            string = strdup(piped_commands[i]);

            while((token = strsep(&string, " ")) != NULL)
            {
                if(strlen(token) > 0)
                    argsv[args++] = strdup(token);
            }

            argsv[args] = NULL;

            free(string);

            // Executar comando
            execvp(argsv[0], argsv);

            _exit(0);
        }
    }

    for(int i = 0; i < num_piped_commands - 1; i++)
    {
        close(p[i][0]);
        close(p[i][1]);
    }

    for(int i = 0; i < num_piped_commands; i++)
        free(piped_commands[i]);

    int status;

    // Esperar que os filhos terminem.
    for(int i = 0; i < num_piped_commands; i++)
        wait(&status);

    // Timestamp do final da execução do comando.
    time_ret = gettimeofday(&end, NULL);

    if(time_ret == -1)
    {
        perror("Timestamp error");
        exit(-1);
    }

    Message message;
    message.type = END;
    message.pid = pid[0];
    message.timestamp = end;

    write(fd, &message, sizeof(Message));

    if(WIFEXITED(status))
    {
        // Imprimir tempo de execução.
        printf("Ended in %ld ms\n", calc_mili(start, end));

        return WEXITSTATUS(status); 
    }

    close(fd);
    
    return 0;
}