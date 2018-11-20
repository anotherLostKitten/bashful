all: shell.o control.o execute.o
	gcc -o shell shell.o control.o execute.o
shell.o: shell.c
	gcc -c shell.c
control.o: control.c
	gcc -c control.c
execute.o: execute.c
	gcc -c execute.c
run: all
	./shell
