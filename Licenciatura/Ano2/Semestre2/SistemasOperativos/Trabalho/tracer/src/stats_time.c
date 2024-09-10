#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "../include/message.h"
#include "../include/stats_time.h"

char* fifo_st = "/tmp/monitor";

void stats_time(char* args[], int args_num)
{
    int rets, fifo_fd;
    long exec_time = 0;
    Message m;

    for(int i = 0; i < args_num - 1; i++)
    {
        strcat(m.name, args[i]);
        strcat(m.name, " ");
    }
    
    strcat(m.name, args[args_num - 1]);

    fifo_fd = open(fifo_st, O_WRONLY);

    if(fifo_fd == -1)
    {
        perror("Open error");
        exit(-1);
    }
            
    // Preparar FIFO de resposta (leitura)
    char fifoname[20];

    sprintf(fifoname, "/tmp/%d", getpid());

    rets = mkfifo(fifoname, 0666);

    if(rets == -1)
    {
        perror("FIFO error");
        exit(0);
    }

    // Enviar mensagem tipo STATS_TIME ao monitor através do FIFO /tmp/monitor
    m.type = STATS_TIME;
    m.pid = getpid();

    rets = write(fifo_fd, &m, sizeof(Message));

    if(rets == -1)
    {
        perror("Write error");
        exit(0);
    }

    close(fifo_fd);

    // Ler resposta do monitor através do FIFO /tmp/(getpid())
    fifo_fd = open(fifoname, O_RDONLY);

    if(fifo_fd == -1)
    {
        perror("Open FIFO to read");
        exit(0);
    }

    rets = read(fifo_fd, &exec_time, sizeof(long));

    if(rets == -1)
    {
        perror("Read error");
        exit(0);
    }

    close(fifo_fd);
    unlink(fifoname);

    printf("Total execution time is %ld ms\n", exec_time);
}