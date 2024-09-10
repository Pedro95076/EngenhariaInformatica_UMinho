#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "../include/message.h"
#include "../include/readln.h"
#include "../include/status.h"

char* fifo_s = "/tmp/monitor";

void status()
{
    // Obter PID do processo para abrir FIFO para comunicação monitor -> tracer
    int pid = getpid();

    char fifoname[20];

    // FIFO com nome /tmp/(pid)
    sprintf(fifoname, "/tmp/%d", pid);

    // Criar FIFO
    int rets = mkfifo(fifoname, 0666);

    if(rets == -1)
    {
        perror("Mkfifo error");
        exit(-1);
    }

    // Abrir extremo de escrita para comunicação com o monitor, ou seja, FIFO /tmp/monitor
    int fd = open(fifo_s, O_WRONLY);

    if(fd == -1)
    {
        perror("Open error");
        exit(-1);
    }

    // Gerar mensagem de tipo STATUS e enviar o PID que origina o nome do FIFO para comunicação
    // monitor -> tracer
    Message m;
    m.type = STATUS;
    m.pid = pid;

    // Enviar mensagem ao monitor para processamento
    rets = write(fd, &m, sizeof(Message));

    if(rets == -1)
    {
        perror("Writing status");
        exit(-1);
    }

    // Fechar extremo de escrita de /tmp/monitor
    close(fd);

    // Abrir extremo de leitura de /tmp/(pid)
    fd = open(fifoname, O_RDONLY);

    char buffer[1024];

    // Enquanto o número de bytes lidos não for 0 ler e imprimir o conteúdo lido
    while((rets = readln(fd, buffer, 1024)) > 0)
        write(1, buffer, rets);

    // Fechar extremo de leitura de /tmp/(pid)
    close(fd);

    // Desfazer FIFO /tmp/(pid)s
    unlink(fifoname);
}