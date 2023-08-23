#include <omp.h>
#include <stdio.h>

int main(){
	int n=4;
	
	omp_set_num_threads(n);
	printf("hilos antes = %d\n",omp_get_num_threads());
	#pragma omp parallel for
	for (int i=0; i<n; i++) {
		printf("hilos = %d\n",omp_get_num_threads());
		printf("yo soy %d\n",omp_get_thread_num());
	}
}
