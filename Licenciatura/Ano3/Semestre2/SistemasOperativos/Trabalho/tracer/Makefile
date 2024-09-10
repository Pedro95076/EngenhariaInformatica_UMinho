CC = gcc
CFLAGS = -g -Wall -O2

SRC = src/
OBJ = obj/

default: tracer

tracer: tracer.o system.o pipeline.o util.o status.o readln.o stats_time.o stats_command.o stats_unique.o
	$(CC) $(CFLAGS) -o tracer $(OBJ)tracer.o $(OBJ)system.o $(OBJ)pipeline.o $(OBJ)status.o $(OBJ)readln.o $(OBJ)stats_time.o $(OBJ)stats_command.o $(OBJ)stats_unique.o $(OBJ)util.o

tracer.o:
	$(CC) $(CFLAGS) -c $(SRC)tracer.c -o $(OBJ)tracer.o

system.o:
	$(CC) $(CFLAGS) -c $(SRC)system.c -o $(OBJ)system.o 

pipeline.o:
	$(CC) $(CFLAGS) -c $(SRC)pipeline.c -o $(OBJ)pipeline.o

status.o:
	$(CC) $(CFLAGS) -c $(SRC)status.c -o $(OBJ)status.o

stats_time.o:
	$(CC) $(CFLAGS) -c $(SRC)stats_time.c -o $(OBJ)stats_time.o

stats_command.o:
	$(CC) $(CFLAGS) -c $(SRC)stats_command.c -o $(OBJ)stats_command.o

stats_unique.o:
	$(CC) $(CFLAGS) -c $(SRC)stats_unique.c -o $(OBJ)stats_unique.o

readln.o:
	$(CC) $(CFLAGS) -c $(SRC)readln.c -o $(OBJ)readln.o

util.o:
	$(CC) $(CFLAGS) -c $(SRC)util.c -o $(OBJ)util.o 

clean: 
	$(RM) tracer $(OBJ)*.o *~