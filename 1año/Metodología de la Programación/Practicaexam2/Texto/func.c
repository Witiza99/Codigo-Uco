#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "func.h"
#include <ctype.h>

int contarlibros(char fichero[50]){

	FILE*F;

	if((F=(fopen(fichero,"r")))==NULL){

		printf("Error al abrir el fichero\n");
		exit(-1);

	}

	int contador=0;

	char cadena[100];

	while((fgets(cadena,100,F))!=NULL){

		if((fgets(cadena,100,F))!=NULL){

			if((fgets(cadena,100,F))!=NULL){

				contador++;

			}

		}

	}

	fclose(F);

	return contador;

}

void nuevolibro(char fichero[50]){

	FILE*F;

	if((F=(fopen(fichero,"a")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	printf("Introduce los datos del nuevo libro:titulo,autor,precio y cantidad\n");

	struct libros libro;

	setbuf(stdin,NULL);
	fgets(libro.titulo,50,stdin);

	if((libro.titulo[strlen(libro.titulo)-1])=='\n'){

		libro.titulo[strlen(libro.titulo)-1]='\0';

	}

	libro.titulo[0]=toupper(libro.titulo[0]);

	scanf("%s",libro.autor);
	scanf("%f",&libro.precio);
	scanf("%d",&libro.cantidad);

	fprintf(F,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.cantidad);

	fclose(F);

}

int buscarlibro(char fichero[50],char busqueda[50]){

	FILE*F;

	if((F=(fopen(fichero,"r")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	int contador=0;

	char cadena[100];

	while((fgets(cadena,100,F))!=NULL){

		if(cadena[strlen(cadena)-1]=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		if((strcmp(cadena,busqueda))==0){

			if((strstr(cadena,busqueda))!=NULL);

				contador++;

		}

	}

	fclose(F);

	return contador;

}

void listarlibros(char fichero[50]){

	struct libros *v=NULL;

	int cantidad=0;

	cantidad=(contarlibros(fichero));

	v=reservarmemoria(&cantidad);

	rellenarmemoria(fichero,v);

	imprimirmemoria(v,cantidad);

	free(v);

}

struct libros *reservarmemoria(int *cantidad){

	struct libros *v=NULL;

	if((v=(struct libros *)malloc((*cantidad)*sizeof(struct libros)))==NULL){

		printf("Error al reservar memoria\n");
		exit(-1);

	}

	return v;

}

void rellenarmemoria(char fichero[50],struct libros *v){

	FILE*F;

	if((F=(fopen(fichero,"r")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	char cadena[100];

	int i=0;

	while((fgets(cadena,100,F))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(v[i].titulo,cadena);

		fgets(cadena,100,F);

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(v[i].autor,cadena);

		fscanf(F,"%f %d\n",&v[i].precio,&v[i].cantidad);

		i++;

	}

	fclose(F);

}

void imprimirmemoria(struct libros *v,int cantidad){

	for(int i=0;i<cantidad;i++){

		printf("%s\n",v[i].titulo);
		printf("%s\n",v[i].autor);
		printf("%f %d\n",v[i].precio,v[i].cantidad);

	}

}

void venderlibro(char fichero[50],char busqueda[50]){

	FILE*F1;
	FILE*F2;

	if((F1=(fopen(fichero,"r")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	if((F2=(fopen("aux","w")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	char cadena[100];
	struct libros libro;

	while((fgets(cadena,100,F1))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(libro.titulo,cadena);

		fscanf(F1,"%s",libro.autor);

		fscanf(F1,"%f %d\n",&libro.precio,&libro.cantidad);

		if(strcmp(cadena,busqueda)==0){

			if(strstr(cadena,busqueda)!=NULL){

				if(libro.cantidad>0){

					libro.cantidad=libro.cantidad-1;
	
				}else{printf("No puedes vender algo que no quedan existencias\n");}

			}
	
		}

		fprintf(F2,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.cantidad);
	
	}

	fclose(F1);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);

}

void borrarregistros(char fichero[50]){

	FILE*F1;
	FILE*F2;

	if((F1=(fopen(fichero,"r")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	if((F2=(fopen("aux","w")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	char cadena[100];
	struct libros libro;

	while((fgets(cadena,100,F1))!=NULL){

		if((cadena[strlen(cadena)-1])=='\n'){

			cadena[strlen(cadena)-1]='\0';

		}

		strcpy(libro.titulo,cadena);

		fscanf(F1,"%s",libro.autor);

		fscanf(F1,"%f %d\n",&libro.precio,&libro.cantidad);

		if(libro.cantidad!=0){

			fprintf(F2,"%s\n%s\n%f %d\n",libro.titulo,libro.autor,libro.precio,libro.cantidad);

		}

	}

	fclose(F1);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);

}