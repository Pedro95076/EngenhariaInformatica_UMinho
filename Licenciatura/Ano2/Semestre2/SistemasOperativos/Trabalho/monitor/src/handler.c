#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>

#include "../include/util.h"
#include "../include/handler.h"
#include "../include/readln.h"
#include "../include/info.h"
#include "../include/linkedlist.h"

void create_file(Message start, Message end, char* pids_file)
{
    int status;
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error when creating file");
        exit(-1);
    }

    if(fork_ret == 0)
    {
        char filename[20];

        sprintf(filename, "%s/%d", pids_file, start.pid);

        int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);

        if(fd == -1)
        {
            perror("Open error when opening PID file");
            exit(-1);
        }

        long exec_time = calc_mili(start.timestamp, end.timestamp);

        Info to_write;

        strcpy(to_write.name, start.name);
        to_write.exec_time = exec_time;

        write(fd, &to_write, sizeof(struct info));

        _exit(1);
    }

    waitpid(fork_ret, &status, WNOHANG);
}

void status(HashTable h, Message m)
{
    int status;
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error when creating file");
        exit(-1);
    }

    if(fork_ret == 0)
    {
        char fifoname[20];

        sprintf(fifoname, "/tmp/%d", m.pid);

        int fd = open(fifoname, O_WRONLY);

        if(fd == -1)
        {
            perror("Open error when opening PID FIFO");
            exit(-1);
        }

        int time_ret, write_ret;
        struct timeval now;
        char message[1024];
        long exec_time;

        for(int i = 0; i < HSIZE; i++)
        {
            for(Pair it = h[i]; it != NULL; it = it->next)
            {
                time_ret = gettimeofday(&now, NULL);

                if(time_ret == -1)
                {
                    perror("Timestamp error");
                    exit(-1);
                }

                exec_time = calc_mili(it->info.timestamp, now);

                sprintf(message, "%d %s %ld ms\n", it->info.pid, it->info.name, exec_time);

                write_ret = write(fd, message, strlen(message));

                if(write_ret == -1)
                {
                    perror("Write error when replying status");
                    exit(-1);
                }
            }
        }

        close(fd);

        _exit(1);
    }

    waitpid(fork_ret, &status, WNOHANG);
}

void stats_time(Message m, char* pids_file)
{
    int status;
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error when creating file");
        exit(-1);
    }

    if(fork_ret == 0)
    {
        char fifoname[20];

        sprintf(fifoname, "/tmp/%d", m.pid);

        int num_args = count_char(m.name, ' ') + 1;

        char *pids[num_args];
        char *token, *string;
        int args = 0;

        string = strdup(m.name);

        while((token = strsep(&string, " ")) != NULL)
            pids[args++] = strdup(token);

        free(string);

        int fd, rets[num_args], p[num_args][2];
        long total_time = 0;
        char filename[20];
        Info h;

        for(int i = 0; i < num_args; i++)
        {
            rets[i] = pipe(p[i]);

            if(rets[i] == -1)
            {
                perror("Error creating pipe when handling stats_unique request");
                exit(-1);
            }
            rets[i] = fork();

            if(rets[i] == -1)
            {
                perror("Error forking when handling stats_unique request");
                exit(-1);
            }

            if(rets[i] == 0)
            {
                // Fechar extremo de leitura do pipe anónimo
                close(p[i][0]);

                // Verificar que ficheiro precisamos abrir
                sprintf(filename, "%s/%s", pids_file, pids[i]);

                // Abrir ficheiro
                fd = open(filename, O_RDONLY, 0666);

                if(fd == -1)
                {
                    perror("Open error when opening PID file");
                    _exit(-1);
                }

                // Ler informação do ficheiro
                read(fd, &h, sizeof(struct info));

                // Fechar ficheiro
                close(fd);

                // Escrever para pipe anónimo o nome do programa
                write(p[i][1], &h.exec_time, sizeof(long));

                // Fechar extremo de escrita do pipe anónimo
                close(p[i][1]);

                _exit(1);
            }

            close(p[i][1]);
        }

        long aux;
        for(int i = 0; i < num_args; i++)
        {
            read(p[i][0], &aux, sizeof(long));
            total_time += aux;
            close(p[i][0]);
            waitpid(rets[i], &status, WNOHANG);
        }

        fd = open(fifoname, O_WRONLY);

        if(fd == -1)
        {
            perror("Open error when opening PID FIFO");
            exit(-1);
        }

        int write_ret = write(fd, &total_time, sizeof(long));

        if(write_ret == -1)
        {
            perror("Write error when replying status");
            exit(-1);
        }

        close(fd);

        _exit(1);
    }

    waitpid(fork_ret, &status, WNOHANG);
}

