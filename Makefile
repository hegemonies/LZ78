all: bin/main

bin/main: build/coder.o build/lz78.o build/strings.o build/main.o
	gcc -Wall -Werror -I src build/coder.o build/lz78.o build/strings.o build/main.o -o bin/main -g

build/coder.o: src/coder.c
	gcc -Wall -Werror -I src -c src/coder.c -o build/coder.o -g

build/lz78.o: src/lz78.c
	gcc -Wall -Werror -I src -c src/lz78.c -o build/lz78.o -g

build/strings.o: src/strings.c
	gcc -Wall -Werror -I src -c src/strings.c -o build/strings.o -g

build/main.o: src/main.c
	gcc -Wall -Werror -I src -c src/main.c -o build/main.o -g

.PHONY: clean

clean:
	rm build/* bin/*
