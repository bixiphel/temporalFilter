CC = gcc

CFLAGS = -Wall -Wextra

SRC = $(shell find src -name "*.c")

TARGET = stfilter

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lm

clean:
	rm -f $(TARGET) \
    rm temp -r    
