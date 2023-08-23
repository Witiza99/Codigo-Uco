#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int librosdiferentes(char fichero[50]){

	FILE *F;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_END);

	int total=ftell(F);

	int registros=(total/(sizeof(struct libros)));

	fclose(F);

	return registros;

}

void buscarlibro(char fichero[50]){

	FILE *F;

	struct libros libro;

	int contador=0;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el archivo.\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_SET);

	char busqueda[100];
	printf("Introduce que libro quieres buscar:\n");
	setbuf(stdin,NULL);
	fgets(busqueda,100,stdin);

	if(busqueda[strlen(busqueda)-1]=='\n'){

		busqueda[strlen(busqueda)-1]='\0';

	}


	while((fread(&libro,sizeof(struct libros),1,F))==1){

		if(strcmp(busqueda,libro.titulo)==0){

			contador++;

		}

	}

	if(contador>0){

		printf("Se ha encontrado el libro\n");

	}

	else{

		printf("No se ha encontrado el libro\n");
	}

	fclose(F);

}

	void nuevolibro(char fichero[50]){

		FILE *F;

		struct libros libro;

		if((F=(fopen(fichero,"a+b")))==NULL){

			printf("Error al abrir el archivo.\n");
			exit(-1);

		}

		fseek(F,0L,SEEK_END);

		printf("Introduce un nuevo libro:\n");

		printf("Introduce el título:\n");
		setbuf(stdin,NULL);
		fgets(libro.titulo,100,stdin);

		if(libro.titulo[strlen(libro.titulo)-1]=='\n'){

			libro.titulo[strlen(libro.titulo)-1]='\0';

		}

		printf("Introduce el autor:\n");
		scanf("%s",libro.autor);

		printf("Introduce el precio\n");
		scanf("%f",&libro.precio);

		printf("Introduce la cantidad:\n");
		scanf("%d",&libro.cantidad);



		fwrite(&libro, sizeof(struct libros),1,F);

		fflush(F);

		fclose(F);

	}


void listarlibros(char fichero[50]){

	FILE *F;

	struct libros *v=NULL;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Ha ocurrido un error al abrir el fichero\n");
		exit(-1);

	}

	int cantidad=librosdiferentes(fichero);

	v=(reservarmemoria(cantidad));

	rellenarmemoria(v,fichero);

	imprimirmemoria(v,cantidad);

	free(v);

	fclose(F);

}

struct libros *reservarmemoria(int cantidad){

	struct libros *v=NULL;

	if((v=((struct libros*)malloc(cantidad*sizeof(struct libros))))==NULL){

		printf("Ha ocurrido un error al reservar memoria.\n");
		exit(-1);

	}

	return v;

}

void rellenarmemoria(struct libros *v,char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"rb"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	struct libros libro;
	int contador=0;

	while((fread(&libro,sizeof(struct libros),1,F))==1){

		strcpy(v[contador].titulo,libro.titulo);

		strcpy(v[contador].autor,libro.autor);

		v[contador].precio=libro.precio;

		v[contador].cantidad=libro.cantidad;

		contador++;

	}

	fclose(F);

}

void imprimirmemoria(struct libros *v, int cantidad){

	for(int i=0;i<cantidad;i++){

		printf("Titulo=>%s\n", v[i].titulo);
		printf("Autor=>%s\n", v[i].autor);
		printf("Precio=>%f\n", v[i].precio);
		printf("Cantidad=>%d\n", v[i].cantidad);

	}

}

void venderunlibro(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r+b"))==NULL){

		printf("Error al abrir el fichero.\n");
		exit(-1);

	}

	struct libros libro;
	char cadena[100];

	printf("Introduce el libro que vas a vender:\n");
	setbuf(stdin,NULL);
	fgets(cadena,100,stdin);

	if((cadena[strlen(cadena)-1])=='\n'){

		cadena[strlen(cadena)-1]='\0';

	}

	fseek(F,0L,SEEK_SET);

	while((fread(&libro,sizeof(struct libros),1,F))==1){

		if((strcmp(libro.titulo,cadena))==0){

			if(libro.cantidad>0){

				fseek(F,(-1)*sizeof(struct libros),SEEK_CUR);
				libro.cantidad=libro.cantidad-1;
				fwrite(&libro, sizeof(struct libros),1,F);

				fflush(F);

			}

			else{

				printf("No se puede vender ya que no quedan existencias.\n");

			}

		}

	}

	fclose(F);

}

void borrarregistros(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"rb"))==NULL){
	exit(-1);

	}

	FILE *F2;

	if((F2=fopen("aux","wb"))==NULL){
	exit(-1);

	}

	struct libros libro;

	while((fread(&libro,sizeof(struct libros),1,F))==1){

		if(libro.cantidad!=0){

			fwrite(&libro,sizeof(struct libros),1,F2);
			fflush(F2);

		}

	}

	fclose(F);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);

}


