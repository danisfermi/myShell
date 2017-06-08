all:
	chmod a+x myShell.c
	gcc -o myShell myShell.c
clean:
	rm *o myShell
