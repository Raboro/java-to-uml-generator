default: 
	gcc -c -o main.o src/main.c
	gcc -c -o file_scanning.o src/file_scanning.c
	gcc -c -o cli_parser.o src/cli_parser.c
	gcc -c -o uml_parser.o src/uml_parser.c
	gcc -O3 -Wall -Wextra -o jtuml main.o file_scanning.o cli_parser.o uml_parser.o
	$(MAKE) cleanup

cleanup:
	rm -f main.o
	rm -f file_scanning.o
	rm -f cli_parser.o
	rm -f uml_parser.o
	rm -f uml.md

run_here:
	$(MAKE) default
	./jtuml