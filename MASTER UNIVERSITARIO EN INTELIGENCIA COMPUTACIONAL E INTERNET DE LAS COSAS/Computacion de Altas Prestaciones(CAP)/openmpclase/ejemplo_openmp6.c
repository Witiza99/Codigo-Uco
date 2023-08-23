#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
	int N = 4;
	int M = 10;
	int *V = (int *)malloc(N*M *sizeof(int));
	omp_set_num_threads(2);
	//paralelizar con 4 hilos for anidados

	#pragma omp parallel for collapse(2)
	for(int i = 0;i<N;i++){
		for(int j=0;j<M;j++){
			V[i*N+j]=1;
			printf("i = %d, j= %d, threadId = %d \n", i, j, omp_get_thread_num());
			printf("Valor V[%d,%d]=%d\n", i,j,V[i*N+j]);
		}
	}
}

//OMP_PLACES = {0,4}
//OMP_PROC_BIND = True