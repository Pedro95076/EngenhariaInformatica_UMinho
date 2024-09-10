CC = gcc
CFLAGS = -g -Wall -O2

SRC = src/
OBJ = obj/

default: monitor

monitor: monitor.o handler.o hashtable.o linkedlist.o readln.o util.o
	$(CC) $(CFLAGS) -o monitor $(OBJ)monitor.o $(OBJ)handler.o $(OBJ)hashtable.o $(OBJ)linkedlist.o $(OBJ)readln.o $(OBJ)util.o 

monitor.o:
	$(CC) $(CFLAGS) -c $(SRC)monitor.c -o $(OBJ)monitor.o

handler.o:
	$(CC) $(CFLAGS) -c $(SRC)handler.c -o $(OBJ)handler.o

hashtable.o:
	$(CC) $(CFLAGS) -c $(SRC)hashtable.c -o $(OBJ)hashtable.o

linkedlist.o:
	$(CC) $(CFLAGS) -c $(SRC)linkedlist.c -o $(OBJ)linkedlist.o

readln.o:
	$(CC) $(CFLAGS) -c $(SRC)readln.c -o $(OBJ)readln.o

util.o:
	$(CC) $(CFLAGS) -c $(SRC)util.c -o $(OBJ)util.o 

clean: 
	$(RM) tracer $(OBJ)*.o *~