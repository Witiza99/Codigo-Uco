#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

int contarlibrosdiferentes(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Hay un error al abrir el fichero.\n");
		exit(-1);

	}

	char cadena[100];

	int contador=0;

	while((fgets(cadena,100,F)!=NULL)){

		if((fgets(cadena,100,F))!=NULL){

			if((fgets(cadena,100,F))!=NULL){

				contador++;

			}

		}

	}

	fclose(F);

	return contador;

}

void existe_libro(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Ha ocurrido un error al abrir el fichero\n");
		exit(-1);

	}

	char cadena[100];
	int contador=0;
	char auxcadena[100];

	printf("Introduce el libro que quieres ver:\n");
	setbuf(stdin,NULL);
	fgets(auxcadena,100,stdin);

	if((auxcadena[strlen(auxcadena)-1])=='\n'){

		auxcadena[strlen(auxcadena)-1]='\0';

	}

	while(fgets(cadena,100,F)!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		if((strcmp(cadena,auxcadena))==0){

			if((strstr(cadena,auxcadena))!=NULL){

				contador++;

			}

		}

	}

	if(contador>0){

		printf("El libro existe.\n");

	}

	else{

		printf("El libro no existe\n");

	}

	fclose(F);

}

void introducir_nuevo(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"a"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	struct libros libro;

	printf("Introduce el titulo:\n");
	setbuf(stdin,NULL);
	fgets(libro.titulo,100,stdin);

	if((libro.titulo[strlen(libro.titulo)-1])=='\n'){

		libro.titulo[strlen(libro.titulo)-1]='\0';

	}

	printf("Introduce el autor:\n");
	scanf("%s",libro.autor);

	printf("Introduce el precio:\n");
	scanf("%f",&libro.precio);

	printf("Introduce el unidades:\n");
	scanf("%d",&libro.unidades);

	fprintf(F,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.unidades);

	fclose(F);

}

void Listarlibros(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	struct libros *v=NULL;

	int cantidad=contarlibrosdiferentes(fichero);

	v=reservarmemoria(cantidad);

	rellenavector(v, fichero);

	imprimevector(v, cantidad);

	free(v);
	fclose(F);

}

struct libros *reservarmemoria(int cantidad){

	struct libros *v=NULL;

	if((v=(struct libros *)malloc(cantidad*(sizeof(struct libros))))==NULL){

		printf("Error al reservar memoria\n");
		exit(-1);

	}

	return v;

}

void rellenavector(struct libros *v, char fichero[100]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	char cadena[100];
	int i=0;

	while((fgets(cadena,100,F))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(v[i].titulo,cadena);

		fscanf(F,"%s\n",v[i].autor);

		fscanf(F,"%f %d\n",&v[i].precio, &v[i].unidades);

		i++;

	}
	
}

void imprimevector(struct libros *v, int cantidad){

	for(int i=0;i<cantidad;i++){

		printf("Titulo->%s\n", v[i].titulo);
		printf("Autor->%s\n", v[i].autor);
		printf("Precio->%f\n", v[i].precio);
		printf("Unidades->%d\n", v[i].unidades);

	}

}

void venderlibro(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	FILE *F2;
	
	if((F2=fopen("aux","w"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	struct libros libro;
	char cadena[100];
	char cad[100];

	printf("Introduce el libro que vas a vender:\n");
	setbuf(stdin,NULL);
	fgets(cad,100,stdin);

	if((cad[strlen(cad)-1])=='\n'){

		cad[strlen(cad)-1]='\0';

	}

	while((fgets(cadena,100,F))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}
		strcpy(libro.titulo,cadena);

		fscanf(F,"%s",libro.autor);

		fscanf(F,"%f %d\n",&libro.precio, &libro.unidades);

		if((strcmp(libro.titulo,cad))==0){

			if((strstr(libro.titulo,cad))!=NULL){

				libro.unidades=libro.unidades-1;

			}

		}

		fprintf(F2,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.unidades);

	}


	fclose(F);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);


}

void borrarlibros(char fichero[50]){

	FILE *F;

	if((F=fopen(fichero,"r"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	FILE *F2;
	
	if((F2=fopen("aux","w"))==NULL){

		printf("Ha ocurrido un error al abrir el archivo.\n");
		exit(-1);

	}

	struct libros libro;
	char cadena[100];

	while((fgets(cadena,100,F))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}
		strcpy(libro.titulo,cadena);

		fscanf(F,"%s",libro.autor);

		fscanf(F,"%f %d\n",&libro.precio, &libro.unidades);

		if(libro.unidades!=0){

			fprintf(F2,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.unidades);

		}

	}


	fclose(F);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);

}	