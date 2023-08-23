#include <stdio.h>
#include <stdlib.h>
#include <time.h>

	float **reservamemoriamatriz(int nFil,int nCol){

		int **m=NULL;

		if((m=((int **)malloc((nFil)*sizeof(int*))))==NULL){

			printf("Fallo al reservar memoria\n");
			exit(-1);

		}

		for(int i=0;i<(nCol);i++){

		if((m[i]=((int*)malloc((nCol)*sizeof(int))))==NULL){

				printf("Fallo al reservar memoria\n");
				exit(-1);

			}

		}

		return m;

	}

	void rellenamatriz(int **m,int *nFil,int *nCol){

		srand(time(NULL));

		for(int i=0;i<(*nFil);i++){

			for(int j=0;j<(*nCol);j++){

				m[i][j]=rand()%21;

			}

		}

	}

	void imprimematriz(int **m,int *nFil,int *nCol){

		for(int i=0;i<(*nFil);i++){

			for(int j=0;j<(*nCol);j++){

				printf("%d\n",m[i][j]);

			}

		}

	}

	float *numerospequenos(int **m, int *nFil,int *nCol){

		int *v=NULL;

		int menor;

		if((v=((int*)malloc((*nFil)*sizeof(int))))==NULL){

			printf("Error al reservar memoria\n");

		}

		for(int i=0;i<(*nFil);i++){

			menor=m[0][i];

			for(int j=0;j<(*nCol);j++){

				if(m[i][j]<menor){menor=m[i][j];}

			}

			v[i]=menor;

		}

		return v;

	}

	void imprime(int *v,int *nFil){

		for(int i=0;i<(*nFil);i++){

			printf("%d\n",v[i]);

		}

	}

	void liberamemoria(int ***m,int **v, int *nCol){

		for(int i=0;i<(*nCol);i++){

			free(m[i]);

		}

		free(v);

		free(m);

	}