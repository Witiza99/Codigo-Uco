//#include <cstdlib>
#include <iostream>

using namespace std;

int menu(){
	int n;
	cout<<"Menu:"<<endl;
	cout<<"1.Insertar Producto"<<endl;
	cout<<"2.Promedio"<<endl;
	cout<<"3.Listar Productos"<<endl;
	cout<<"4.Salir del programa"<<endl;
	cin>>n;
	return n;
}

void insertarProducto(string productos[], int n_productos, float precios[], int n_precios){
	string producto;
	float precio;
	cout<<"Introduzca nuevo producto y su respectivo precio: "<<endl;
	cin>>producto;
	cin>>precio;

	string aux_productos[n_productos+1];	
	float aux_precios[n_precios+1];

	for(int i=0;i<n_productos;i++){
		aux_productos[i]=productos[i];
		aux_precios[i]=precios[i];
	}
	aux_productos[n_productos]=producto;
	aux_precios[n_precios]=precio;

	productos=aux_productos;
	precios=aux_precios;

}

void listarProductos(string productos[], int n_productos, float precios[], int n_precios){
	for(int i=0;i<n_productos;i++){
		cout<<"Producto: "<<productos[i]<<" con precio: "<<precios[i]<<endl;
	}

}

float promedio(float precios[], int n_precios){
	float sum=0;
	for(int i=0;i<n_precios;i++){
		sum=sum+precios[i];
	}
	return sum/n_precios;
}

int main()
{
	int n_productos=0;
	string productos[n_productos];	
	int n_precios=0;//no deberia de existir ya que debo mantener n_precios = n_productos
	float precios[n_precios];
	int aux;

	while(menu()!=4){

		aux=menu();

		switch(aux){
			case 1:
				insertarProducto(productos,n_productos,precios,n_precios);
			break;
			case 2:
				cout<<"El precio promedio de todo el conjunto de productos es: "<<promedio(precios, n_precios)<<endl;
			break;
			case 3:
				listarProductos(productos,n_productos,precios,n_precios);
			break;
			case 4:
				cout<<"Hasta la proxima"<<endl;
			break;
			default:
				cout<<"Numero introducido no apto"<<endl;
			break;
		}
		
	}
	
	return 0;
}