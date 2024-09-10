#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "../include/handler.h"

int fdr, fdw;
char* fifo = "/tmp/monitor";
HashTable h;

void signal_callback_handler(int signum)
{
    int close_ret = close(fdr);

    if(close_ret == -1)
    {
        perror("Close error");
        exit(-1);
    }

    close_ret = close(fdw);

    if(close_ret == -1)
    {
        perror("Close error");
        exit(-1);
    }

    close_ret = unlink(fifo);

    if(close_ret != 0)
    {
        perror("Unlink error");
        exit(-1);
    }

    destroy_table(h);

    exit(signum);
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        perror("Invalid number of arguments");
        exit(-1);
    }

    int bytes_read;
    Message message;

    int mkfifo_ret = mkfifo(fifo, 0666);

    if(mkfifo_ret == -1)
    {
        perror("Mkfifo error");
        exit(-1);
    }

    signal(SIGINT, signal_callback_handler);

    fdr = open(fifo, O_RDONLY);

    if(fdr == -1)
    {
        perror("Open error");
        exit(-1);
    }

    fdw = open(fifo, O_WRONLY);

    if(fdw == -1)
    {
        perror("Open error");
        exit(-1);
    }

    while((bytes_read = read(fdr, &message, sizeof(message)) > 0))
    {
        if(bytes_read == -1)
        {
            perror("Read error -> monitor");
            exit(-1);
        }
        
        handle_message(h, message, (char*) argv[1]);
    }

    return 0;
}