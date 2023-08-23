#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Alumno{
	
	string dni;
	int edad;
	float nota;

};

void nuevo_alumno(Alumno alumnos[10],int nmatriculados){

	cout<<"Introduzca DNI, edad y nota del alumno: "<<endl;

	cin>>alumnos[nmatriculados].dni;

	cin>>alumnos[nmatriculados].edad;

	cin>>alumnos[nmatriculados].nota;

}

void imprimir_datos(Alumno alumnos[10], string persona, int nmatriculados){

	int ayuda=0;

	for(int i=0; i<nmatriculados;i++){

		if (persona==alumnos[i].dni){

			cout<<"DNI: "<<alumnos[i].dni<<endl;

			cout<<"Edad: "<<alumnos[i].edad<<endl;

			cout<<"Nota: "<<alumnos[i].nota<<endl;

			ayuda=ayuda+1;

		}

	}

	if(ayuda==0){cout<<"Este DNI no pertenece a ningun alumno."<<endl;}

}

void print_all(Alumno alumnos[10], int nmatriculados){

	for(int i=0; i<nmatriculados; i++){
	
		cout<<"DNI: "<<alumnos[i].dni<<endl;

		cout<<"Edad: "<<alumnos[i].edad<<endl;

		cout<<"Nota: "<<alumnos[i].nota<<endl;

	}

}

void modf_alumno(Alumno alumnos[10], int nmatriculados, string persona2){

	int ayuda=0;

	for(int i=0; i<nmatriculados;i++){

		if (persona2==alumnos[i].dni){

			cout<<"Introduzca el nuevo DNI: "<<endl;
			cin>>alumnos[i].dni;

			cout<<"Introcuzca la nueva edad: "<<endl;
			cin>>alumnos[i].edad;

			cout<<"Introduzca la nueva nota: "<<endl;
			cin>>alumnos[i].nota;

			ayuda=ayuda+1;

		}

	}if(ayuda==0){cout<<"Este DNI no pertenece a ningun alumno."<<endl;}

}

void eliminar_alumno(Alumno alumnos[10], int nmatriculados, string persona3){

	int ayuda=0;

	for(int i=0; i<nmatriculados;i++){

		if (persona3==alumnos[i].dni){

			alumnos[i].dni="vacio";

			alumnos[i].edad=0;

			alumnos[i].nota=0;


			ayuda=ayuda+1;

		}

	}if(ayuda==0){cout<<"Este DNI no pertenece a ningun alumno."<<endl;}

}


int main(){
	
	int salida=0;

	Alumno alumnos[10];//se crea vector

	int nmatriculados=0;//ayuda para controlar los que se matriculan

	int opcionesmenu;//apoyo para moverme por el menu

	do{

		cout<<"Elige la opcion del menu: "<<endl;

		cout<<"1. Nuevo alumno:"<<endl;

		cout<<"2. Imprimir datos de alumno: "<<endl;

		cout<<"3. Imprimir datos de todos los alumnos: "<<endl;

		cout<<"4. Modificar alumno: "<<endl;

		cout<<"5. Eliminar alumno"<<endl;

		cout<<"6. Salir"<<endl;

		cin>>opcionesmenu;

		switch(opcionesmenu){

			case 1: {

				nuevo_alumno(alumnos, nmatriculados);
				nmatriculados++;

			}break;

			case 2: {

				string persona;
				cout<<"Introduce el DNI del alumno: "<<endl;
				cin>>persona;

				imprimir_datos(alumnos, persona, nmatriculados);

			}break;

			case 3: {

				print_all(alumnos, nmatriculados);

			}break;

			case 4: {

				string persona2;
				cout<<"Introduce el DNI del alumno: "<<endl;
				cin>>persona2;

				modf_alumno(alumnos, nmatriculados, persona2);

			}break;

			case 5: {

				string persona3;
				cout<<"Introduce el DNI del alumno que desea eliminar: "<<endl;
				cin>>persona3;

				eliminar_alumno(alumnos, nmatriculados, persona3);

			}break;

			case 6: {

				salida=1;
			
			}break;

		}

	}while (salida!=1);

	cin.get();
	cin.ignore();

}

