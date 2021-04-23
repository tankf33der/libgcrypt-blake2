all:
	gcc -Wall -Wextra *.c -lgcrypt && ./a.out
clean:
	rm -rf *.o *.out
