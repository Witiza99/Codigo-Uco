
#include <stdlib.h>

int main(){

	int buffer_size = 10;
	float *b = (float *) malloc (sizeof(float) * buffer_size);
	size_t result = 0;
	for (int i= 0; i < buffer_size; i++) b[i] = 1.0;
	for (int i=0; i < buffer_size; i++) result += b[i];

	return(0);
}