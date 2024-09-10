#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../include/system.h"
#include "../include/message.h"
#include "../include/util.h"

char* fifo = "/tmp/monitor";

int _system_(char* command)
{
    int fd = open(fifo, O_WRONLY);

    if(fd == -1)
    {
        perror("Open error");
        exit(-1);
    }

    // Contar número de argumentos com base no número de espaços no comando
    // mais 2 para o último argumento e para o elemento NULL do execvps.
    int num_args = count_char(command, ' ') + 2;

    // Para guardar os timestamps.
    struct timeval start, end;
    
    // Para guardar os argumentos.
    char *execvp_args[num_args];
    char *token, *string;
    int args = 0, status;

    // Dar parse ao comando e guardar os argumentos em execvp_argss.
    string = strdup(command);

    while((token = strsep(&string, " ")) != NULL)
    {
        if(strlen(token) > 0)
            execvp_args[args++] = strdup(token);
    }

    execvp_args[args] = NULL;
    
    // Criar processo filho para executar o comando.
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error");
        exit(-1);
    }

    // Timestamp imediatamente antes de executar o comando.
    int time_ret = gettimeofday(&start, NULL);

    if(time_ret == -1)
    {
        perror("Timestamp error");
        exit(-1);
    }
    
    // Processo filho
    if(fork_ret == 0)
    {
        // Imprimir PID do processo filho.
        printf("Running PID %d\n", getpid());

        Message message;

        message.type = CREATE;
        message.pid = getpid();
        message.timestamp = start;
        sprintf(message.name, "%s", execvp_args[0]);

        write(fd, &message, sizeof(Message));
        
        // Executar o comando
        execvp(execvp_args[0], execvp_args);

        perror("Exec error");
        _exit(-1);
    }

    // Esperar que o filho termine.
    int terminated_pid = wait(&status);

    // Timestamp do final da execução do comando.
    time_ret = gettimeofday(&end, NULL);

    if(time_ret == -1)
    {
        perror("Timestamp error");
        exit(-1);
    }

    Message message;
    message.type = END;
    message.pid = terminated_pid;
    message.timestamp = end;

    write(fd, &message, sizeof(Message));

    if(WIFEXITED(status))
    {
        // Imprimir tempo de execução.
        printf("Ended in %ld ms\n", calc_mili(start, end));

        return WEXITSTATUS(status); 
    }

    free(string);

    close(fd);

    for(int i = 0; i < num_args && execvp_args[i] != NULL; i++)
        free(execvp_args[i]);

    return -1;
}