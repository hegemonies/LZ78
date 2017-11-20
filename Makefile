all: bin/lz78

bin/lz78: build/coder.o build/lz78.o build/strings.o build/main.o
	gcc -std=c99 -Wall -Werror -I src build/coder.o build/lz78.o build/strings.o build/main.o -o bin/lz78 -g

build/coder.o: src/coder.c
	gcc -std=c99 -Wall -Werror -I src -c src/coder.c -o build/coder.o -g

build/lz78.o: src/lz78.c
	gcc -std=c99 -Wall -Werror -I src -c src/lz78.c -o build/lz78.o -g

build/strings.o: src/strings.c
	gcc -std=c99 -Wall -Werror -I src -c src/strings.c -o build/strings.o -g

build/main.o: src/main.c
	gcc -std=c99 -Wall -Werror -I src -c src/main.c -o build/main.o -g

.PHONY: clean

clean:
	rm build/* bin/*
