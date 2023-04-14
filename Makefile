main: runtime.c
	gcc -Wall -Wextra -pedantic -std=c99 -o main.exe runtime.c src/reader.c src/MBR.c src/Partition.c


all: main

.PHONY: clean 

clean:
	rm main.exe