#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define TAM_VECTOR 1000000


int Vector[TAM_VECTOR];

MPI_Status status;

int main (int argc, char *argv[]) {

	srand (time(NULL)); 
	double start_t, end_t, total_t;

	int numeroTareas, idtarea, numtrabajadores, TamSeg, offset;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &idtarea);
	MPI_Comm_size(MPI_COMM_WORLD, &numeroTareas);

	numtrabajadores = numeroTareas - 1;

	/*------------------------------maestro------------------------------------*/

	if (idtarea == 0) {

		//relleno las matrices con valores aleatorios 
		for(int i=0;i<TAM_VECTOR;i++){
			Vector[i]= rand() % 10000;
		}

		//paralelo
		printf("Realizando ordenacion del vector en paralelo: \n");
	 
		//enviamos la matriz de datos a los esclavos para realizar las tareas
		TamSeg = TAM_VECTOR/numtrabajadores;
 		offset = 0;

 		start_t = clock();

		for (int dest=1; dest <= numtrabajadores; dest++){
			MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&TamSeg, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
			MPI_Send(&Vector[offset], TamSeg, MPI_INT,dest,1, MPI_COMM_WORLD);
			offset = offset + TamSeg;
		}

		/* espera los resultados de las tareas */
		for (int i=1; i<=numtrabajadores; i++){
			MPI_Recv(&offset, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&TamSeg, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&Vector[offset], TamSeg, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
		}

		end_t = clock();

		total_t = (end_t - start_t) / CLOCKS_PER_SEC;

		printf("Tiempo total de CPU para paralelizacion: %f\n", total_t  );

	}

	/*------------------------------trabajador------------------------------------*/

	if (idtarea > 0) {
		MPI_Recv(&offset, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&TamSeg, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&Vector, TamSeg, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

		//ordenacion del vector
		int x,y,tmp;
		for(x = 1; x < TamSeg; x++) {
			for(y = 0; y < TamSeg - x; y++) {
				if(Vector[y] > Vector[y + 1]) {
					tmp = Vector[y];
					Vector[y] = Vector[y + 1];
					Vector[y + 1] = tmp;
				}
			}
		}

		MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&TamSeg, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&Vector, TamSeg, MPI_INT, 0, 2, MPI_COMM_WORLD);
	}

	MPI_Finalize();

	return(0);
}