TARGET = guiao-1

OUT = saida
SRC = src
BIN = obj

SOURCE = $(wildcard $(SRC)/*.c)
OBJECT = $(patsubst %,$(BIN)/%, $(notdir $(SOURCE:.c=.o)))

CC = gcc
CFLAGS = -Wall

$(TARGET) : $(OBJECT)
	$(CC) -O2 -Wall -g -o $@ $^
	@echo "Compiled!"

$(BIN)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJECT) $(TARGET) $(OUT)/*.txt