void stats_command(Message m, char* pids_file)
{
    int status;
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error when creating file");
        exit(-1);
    }

    if(fork_ret == 0)
    {
        char fifoname[20];

        char *token, *string, *name;
        int args = 0;

        string = strdup(m.name);

        if((token = strsep(&string, ";")) != NULL)
            name = strdup(token);

        sprintf(fifoname, "/tmp/%d", m.pid);

        int num_args = count_char(string, ' ') + 1;

        char *pids[num_args];

        while((token = strsep(&string, " ")) != NULL)
            pids[args++] = strdup(token);

        free(string);

        int fd, rets[num_args], p[num_args][2];
        int valid = 0;
        char filename[20];
        Info h;

        for(int i = 0; i < num_args; i++)
        {
            rets[i] = pipe(p[i]);

            if(rets[i] == -1)
            {
                perror("Error creating pipe when handling stats_unique request");
                exit(-1);
            }
            rets[i] = fork();

            if(rets[i] == -1)
            {
                perror("Error forking when handling stats_unique request");
                exit(-1);
            }

            if(rets[i] == 0)
            {
                // Fechar extremo de leitura do pipe anónimo
                close(p[i][0]);

                // Verificar que ficheiro precisamos abrir
                sprintf(filename, "%s/%s", pids_file, pids[i]);

                // Abrir ficheiro
                fd = open(filename, O_RDONLY, 0666);

                if(fd == -1)
                {
                    perror("Open error when opening PID file");
                    _exit(-1);
                }

                // Ler informação do ficheiro
                read(fd, &h, sizeof(struct info));

                // Fechar ficheiro
                close(fd);

                if(strcmp(h.name, name) == 0)
                    valid++;
                
                // Escrever para pipe anónimo o nome do programa
                write(p[i][1], &valid, sizeof(int));

                // Fechar extremo de escrita do pipe anónimo
                close(p[i][1]);

                _exit(1);
            }

            close(p[i][1]);
        }

        int aux;
        for(int i = 0; i < num_args; i++)
        {
            read(p[i][0], &aux, sizeof(int));
            valid += aux;
            close(p[i][0]);
            waitpid(rets[i], &status, WNOHANG);
        }

        fd = open(fifoname, O_WRONLY);

        if(fd == -1)
        {
            perror("Open error when opening PID FIFO");
            exit(-1);
        }

        int write_ret = write(fd, &valid, sizeof(int));

        if(write_ret == -1)
        {
            perror("Write error when replying status");
            exit(-1);
        }

        close(fd);

        _exit(1);
    }

    waitpid(fork_ret, &status, WNOHANG);
}

void stats_unique(Message m, char* pids_file)
{
    int status;
    int fork_ret = fork();

    if(fork_ret == -1)
    {
        perror("Fork error when creating file");
        exit(-1);
    }

    if(fork_ret == 0)
    {
        char filename[20];

        int num_args = count_char(m.name, ' ') + 1;

        char *pids[num_args];
        char *token, *string;
        int args = 0;

        string = strdup(m.name);

        while((token = strsep(&string, " ")) != NULL)
            pids[args++] = strdup(token);

        free(string);

        int fd, rets[num_args], p[num_args][2];
        Info h;

        for(int i = 0; i < num_args; i++)
        {
            rets[i] = pipe(p[i]);

            if(rets[i] == -1)
            {
                perror("Error creating pipe when handling stats_unique request");
                exit(-1);
            }
            rets[i] = fork();

            if(rets[i] == -1)
            {
                perror("Error forking when handling stats_unique request");
                exit(-1);
            }

            if(rets[i] == 0)
            {
                // Fechar extremo de leitura do pipe anónimo
                close(p[i][0]);

                // Verificar que ficheiro precisamos abrir
                sprintf(filename, "%s/%s", pids_file, pids[i]);

                // Abrir ficheiro
                fd = open(filename, O_RDONLY, 0666);

                if(fd == -1)
                {
                    perror("Open error when opening PID file");
                    _exit(-1);
                }

                // Ler informação do ficheiro
                read(fd, &h, sizeof(struct info));

                // Fechar ficheiro
                close(fd);

                // Escrever para pipe anónimo o nome do programa
                write(p[i][1], h.name, strlen(h.name));

                // Fechar extremo de escrita do pipe anónimo
                close(p[i][1]);

                _exit(1);
            }

            // Fechar extremo de escrita do pipe anónimo
            close(p[i][1]);
        }

        char name[420];
        LinkedList unique_names = NULL;

        char fifoname[20];

        sprintf(fifoname, "/tmp/%d", m.pid);

        // Abrir FIFO para comunicação com o cliente
        fd = open(fifoname, O_WRONLY);

        if(fd == -1)
        {
            perror("Open error when opening PID FIFO");
            exit(-1);
        }

        // Popular lista de nomes únicos
        for(int i = 0; i < num_args; i++)
        {
            int bytes_read = read(p[i][0], name, 420);

            if(lookup_l(unique_names, name) == 1)
            {
                add(&unique_names, name);
                // Escrever resultado
                write(fd, name, bytes_read);
                write(fd, "\n", 1);
            }
            
            // Fechar extremo de leitura do pipe anónimo
            close(p[i][0]);
            waitpid(rets[i], &status, WNOHANG);
        }

        destroy(unique_names);
        close(fd);

        _exit(1);
    }

    waitpid(fork_ret, &status, WNOHANG);
}

void handle_message(HashTable h, Message message, char* pids_file)
{
    if(message.type == CREATE)
        update(h, message.pid, message);
    else if(message.type == END)
    {
        Message start;
        remove_message(h, message.pid, &start);
        create_file(start, message, pids_file);
    }
    else if(message.type == STATUS)
        status(h, message);
    else if(message.type == STATS_TIME)
        stats_time(message, pids_file);
    else if(message.type == STATS_COMMAND)
        stats_command(message, pids_file);
    else if(message.type == STATS_UNIQUE)
        stats_unique(message, pids_file);
}