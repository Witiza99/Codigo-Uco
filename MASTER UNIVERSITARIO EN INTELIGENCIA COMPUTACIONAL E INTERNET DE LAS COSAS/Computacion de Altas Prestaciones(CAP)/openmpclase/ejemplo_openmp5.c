#include <omp.h>
#include <stdio.h>

int main () {
	int thid;
	int a;
	for (int i = 0; i < 10; i++) {
		a= 0;
		omp_set_num_threads(2);
		printf("Itr %d ------------------>\n", i);
		#pragma omp parallel sections firstprivate(a)
		{
			#pragma omp section
			{
				a += 1;
				thid = omp_get_thread_num();
				printf("Section 1 - Thread id=%d, a=%d\n", thid, a);
			}
			#pragma omp section
			{
				a += 1;
				thid = omp_get_thread_num();
				printf("Section 2 - Thread id=%d a=%d\n", thid, a);
			}
		}
	}
}
//OMP_PLACES = {0,4}
//OMP_PROC_BIND = True