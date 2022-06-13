SHELL = /bin/bash
CC = gcc
CFLAGS = -g -pthread
SRC = $(wildcard *.c)
EXE = $(patsubst %.c, %, $(SRC))

SRC2 = $(wildcard *.csv)
SRC3 = $(wildcard *.png)


all: ${EXE}

%:	%.c
	${CC} ${CFLAGS} $@.c -o $@

plot:
	sudo taskset -c 0 ./main 10000 > data.csv 
	gnuplot plot_bitmap.gp
	mv data.csv  10000_data.csv 
	mv bitmap.png 10000_bitmap.png

	sudo taskset -c 0 ./main 50000 > data.csv 
	gnuplot plot_bitmap.gp
	mv data.csv  50000_data.csv 
	mv bitmap.png 50000_bitmap.png

	sudo taskset -c 0 ./main 100000 > data.csv 
	gnuplot plot_bitmap.gp
	mv data.csv  100000_data.csv 
	mv bitmap.png 100000_bitmap.png

clean:
	rm ${EXE} 
	rm ${SRC2} 
	rm ${SRC3}
	