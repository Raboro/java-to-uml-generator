default: 
	gcc -c -o main.o src/main.c
	gcc -c -o file_scanning.o src/file_scanning.c
	gcc -Wall -Wextra -o main main.o file_scanning.o
	$(MAKE) cleanup

cleanup:
	rm main.o
	rm file_scanning.o