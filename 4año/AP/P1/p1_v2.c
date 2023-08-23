#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main () {

	srand (time(NULL)); 
	double start_t, end_t, total_t;

	float A[512][528];
	float B[512][528];
	float C[512][528];

	for(int i=0;i<512;i++){
		for(int j=0;j<528;j++){
			A[i][j]= rand() % 10000;
			B[i][j]= rand() % 10000;
			C[i][j]= 0;
		}
	}

	start_t = clock();
	for(int i=0;i<512;i++){
		for(int k=0;k<512;k++){
			for(int j=0;j<512;j++){
				C[i][j]+= A[i][k]*B[k][j];
			}
		}
	}

	end_t = clock();

	total_t = (end_t - start_t) / CLOCKS_PER_SEC;
	printf("C[0][0]: %f\n", C[0][0] );
	printf("Total time taken by CPU: %f\n", total_t  );

	return(0);
}