#include <list>
#include "Alumno.h"
#include "Agenda.h"


list <Alumno> Agenda::BuscarAlumno(string cadena, int elec){
  list <Alumno>:: iterator i=alumnos_.begin();
  list <Alumno> aux;

  switch(elec){

    case 1://Buscar por nombre
      while(i!=alumnos_.end()){
        if((*i).getNombre()==cadena){
          aux.push_back((*i));
        }
        i++;
      }
    break;
    case 2://Buscar por apellido
      while(i!=alumnos_.end()){
        if((*i).getApellido1()==cadena){
          aux.push_back((*i));
        }
        i++;
      }
    break;
    case 3://Buscar por DNI
      while(i!=alumnos_.end()){
        if((*i).getDNI()==cadena){
          aux.push_back((*i));
        }
        i++;
      }
    break;
    case 4://Buscar por correo
      while(i!=alumnos_.end()){
        if((*i).getCorreo()==cadena){
          aux.push_back((*i));
        }
        i++;
      }
    break;
    case 5://Buscar por equipo
      while(i!=alumnos_.end()){
        if(to_string((*i).getEquipo())==cadena){
          aux.push_back((*i));
        }
        i++;
      }
    break;
  }
  return aux;
}
