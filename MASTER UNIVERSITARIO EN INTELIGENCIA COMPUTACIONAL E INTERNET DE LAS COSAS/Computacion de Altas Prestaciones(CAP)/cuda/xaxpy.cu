//Cabeceras útiles
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>

//#include <cuda_utils.h>

/*
all: saxpy

saxpy: saxpy_cuda.o saxpy.o
        g++ -O3 -fopenmp saxpy.o saxpy_cuda.o -o driver_saxPy -I ./ -lm -lcudart -L/usr/local/cuda/lib64/

saxpy_cuda.o:
        nvcc -O3 -c saxpy_cuda.cu 
saxpy.o:
        g++ -O3 -fopenmp -c saxpy.c -lm -I./
clean:
        rm *.o
        rm driver_saxPy
*/

__global__ void my_kernel(float * z, float * y, float * x, int alpha, int vector_len){
	//Rutina Saxpy
	for(int i=0; i < vector_len; i++){
		z[i] = alpha * x[i] + y[i];
	}
}

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
	float *z, *x, *y, *cuda_z, *cuda_x, *cuda_y;
	z = (float *)malloc(vector_len * sizeof(float));
	x = (float *)malloc(vector_len * sizeof(float));
	y = (float *)malloc(vector_len * sizeof(float));
	
	//reserva de memoria en gpu
	cudaMalloc((void**)&cuda_z,(vector_len * sizeof(float)));
	cudaMalloc((void**)&cuda_x,(vector_len * sizeof(float)));
	cudaMalloc((void**)&cuda_y,(vector_len * sizeof(float)));
	if(z ==0 || y == 0 || x ==0 || cuda_z == 0 || cuda_x == 0 || cuda_y == 0)
		printf("Error con la reserva de memoria");

	//inicializamos a 0
	cudaMemset(cuda_z, 0, (vector_len * sizeof(float)));
	cudaMemset(cuda_x, 0, (vector_len * sizeof(float)));
	cudaMemset(cuda_y, 0, (vector_len * sizeof(float)));


	//inicialización de valores por defecto en x e y
	for(int i=0; i < vector_len; i++){
		x[i] = 1;
		y[i] = 1;

	}

	double t0 = dclock();

	//copia de memoria cpu a gpu
	cudaMemcpy(z, cuda_z, (vector_len * sizeof(float)), cudaMemcpyHostToDevice);
	cudaMemcpy(x, cuda_x, (vector_len * sizeof(float)), cudaMemcpyHostToDevice);
	cudaMemcpy(y, cuda_y, (vector_len * sizeof(float)), cudaMemcpyHostToDevice);

	//llamada al kernel
	int blockSize = 1;
	int gridSize = 1;
	
	my_kernel<<<gridSize, blockSize>>>(cuda_z, cuda_y, cuda_x, alpha, vector_len);
	
	//copia de gpu a cpu
	cudaMemcpy(cuda_z, z, (vector_len * sizeof(float)), cudaMemcpyDeviceToHost);
	cudaMemcpy(cuda_x, x, (vector_len * sizeof(float)), cudaMemcpyDeviceToHost);
	cudaMemcpy(cuda_y, y, (vector_len * sizeof(float)), cudaMemcpyDeviceToHost);
	
	//se libera memoria
	free(z);
	free(y);
	free(x);
	cudaFree(cuda_z);
	cudaFree(cuda_y);
	cudaFree(cuda_x);

	double t1 = dclock();
	double tsaxpy = t1 - t0;
	printf("Tiempo rutina saxpy: %.4f\n", tsaxpy);

	double gflops = (vector_len * 2) / (1.0e+9 * tsaxpy);
	
	printf("Gflops-> %.4f\n", gflops);
	
	

	return(0);
}

