main: runtime.c
	gcc -Wall -Wextra -pedantic -std=c99 -o main.exe runtime.c src/reader.c src/MBR.c src/Partition.c src/utility.c

main-win: runtime.c
	gcc -Wall -Wextra -pedantic -std=c99 -o main.exe runtime.c .\src\reader.c .\src\MBR.c .\src\Partition.c .\src\utility.c

all: main

.PHONY: clean 

clean:
	rm main.exe