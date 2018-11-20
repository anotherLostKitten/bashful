all: parse_args.o shell.o control.o execute.o
	gcc -o shell shell.o control.o execute.o parse_args.o
shell.o: shell.c
	gcc -c shell.c
control.o: control.c
	gcc -c control.c
execute.o: execute.c
	gcc -c execute.c
parse_args.o: parse_args.c
	gcc -c parse_args.c
run: all
	./shell
clean:
	rm *~* \#*\# shell *.o
