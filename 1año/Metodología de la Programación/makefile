all: libMemoria.a crucigrama.x clear
.PHONY:all, clear
libMemoria.a: liberaMemoria.o reservaMemoria.o
	ar -rvs libMemoria.a liberaMemoria.o reservaMemoria.o
liberaMemoria.o: liberaMemoria.c memoria.h
	-gcc -c liberaMemoria.c
reservaMemoria.o: reservaMemoria.c memoria.h
	-gcc -c reservaMemoria.c
crucigrama.o: crucigrama.c crucigrama.h
	-gcc -c crucigrama.c
ficheros.o: ficheros.c ficheros.h
	-gcc -c ficheros.c
main.o: main.c crucigrama.h ficheros.h memoria.h
	-gcc -c main.c
crucigrama.x: libMemoria.a main.o ficheros.o crucigrama.o
	-gcc -o crucigrama.x main.o ficheros.o crucigrama.o libMemoria.a
clear:
	@ -rm -f *.o