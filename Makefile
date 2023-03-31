


build:
	gcc shell.c -o shell

build_run:	build
	./shell	

clean:
	rm shell