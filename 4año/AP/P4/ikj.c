#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAMMATRIZ 4000
#define ITERACIONES_MATRICES 4000


float A[TAMMATRIZ][TAMMATRIZ];
float B[TAMMATRIZ][TAMMATRIZ];
float Cparalelo[TAMMATRIZ][TAMMATRIZ];

MPI_Status status;

int main (int argc, char *argv[]) {

	srand (time(NULL)); 
	double start_t, end_t, total_t;

	int numeroTareas, idtarea, numtrabajadores, TamSeg, offset, dest;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &idtarea);
	MPI_Comm_size(MPI_COMM_WORLD, &numeroTareas);

	numtrabajadores = numeroTareas - 1;

	/*------------------------------maestro------------------------------------*/

	if (idtarea == 0) {

		//relleno las matrices con valores aleatorios 
		for(int i=0;i<ITERACIONES_MATRICES;i++){
			for(int j=0;j<ITERACIONES_MATRICES;j++){
				A[i][j]= rand() % 10000;
				B[i][j]= rand() % 10000;
				Cparalelo[i][j]= 0;
			}
		}

		//paralelo
		printf("Realizando multiplicacion en paralelo: \n");
	 
		//enviamos la matriz de datos a los esclavos para realizar las tareas
		TamSeg = ITERACIONES_MATRICES/numtrabajadores;
 		offset = 0;

 		start_t = clock();

		for (dest=1; dest <= numtrabajadores; dest++){
			MPI_Send(&offset, 1, MPI_FLOAT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&TamSeg, 1, MPI_FLOAT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&A[offset][0], TamSeg*ITERACIONES_MATRICES, MPI_FLOAT,dest,1, MPI_COMM_WORLD);
			MPI_Send(&B, ITERACIONES_MATRICES*ITERACIONES_MATRICES, MPI_FLOAT, dest, 1, MPI_COMM_WORLD);
			offset = offset + TamSeg;
		}

		/* espera los resultados de las tareas */
		for (int i=1; i<=numtrabajadores; i++){
			MPI_Recv(&offset, 1, MPI_FLOAT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&TamSeg, 1, MPI_FLOAT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&Cparalelo[offset][0], TamSeg*ITERACIONES_MATRICES, MPI_FLOAT, i, 2, MPI_COMM_WORLD, &status);
		}

		end_t = clock();

		total_t = (end_t - start_t) / CLOCKS_PER_SEC;

		printf("C[0][0]: %f\n", Cparalelo[0][0] );
		printf("Tiempo total de CPU para paralelizacion: %f\n", total_t  );

	}

	/*------------------------------trabajador------------------------------------*/

	if (idtarea > 0) {
		MPI_Recv(&offset, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&TamSeg, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&A, TamSeg*ITERACIONES_MATRICES, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&B, ITERACIONES_MATRICES*ITERACIONES_MATRICES, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);

		//multiplicacion de matrices
		for(int i=0;i<TamSeg;i++){
			for(int k=0;k<ITERACIONES_MATRICES;k++){
				for(int j=0;j<ITERACIONES_MATRICES;j++){
					Cparalelo[i][j]+= A[i][k]*B[k][j];
				}
			}
		}

		MPI_Send(&offset, 1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&TamSeg, 1, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&Cparalelo, TamSeg*ITERACIONES_MATRICES, MPI_FLOAT, 0, 2, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return(0);
}