all:crucigrama.x libMemoria.a
.PHONY: clean
libMemoria.a: reservaMemoria.o liberaMemoria.o memoria.h
	-ar rvs libMemoria.a liberaMemoria.o reservaMemoria.o
liberaMemoria.o: liberaMemoria.c memoria.h
	gcc -Wall -c liberaMemoria.c
reservaMemoria.o: reservaMemoria.c memoria.h
	gcc -Wall -c reservaMemoria.c 
crucigrama.x: libMemoria.a crucigrama.o ficheros.o main.o ficheros.h crucigrama.h memoria.h
	gcc -Wall -o crucigrama.x main.o ficheros.o crucigrama.o libMemoria.a
main.o: main.c crucigrama.h ficheros.h memoria.h
	gcc -Wall -c main.c
ficheros.o: ficheros.c ficheros.h
	gcc -Wall -c ficheros.c
crucigrama.o: crucigrama.c crucigrama.h
	gcc -Wall -c crucigrama.c
clean:
	rm -f *.o