#include "include/my_gemm.h"

void my_gemm(float *A, float *B, float *C, size_t m, size_t n, size_t k) {

int ldA, ldB, ldC;
ldA = k;
ldB = n;
ldC = n;  
  //-> PUT HERE YOUR GEMM CODE
	//base_matrix_multiplication(A, B, C, m, n, k);
	for(int i=0; i < m; i++){
		for(int j=0; j< n; j++){
			for(int w=0; w < k; w++){
				Crow(i,j) += Arow(i,w)*Brow(w,j);
			}
		}
	}
	
  //--------------------------------------------------------------------
  //TODO: Remove the sleep instruccion
  //sleep(1);
  //--------------------------------------------------------------------

}
