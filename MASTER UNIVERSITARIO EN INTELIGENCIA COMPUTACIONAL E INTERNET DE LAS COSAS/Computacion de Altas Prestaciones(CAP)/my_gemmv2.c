#include "include/my_gemm.h"

void my_gemm(float *A, float *B, float *C, size_t m, size_t n, size_t k) {

int ldA, ldB, ldC;
ldA = k;
ldB = n;
ldC = n;  
  //-> PUT HERE YOUR GEMM CODE
	//base_matrix_multiplication(A, B, C, m, n, k);

	//float32x4_t _A,_B, _C,_Atmp, _Btmp;


	for(int i=0; i < m; i++){
		for(int w=0; w < k; w++){
			for(int j=0; j < n; j++){
				Crow(i,j) += Arow(i,w)*Brow(w,j);	
			}
		}
	}
	/*float32x4_t _A,_B, _C, _tmp;


	for(int i=0; i < m; i++){
		for(int w=0; w < k; w++){
			_C = 0;
			for(uint32_t j=0; j < n; j+=4){
				_A = vld1q_f32(&Arow(i,w));
				_B = vld1q_f32(&Brow(w,j));
				_tmp = vmulq_f32(_A,_B);
				_C = vaddq_f32(_C,_tmp);
				vst1q_f32(&Crow(i,j),_C);
				//Crow(i,j) += Arow(i,w)*Brow(w,j);

				
			}
		}
	}*/
	
  //--------------------------------------------------------------------
  //TODO: Remove the sleep instruccion
  //sleep(1);
  //--------------------------------------------------------------------

}
