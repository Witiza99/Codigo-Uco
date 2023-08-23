//Cabeceras útiles
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <arm_neon.h>

//Rutina temporización (tiempo en segundos)
double dclock() {
	struct timeval tv;
	gettimeofday( &tv, NULL );
	return (double) (tv.tv_sec + tv.tv_usec*1.0e-6);
}

//Programa principal
int main() {
	const size_t vector_len = (32 * 1024 * 1024) / sizeof(float);	

	//Declaración y reserva de memoria (z, y, x)
	float alpha = 2;
	float * z = malloc(vector_len * sizeof(float));
	float * x = malloc(vector_len * sizeof(float));
	float * y = malloc(vector_len * sizeof(float));

	for(int i=0; i < vector_len; i++){
		x[i] = 1;
		y[i] = 1;

	}

	double t0 = dclock();
	//Rutina Saxpy
	for(int i=0; i < vector_len; i++){
		z[i] = alpha * x[i] + y[i];
	}

	double t1 = dclock();
	double tsaxpy = t1 - t0;
	printf("Tiempo rutina saxpy: %.4f\n", tsaxpy);

	double gflops = (vector_len * 2) / (1.0e+9 * tsaxpy);
	
	printf("Gflops-> %.4f\n", gflops);
	
	

	return(0);
}

