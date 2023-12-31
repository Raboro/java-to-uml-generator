default: 
	gcc -c -o main.o src/main.c
	gcc -c -o file_scanning.o src/file_scanning.c
	gcc -c -o cli_parser.o src/cli_parser.c
	gcc -O3 -Wall -Wextra -o jtuml main.o file_scanning.o cli_parser.o
	$(MAKE) cleanup

cleanup:
	rm main.o
	rm file_scanning.o
	rm cli_parser.o

run_here:
	$(MAKE) default
	./jtuml