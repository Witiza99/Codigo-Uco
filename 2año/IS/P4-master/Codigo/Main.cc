#include "Agenda.h"
#include "Profesor.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
  int salir=0;
  int eleccion;
  list <Alumno> aux;
  int elec;
  string cadena;
  string Usuario;
  string Contrasena;
  int nomap;
  int asc;
  int vista;
  Agenda a;
  Profesor p;

  while(salir!=2){
    cout<<"Introduzca su usuario"<<endl;
    cin>>Usuario;
    cout<<"Introduzca su contraseña"<<endl;
    cin>>Contrasena;
    if (!p.Identificacion(Usuario,Contrasena)) {
      cout << "El usuario o la contraseña no son correctos, introdúzcalos de nuevo" << '\n';
    }else{
      salir=2;
    }
  }
  cout << "Bienvenido" << '\n';

  p.CargarInformacion(a);

  while(salir!=1){
    cout << "¿Qué quiere hacer?" << '\n';
    cout << "1. Introducir un alumno" << '\n';
    cout << "2. Mostrar alumnos" << '\n';
    cout << "3. Modificar un alumno" << '\n';
    cout << "4. Borrar un alumno" << '\n';
    cout << "5. Borrar todos los alumnos" << '\n';
    cout << "6. Guardar información" << '\n';
    cout << "7. Guardar copia de seguridad" << '\n';
    cout << "8. Cargar copia de seguridad" << '\n';
    cout << "9. Modificar su contraseña" << '\n';
    cout << "10. Cerrar sesión" << '\n';
    cin >> eleccion;
    switch(eleccion){
      case 1:
        a.IntroducirAlumno();
      break;

      case 2:
        cout << "Conteste '1' para si o '0' para no" << '\n';
        cout << "¿Quiere mostrar todos los alumnos?" << '\n';
        cin >> elec;
        if(elec==1){
          list <Alumno> aux=a.getAlumnos();
          cout << "Conteste '1' para si o '0' para no" << '\n';
          cout << "¿Quiere ordenarlos?" << '\n';
          cin>>elec;
          if(elec==1){
            //introducir compribacion nomap y asc
            cout<<"Marque '1' para ordenar por nombre o '2' para ordenar por apellido\n";
            cin>>nomap;
            cout<<"Marque '1' para ordenar ascendentemente o '0' para ordenar descendentemente\n";
            cin>>asc;
            a.OrdenarAlumnos(aux, nomap, asc);
            cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
            cin>>vista;
            a.MostrarAlumnos(aux, vista);
          }else{
            cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
            cin>>vista;
            a.MostrarAlumnos(aux, vista);
          }
        }else{
          if(elec==0){
            cout << "¿Por que opción quiere buscar?" << '\n';
            cout << "1. Nombre" << '\n';
            cout << "2. Apellidos" << '\n';
            cout << "3. DNI" << '\n';
            cout << "4. Correo" << '\n';
            cout << "5. Equipo" << '\n';
            cin>>elec;
            switch (elec) {
              case 1:
                cout << "Introduzca el nombre" << '\n';
                cin>>cadena;
                aux=a.BuscarAlumno(cadena, 1);
                if(aux.size()==0)
                  cout << "No existe el alumno" << '\n';
                cout << "Conteste '1' para sí o '0' para no" << '\n';
                cout << "¿Quiere ordenarlos?" << '\n';
                cin>>elec;
                if(elec==1){
                  cout<<"Marque '1' para ordenar ascendentemente o '0' para ordenar descendentemente\n";
                  cin>>asc;
                  a.OrdenarAlumnos(aux, 1, asc);
                  cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                  cin>>vista;
                  a.MostrarAlumnos(aux, vista);
                }else{
                  cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                  cin>>vista;
                  a.MostrarAlumnos(aux, vista);
                }
                break;
              case 2:
                cout << "Introduzca el apellido" << '\n';
                cin>>cadena;
                aux=a.BuscarAlumno(cadena, 2);
                if(aux.size()==0)
                  cout << "No existe el alumno" << '\n';
                cout << "Conteste '1' para sí o '0' para no" << '\n';
                cout << "¿Quiere ordenarlos?" << '\n';
                cin>>elec;
                if(elec==1){
                  cout<<"Marque '1' para ordenar ascendentemente o '0' para ordenar descendentemente\n";
                  cin>>asc;
                  a.OrdenarAlumnos(aux, 2, asc);
                  cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                  cin>>vista;
                  a.MostrarAlumnos(aux, vista);
                }else{
                  cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                  cin>>vista;
                  a.MostrarAlumnos(aux, vista);
                }
                break;
              case 3:
                cout << "Introduzca el DNI" << '\n';
                cin>>cadena;
                aux=a.BuscarAlumno(cadena, 3);
                if(aux.size()==0){
                  cout << "No existe el alumno" << '\n';
                }
                cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                cin>>vista;
                a.MostrarAlumnos(aux, vista);
                break;
              case 4:
                cout << "Introduzca el correo" << '\n';
                cin>>cadena;
                aux=a.BuscarAlumno(cadena, 4);
                if(aux.size()==0){
                  cout << "No existe el alumno" << '\n';
                }
                cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                cin>>vista;
                a.MostrarAlumnos(aux, vista);
              break;
              case 5:
                cout << "Introduzca el equipo" << '\n';
                cin>>cadena;
                aux=a.BuscarAlumno(cadena, 5);
                if(aux.size()==0){
                  cout << "No existe el alumno" << '\n';
                }
                cout<<"Introduzca '0' para ver un resumen o '1' para ver toda la información\n";
                cin>>vista;
                a.MostrarAlumnos(aux, vista);
              break;
              default:
              cout<<"Opción no válida\n";
            }
          }else{
            cout << "Opción no válida" << '\n';
          }
        }
      break;

      case 3:
        cout << "¿Por que opción quiere buscar?" << '\n';
        cout << "1. Nombre" << '\n';
        cout << "2. Apellidos" << '\n';
        cout << "3. DNI" << '\n';
        cout << "4. Correo" << '\n';
        cin>>elec;
        switch(elec){
          case 1:
            cout<<"Introduzca el nombre\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 1);
            if(aux.size()!=1)
              cout<<"Hay mas de un alumno con el mismo nombre, busque por otra opción\n";
            else{
              a.ModificarAlumno(aux);
              a.MostrarAlumnos(aux, 1);
            }
          break;
          case 2:
            cout<<"Introduzca el primer apellido\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 2);
            if(aux.size()!=1)
              cout<<"Hay mas de un alumno con el mismo apellido, busque por otra opción\n";
            else
              a.ModificarAlumno(aux);
          break;
          case 3:
            cout<<"Introduzca el DNI\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 3);
            a.ModificarAlumno(aux);
          break;
          case 4:
            cout<<"Introduzca el correo\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 4);
            a.ModificarAlumno(aux);
          break;

          default:
            cout<<"opción no válida\n";
        }
      break;

      case 4:
        cout << "¿Por que opción quiere buscar?" << '\n';
        cout << "1. Nombre" << '\n';
        cout << "2. Apellidos" << '\n';
        cout << "3. DNI" << '\n';
        cout << "4. Correo" << '\n';
        cin>>elec;
        switch(elec){
          case 1:
            cout<<"Introduzca el nombre\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 1);
            if(aux.size()!=1)
              cout<<"Hay mas de un alumno con el mismo nombre busque por otra opción";
            else
              a.BorrarAlumno(aux);
          break;
          case 2:
            cout<<"Introduzca el primer apellido\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 2);
            if(aux.size()!=1)
              cout<<"Hay mas de un alumno con el mismo apellido busque por otra opción";
            else
              a.BorrarAlumno(aux);
          break;
          case 3:
            cout<<"Introduzca el DNI\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 3);
            a.BorrarAlumno(aux);
          break;
          case 4:
            cout<<"Introduzca el correo\n";
            cin>>cadena;
            aux=a.BuscarAlumno(cadena, 4);
            a.BorrarAlumno(aux);
          break;

          default:
            cout<<"opción no válida\n";
        }
      break;

      case 5:
        cout << "Conteste '1' para si o '0' para no" << '\n';
        cout<<"¿Esta seguro que quiere borrar todos los alumnos?\n";
        cin>>elec;
        if (elec==1) {
          a.BorrarTodos();
        }else{
          if (elec==0) {
            cout<<"Ha marcado 'no'\n";
          }else{
            cout<<"Opción no válida\n";
          }
        }

      break;

      case 6:
        cout << "Conteste '1' para si o '0' para no" << '\n';
        cout<<"¿Esta seguro que quiere guardar la información?\n";
        cin>>elec;
        if (elec==1) {
          p.GuardarInformacion(a);
        }else{
          if (elec==0) {
            cout<<"Ha marcado 'no'\n";
          }else{
            cout<<"Opción no válida\n";
          }
        }
      break;

      case 7:
        if(p.getCoordinador()){
          cout << "Conteste '1' para si o '0' para no" << '\n';
          cout<<"¿Esta seguro que quiere guardar una copia de seguridad?\n";
          cin>>elec;
          if (elec==1) {
            p.GuardarInfoCs(a);
          }else{
            if (elec==0) {
              cout<<"Ha marcado 'no'\n";
            }else{
              cout<<"Opción no válida\n";
            }
          }
        }else{
          cout<<"Solo los coordinadores tienen acceso a esta opción\n";
        }
      break;

      case 8:
        if(p.getCoordinador()){
          cout << "Conteste '1' para si o '0' para no" << '\n';
          cout<<"¿Esta seguro que quiere cargar una copia de seguridad?\n";
          cin>>elec;
          if (elec==1) {
            p.CargarInfoCs(a);
          }else{
            if (elec==0) {
              cout<<"Ha marcado 'no'\n";
            }else{
              cout<<"Opción no válida\n";
            }
          }
        }else{
          cout<<"Solo los coordinadores tienen acceso a esta opción\n";
        }
      break;

      case 9:
        cout << "Conteste '1' para si o '0' para no" << '\n';
        cout<<"¿Esta seguro que quiere modificar su contraseña?\n";
        cin>>elec;
        if (elec==1) {
          string cadena;
          cout<<"Introduzca su nueva contraseña\n";
          cin>>cadena;
          p.ModificarContrasena(cadena);
        }else{
          if (elec==0) {
            cout<<"Ha marcado 'no'\n";
          }else{
            cout<<"Opción no válida\n";
          }
        }
      break;

      case 10:
        cout << "Conteste '1' para si o '0' para no" << '\n';
        cout<<"¿Esta seguro que quiere cerrar sesión?\n";
        cin>>elec;
        if (elec==1) {
          p.CerrarSesion(a);
          salir=1;
        }else{
          if (elec==0) {
            cout<<"Ha marcado 'no'\n";
          }else{
            cout<<"Opción no válida\n";
          }
        }
      break;
      default:
        cout << "Opción no válida, vuelva a intentarlo" << '\n';
    }
  }
}
