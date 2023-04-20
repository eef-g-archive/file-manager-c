main: runtime.c
	gcc -Wall -Wextra -pedantic -std=c99 -o main.exe runtime.c src/reader.c src/MBR.c src/part.c src/utility.c src/fat16.c
all: main

.PHONY: clean 

clean:
	rm main.exe