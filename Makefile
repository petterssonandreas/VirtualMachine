all : virtualMachine

virtualMachine : main.c stack.c instruction.c
	gcc -Wall -o virtualMachine main.c stack.c instruction.c -I.

clean:
	rm virtualMachine
