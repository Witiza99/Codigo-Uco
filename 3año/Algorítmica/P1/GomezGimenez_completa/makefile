NAME=main

#
OBJECTS = $(NAME).o \
		main.o \
		Quicksort.o \
		ClaseTiempo.o \
		sistemaEcuaciones.o \
		multiplicacionmatrices.o \

#
CPPFLAGS = -c -g -Wall -ansi -O2 -lrt

INCLUDES = sistemaEcuaciones.hpp \

# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

objetivo: $(NAME).exe

#Opciones para NO depurar los asertos
#ndebug: CPPFLAGS += -DNDEBUG 
#ndebug: objetivo

# Primer objetivo 
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp Quicksort.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
Quicksort.o: Quicksort.cpp ClaseTiempo.cpp Quicksort.hpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<


ClaseTiempo.o: ClaseTiempo.cpp
			@g++ $(CPPFLAGS) $<

sistemaEcuaciones.o: sistemaEcuaciones.cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

#
multiplicacionmatrices.o: multiplicacionmatrices.cpp ClaseTiempo.cpp Multiplicacionmatrices.hpp  $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<
#

# Borrado
.PHONY: clean  
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~ 