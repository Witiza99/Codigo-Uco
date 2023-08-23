#include "Agenda.h"

void Agenda::ModificarLider(int equipo, int n){
  list <Alumno> aux=BuscarAlumno(equipo,5);
  list <Alumno>::iterator j=alumnos_.begin();
  if(n==1){
    while(j!=alumnos_.end()){
      if(aux.begin()->getDNI()==(*j).getDNI()){
        (*j).setLider(true);
      }
      j++;
    }
  }else{
    while (j!=alumnos_.end()){
      if(equipo==(*j).getEquipo()){
        if(aux.begin()->getLider()==true){
          aux.begin()->setLider(false);
        }
      }
      j++;
    }
  }
}
