all:
	gcc -Wall -Wextra *.c -lgcrypt -lb2 && ./a.out
clean:
	rm -rf *.o *.out
