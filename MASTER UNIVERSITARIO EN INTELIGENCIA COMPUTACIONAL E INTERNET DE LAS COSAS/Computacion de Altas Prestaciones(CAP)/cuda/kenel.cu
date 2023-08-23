
__global__ void my_kernel(float * z, float * y, float * x, int alpha, int vector_len){
	//Rutina Saxpy
	for(int i=0; i < vector_len; i++){
		z[i] = alpha * x[i] + y[i];
	}
}
