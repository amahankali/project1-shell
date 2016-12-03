compile: pipe.c main.c
	gcc pipe.c main.c -o Driver

run: Driver
	./Driver

clear: *~
	rm *~
