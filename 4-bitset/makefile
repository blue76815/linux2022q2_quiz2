SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

plot:
	sudo taskset -c 0 ./main 10000
	gnuplot plot_bitmap.gp

clean:
	rm ${EXE}