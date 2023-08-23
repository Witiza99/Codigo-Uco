#include "include/my_gemm.h"
#include <omp.h>

void my_gemm(float *A, float *B, float  *C, size_t M, size_t N, size_t K) {
  
  //-> PUT HERE YOUR GEMM CODE
  //--------------------------------------------------------------------
  //Posiblemente una de las implementaciones más usadas
  size_t n , m, k;
  size_t ldA = K, ldB = N, ldC = N;

  //Order 1
  //for (m = 0; m < M; m++)
    //for (n = 0; n < N; n++)
      //for (k = 0; k < K; k++)
        //Crow(m, n) += Arow(m, k) * Brow(k, n); 

  //Order 2
  //for (n = 0; n < N; n++)
    //for (m = 0; m < M; m++)
      //for (k = 0; k < K; k++)
        //Crow(m, n) += Arow(m, k) * Brow(k, n); 
  
  //Order 3. 
  //Pregunta 1: ¿Porque esta reordenación funciona mejor que las otras dos?
  //Pregunta 2: ¿Realmente es óptima?
  /*for (k = 0; k < K; k++)
    for (m = 0; m < M; m++)
      for (n = 0; n < N; n++)
        Crow(m, n) += Arow(m, k) * Brow(k, n);*/
  //--------------------------------------------------------------------
  for (m = 0; m < M; m++)
    for (k = 0; k < K; k++)
      for (n = 0; n < N; n++)
        Crow(m, n) += Arow(m, k) * Brow(k, n);

}

void saxpy_gemm(float *A, float *B, float *C, size_t M, size_t N, size_t K) {
  //----------------------------------------------------
  // x0  x4  x8  xC    y0  y4  y8     C(00)x0y0 + x4y1 + x8y2 + xCy3 C(01)x0y4 + x4y5 + x8y6 + xCy7 + C(02) x0y8+ x4y9+ x8yA + xCyB + C(03) x0+x4+x8+xC
  // x1  x5  x9  xD    y1  y5  y9     C(10)x1y0 + x5y1 + x9y2 + xDy3 C(11)x
  // x2  x6  xA  xE X  y2  y6  yA  =  C(20)x2y0 + x6y1 + xAy2 + xEy3 C(21)x
  // x3  x7  xB  xF    y3  y7  yB     C(30)x3y0 + x7y1 + xBy2 + xFy3 C(31)x
  //----------------------------------------------------

  size_t m, n, k;
  //float saxpy; 
  //Leading Dimensions
  size_t ldA, ldB, ldC;
  
  ldA = K;
  ldB = N;
  ldC = N;

  omp_set_num_threads(4);
  __m128 _A, _B, _C;
  //#pragma omp parallel for num_threads(2) collapse(2)
  //#pragma omp parallel
  //#pragma omp parallel//nowait
  #pragma omp parallel for 
  for (m = 0; m < M; ++m) {
    for (k = 0; k < K; ++k){
      _A = _mm_set1_ps(Arow(m,k));
      for(n = 0; n < N; n+=4){
        _B = _mm_load_ps((float*)&Brow(k,n));
        _C = _mm_load_ps((float*)&Crow(m,n));
        _C += _A * _B;
        _mm_store_ps((float*)&Crow(m,n), _C);
      }
    }
  }
}

//Instrucciones SSE de utilidad

// [*]  __m128 // Declaración de variables. Declara un registro vectorial de 4 floats 
// [*]  _mm_load_ps( float *) // Carga 4 floats 
// [*]  _mm_set1_ps(float)    // Fija los 4 valores del registro vectorial iguales al que se le pasa
// [*]  _mm_store_ps(float *, Registro Vectorial) // Almacena los 4 valores del registro vectorial a partir la posición de memoria indicada

// Para operaciones, como si fueran vectores, Ejmp:
// __m128 A, B, C;
// C += A * B;   //Multiplica elemento a elemento los 4 valores de A y B y acumula resultados sobre los 4 valores de C
// C += A * B[0] //Multiplica los 4 elementos de A por el primer elemento del registro vectorial de B. Acumula valores igual que el anterior caso.
//
// Si A = {0, 1, 2, 3}
// Si B = {0, 1, 2, 3}
// Si C = {0, 0, 0, 0}

// Entonces:
// C += A * B    = {0 += 0*0, 0 += 1*1, 0 += 2*2, 0 += 3*3} = {0, 1, 4, 9}
// C += A * B[0] = {0 += 0*0, 0 += 1*0, 0 += 2*0, 0 += 3*0} = {0, 0, 0, 0}
//
// Enlace a las intrinsecas: https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html
// Seleccionar SSE Family!
