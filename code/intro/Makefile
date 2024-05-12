all: cpu mem threads io

clean:
	rm -f cpu mem threads io

cpu: cpu.c common.c common.h
	gcc -o cpu cpu.c common.c -Wall

mem: mem.c common.c common.h
	gcc -o mem mem.c common.c -Wall

threads: threads.c
	gcc -o threads threads.c -Wall -pthread

io: io.c
	gcc -o io io.c -Wall
	
