#include <stdio.h>

int func_div(int a, int b){

	a=a-b;

	if(a<0){return 0;}

	else{

		return (1+func_div(a, b));

	}

}

int main(){

	int a=12;
	int b=3;
	int resultado;

	resultado=func_div(a,b);

	printf("Su resultado es: %d\n", resultado);

	return 0;
}