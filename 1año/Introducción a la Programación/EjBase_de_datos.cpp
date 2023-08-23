#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

struct Alumno{//structura alumno que me servira para todo el programa
	
	string dni;
	int edad;
	float nota;

};

int digitos(string persona){//esta funcion comprueba los digitos que tiene la frase

	int contador=0;

	for(unsigned i=0; i<persona.size(); i++){

		if (isdigit(persona[i])==true)	{contador=contador+1;}//compruebo uno a uno si son digitos o no y los voy almacenado

	}

return contador;

}

void convierte_a_cadena(string &persona){//esta funcion transforma la cadena de caracteres en minuscula a mayuscula

	persona[8]=toupper(persona[8]);//aqui utilizo la funcion toupper que transforma ls letra en minuscula en mayuscula

}


bool comprobarDNI(string &persona){

	int fail=0;

	string vector_letras="TRWAGMYFPDXBNJZSQVHLCKE";

	if (persona.size()==9){//compruebo tamaño //1corchete

		if((digitos(persona)==8)&&(isdigit(persona[8])==0)){//compruebo 8 digitos y la letra en el ultimo lugar //2 corchete

			convierte_a_cadena(persona);//llamo a funcion que me transforma la letra minuscula a mayuscula

			string numeroDNI;

			for(int i=0; i<(persona.size()-1); i++){//almaceno solo numeros
			
				numeroDNI[i]=persona[i];

			}

			int numero_DNI=stoi(numeroDNI);

			char letra=vector_letras[numero_DNI % 23 ];

			if (letra==persona[8]){return true; //compruebo si la letra es correcta //3corchete
			
			}else {fail=fail+1;}//3corchete

		}else {fail=fail+1;}//2 corchete

	}else {fail=fail+1;} //1corchete

	if(fail>0){return false;}

}



void nuevo_alumno(Alumno alumnos[10],int nmatriculados){//primera funcion que crea los datos para un alumno

	cout<<"Introduzca DNI, edad y nota del alumno: "<<endl;

	cin>>alumnos[nmatriculados].dni;

	cin>>alumnos[nmatriculados].edad;

	cin>>alumnos[nmatriculados].nota;

}

void imprimir_datos(Alumno alumnos[10], string persona, int nmatriculados){//segunda funcion que me imprime los datos de un alumno

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

void print_all(Alumno alumnos[10], int nmatriculados){//tercera funcion que me imprime por pantalla todos los datos

	for(int i=0; i<nmatriculados; i++){
	
		cout<<"DNI: "<<alumnos[i].dni<<endl;

		cout<<"Edad: "<<alumnos[i].edad<<endl;

		cout<<"Nota: "<<alumnos[i].nota<<endl;

	}

}

void modf_alumno(Alumno alumnos[10], int nmatriculados, string persona2){//cuarta funcion que me modifica los datos de un alumno

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

void eliminar_alumno(Alumno alumnos[10], int nmatriculados, string persona3){//quinta funcion que me permite eliminar a un alumno

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

	Alumno alumnos[10];//se crea vector

	int nmatriculados=0;//ayuda para controlar los que se matriculan

	int opcionesmenu=1;//apoyo para moverme por el menu

	while((opcionesmenu>0) && (opcionesmenu<6)){//este while me permite salir del menu una vez que se eliga su salida o el usuario se equivoque de numero

		cout<<"Elige la opcion del menu: "<<endl;

		cout<<"1. Nuevo alumno:"<<endl;

		cout<<"2. Imprimir datos de alumno: "<<endl;

		cout<<"3. Imprimir datos de todos los alumnos: "<<endl;

		cout<<"4. Modificar alumno: "<<endl;

		cout<<"5. Eliminar alumno"<<endl;

		cout<<"6. Salir"<<endl;

		cin>>opcionesmenu;

		switch(opcionesmenu){//en este switch se entra en cada uno de los casos del menu, en su respetiva funcion

			case 1: {

				nuevo_alumno(alumnos, nmatriculados);
				nmatriculados++;

			}break;

			case 2: {

				string persona;
				cout<<"Introduce el DNI del alumno: "<<endl;
				cin>>persona;

				if(comprobarDNI(persona)==true){imprimir_datos(alumnos, persona, nmatriculados);}

				else{cout<<"El DNI es erroneo"<<endl;}

			}break;

			case 3: {

				print_all(alumnos, nmatriculados);

			}break;

			case 4: {

				string persona2;
				cout<<"Introduce el DNI del alumno: "<<endl;
				cin>>persona2;

				if(comprobarDNI(persona2)==true){modf_alumno(alumnos, nmatriculados, persona2);}

				else{cout<<"El DNI es erroneo"<<endl;}
				
			}break;

			case 5: {

				string persona3;
				cout<<"Introduce el DNI del alumno que desea eliminar: "<<endl;
				cin>>persona3;

				if(comprobarDNI(persona3)==true){eliminar_alumno(alumnos, nmatriculados, persona3);}

				else{cout<<"El DNI es erroneo"<<endl;}

			}break;

		}

	}

	cin.get();
	cin.ignore();

}

