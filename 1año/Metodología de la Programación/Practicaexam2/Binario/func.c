#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include <ctype.h>

int contarlibrosdiferentes(char fichero[50]){

	FILE *F;

	int cantidad;

	int total;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el archivo, no existe\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_END);

	cantidad=ftell(F);

	total=cantidad/sizeof(struct libros);

	fclose(F);

	return total;

}

int buscarlibro(char fichero[50],char libropedido[50]){

	FILE*F;

	int contador=0;

	struct libros libro;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el fichero\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_SET);

	while(fread(&libro,sizeof(struct libros),1,F)==1){

		if((strcmp(libro.titulo,libropedido))==0){

			if((strstr(libro.titulo,libropedido))!=NULL){

				contador++;

			}

		}

	}

	fclose(F);

	return contador;

}

void nuevolibro(char fichero[50]){

	FILE *F;

	struct libros libro;

	if((F=(fopen(fichero,"ab")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	fseek(F,0L,SEEK_END);

	printf("Introduce los datos del nuevo libro: titulo, autor, precio y cantidad\n");

	setbuf(stdin,NULL);
	fgets(libro.titulo,50,stdin);

	if(libro.titulo[strlen(libro.titulo)-1]=='\n'){

		libro.titulo[strlen(libro.titulo)-1]='\0';

	}

	libro.titulo[0]=toupper(libro.titulo[0]);

	scanf("%s",libro.autor);
	scanf("%f",&libro.precio);
	scanf("%d",&libro.cantidad);

	fwrite(&libro,sizeof(struct libros),1,F);

	fclose(F);

}

void listarlibros(char fichero [50]){

	FILE*F;

	struct libros *v=NULL;

	int contador=0;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	contador=contarlibrosdiferentes(fichero);

	v=reservarmemoria(contador);

	rellenarvector(fichero,v);

	imprimirvector(v,contador);

	free(v);

	fclose(F);

}

struct libros *reservarmemoria(int contador){

	struct libros *v=NULL;

	if((v=(struct libros*)malloc(contador*sizeof(struct libros)))==NULL){

		printf("Error al reservar memoria para el vector dinamico\n");

	}

	return v;

}

void rellenarvector(char fichero [50],struct libros *v){

	FILE*F;

	int i=0;

	if((F=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	struct libros libro;

	while(fread(&libro,sizeof(struct libros),1,F)==1){

		strcpy(v[i].titulo,libro.titulo);

		strcpy(v[i].autor,libro.autor);

		v[i].precio=libro.precio;

		v[i].cantidad=libro.cantidad;

		i++;
			
	}

	fclose(F);

}

void imprimirvector(struct libros *v,int contador){

	for(int i=0;i<contador;i++){

		printf("%s\n",v[i].titulo);
		printf("%s\n",v[i].autor);
		printf("%f %d\n",v[i].precio,v[i].cantidad);

	}

}

void venderlibro(char fichero[50]){

	FILE*F;

	if((F=(fopen(fichero,"r+b")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	struct libros libro;

	char aux[50];

	printf("Introduce el nombre del libro que desear vender\n");

	setbuf(stdin,NULL);
	fgets(aux,50,stdin);

	if((aux[strlen(aux)-1])=='\n'){

		aux[strlen(aux)-1]='\0';

	}

	if((buscarlibro(fichero,aux))==1){

		fseek(F,0L,SEEK_SET);

		while((fread(&libro,sizeof(struct libros),1,F))==1){

			if(strcmp(libro.titulo,aux)==0){

				if(strstr(libro.titulo,aux)!=NULL){

					if(libro.cantidad>0){

						fseek(F,(-1)*sizeof(struct libros),SEEK_CUR);

						libro.cantidad=libro.cantidad-1;

						fwrite(&libro,sizeof(struct libros),1,F);

						fflush(F);

					}else{printf("No tiene sentido vender algo que no tienes\n");}

				}

			}

		}

	}else{printf("El libro introducido no se ha encontrado\n");}

	fclose(F);

}

void borrarregistros(char fichero[50]){

	FILE*F1;
	FILE*F2;

	if((F1=(fopen(fichero,"rb")))==NULL){

		printf("Error al abrir el archivo\n");
		exit(-1);

	}

	if((F2=(fopen("aux","wb")))==NULL){

		printf("Error al introducir el fichero\n");
		exit(-1);

	}

	struct libros libro;

	while((fread(&libro,sizeof(struct libros),1,F1))==1){

		if(libro.cantidad!=0){

			fwrite(&libro,sizeof(struct libros),1,F2);

			fflush(F2);

		}

	}

	fclose(F1);
	fclose(F2);

	remove(fichero);
	rename("aux",fichero);

}

