all:
	gcc -Wall -Wextra main.c -lgcrypt -lb2 && ./a.out
demo:
	gcc -Wall -Wextra demo.c -lgcrypt -lb2 && ./a.out
clean:
	rm -rf *.o *.out
