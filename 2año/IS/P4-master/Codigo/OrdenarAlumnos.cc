
#include "Agenda.h"
#include "Alumno.h"

bool MenorNombre(Alumno &a, Alumno &b){
    return a.getNombre() < b.getNombre();
}

bool MayorNombre(Alumno &a, Alumno &b){
    return a.getNombre() > b.getNombre();
}

bool MenorApellidos(Alumno &a, Alumno &b){
    if(a.getApellido1()==b.getApellido1()){
      return a.getApellido2() < b.getApellido2();
  }
    return a.getApellido1() < b.getApellido1();
}

bool MayorApellidos(Alumno &a, Alumno &b){
    if(a.getApellido1()==b.getApellido1()){
      return a.getApellido2() > b.getApellido2();
  }
    return a.getApellido1() > b.getApellido1();
}

bool MenorCurso(Alumno &a, Alumno &b){
  return a.getCurso() < b.getCurso();
};

bool MayorCurso(Alumno &a, Alumno &b){
    return a.getCurso() > b.getCurso();
}

void Agenda::OrdenarAlumnos(list <Alumno> &lista, int elec, int asc){
    switch(elec){
      case 1://Nombre
        if(asc==1){
          lista.sort(MenorNombre);
        }else{
          lista.sort(MayorNombre);
        }
      break;
      case 2://Apellidos
        if(asc==1){
          lista.sort(MenorApellidos);
        }else{
          lista.sort(MayorApellidos);
        }
      break;
      case 4://Curso
        if(asc==1){
          lista.sort(MenorCurso);
        }else{
          lista.sort(MayorCurso);
        }
      break;
    }
}
