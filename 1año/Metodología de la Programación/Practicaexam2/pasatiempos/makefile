.PHONY:clean
all:crucigrama.x libMemoria.a
libMemoria.a:liberaMemoria.o reservaMemoria.o memoria.h
	ar -rvs libMemoria.a liberaMemoria.o reservaMemoria.o
liberaMemoria.o: liberaMemoria.c memoria.h
	gcc -Wall -c liberaMemoria.c
reservaMemoria.o: reservaMemoria.c memoria.h
	gcc -Wall -c reservaMemoria.c
crucigrama.x:main.o ficheros.o crucigrama.o memoria.h crucigrama.h ficheros.h libMemoria.a
	gcc -Wall -o crucigrama.x main.o crucigrama.o ficheros.o libMemoria.a
main.o:main.c memoria.h crucigrama.h ficheros.h
	gcc -Wall -c main.c
ficheros.o:ficheros.c ficheros.h
	gcc -Wall -c ficheros.c
crucigrama.o: crucigrama.c crucigrama.h
	gcc -Wall -c crucigrama.c
clean:
	rm -f *.o