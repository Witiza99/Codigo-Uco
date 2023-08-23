#define <stdio.h>

int **reservarMemoria(int nFil,int nCol){

	int **matriz;

	if((matriz=(float**)malloc(nFil*sizeof(float*)))==NULL){

		printf("Error en la reserva de memoria(1)\n");
		exit(-1);

	}

	for (int i=0;i<nFil;i++){

		if(((*matriz)[i]=(float*)malloc(nCol*sizeof(float)))==NULL){

		printf("Error en la reserva de memoria(2)\n");
		exit(-1);

		}

	}

	return matriz;
}



