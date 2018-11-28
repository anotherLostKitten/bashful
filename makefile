all: parse_args.o shell.o control.o execute.o input.o dll.o chario.o
	gcc -o shell shell.o control.o execute.o parse_args.o input.o dll.o chario.o
shell.o: shell.c
	gcc -c shell.c
control.o: control.c
	gcc -c control.c
execute.o: execute.c
	gcc -c execute.c
parse_args.o: parse_args.c
	gcc -c parse_args.c
input.o: input.c
	gcc -c input.c
dll.o: dll.c
	gcc -c dll.c
chario.o: chario.c
	gcc -c chario.c
run: all
	./shell
clean:
	rm *~* \#*\# shell *.o
