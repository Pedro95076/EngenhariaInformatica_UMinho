#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#define BUFFER_SIZE 1024

char buff[BUFFER_SIZE];
int inicio = 0;
int fim = 0;

int readc(int fd, char* c)
{
    if(inicio == fim)
    {
        fim = read(fd, buff, BUFFER_SIZE);
        inicio = 0;
    }
    
    if(fim == 0)
    {
        return 0;
    }

    *c = buff[inicio];
    inicio++;
    return 1;
    
}

ssize_t readln(int fd, char* line, size_t size)
{
    int i = 0;

    while(i < size && readc(fd, line + i) > 0)
    {
        if(line[i] == '\n')
        {
            return i + 1;
        }
        i++;
    }

    return i;
}
