all : virtualMachine

virtualMachine : main.c stack.c stack.h instruction.c instruction.h register.c register.h
	gcc -Wall -o virtualMachine main.c stack.c instruction.c register.c -I.

clean:
	rm virtualMachine
