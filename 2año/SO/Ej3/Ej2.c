//código creado por Antonio Gómez Giménez
//Esta función simula aun procesador que usa el algoritmo SJF donde va buscando en la cola cual tiene menor tiempo de ejución y lo ejecuta
#include <stdio.h>
#include <string.h>

#define NPROC 5
#define MAX 999999999

typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan  //inicio
    int t_fin;                   //fin
    int t_ret;                   //estancia
    int t_esp;                   //espera
    
} parametros;

int main(){
    
    int i;
    int min=MAX;
    int ant;
    int valor;
    int aux;
    
    // Inicialización de los datos de procesos
    parametros procesos[NPROC];
    parametros procesos2[NPROC-1];    
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;
    procesos2[0].t_ejec = 4;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;
    procesos2[1].t_ejec = 9;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;
    procesos2[2].t_ejec = 5;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 4;
    procesos2[3].t_ejec = 2;

    printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
    printf("-------------------------------------------------------\n");
    for(i=0; i< NPROC; i++)
    {
        if(i==0){
            procesos[i].t_com = 0;
            ant=0;
            valor=0;
        }
        else {

            for(int j=0;j<(NPROC-1);j++){

                if(procesos2[j].t_ejec<min){
                    min=procesos2[j].t_ejec;//para saber el proceso con el menos tiempo de ejecución
                    aux=j;//permite que si encuentra dos min no machaque el primero
                }
            }
            procesos2[aux].t_ejec=MAX;//no lo permito que pueda volver a salir

            for(int j=1;j<NPROC;j++){

                if(procesos[j].t_ejec==min){
                    valor=j;//para saber el proceso que es
                }
            }
            min=MAX;//vuelvo a poner el mínimo al máximo
            procesos[valor].t_com = procesos[ant].t_fin;
            ant=valor;//guardo el proceso anterior

        }
        procesos[valor].t_fin = procesos[valor].t_com + procesos[valor].t_ejec;//relleno los campos restantes
        procesos[valor].t_ret = procesos[valor].t_fin - procesos[valor].t_lleg;
        procesos[valor].t_esp = procesos[valor].t_ret - procesos[valor].t_ejec;

    }
    
    for(int j=0; j< NPROC; j++){//imprimo los resutados no ordenados sino de A,B,C,D,E

        printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[j].nombre,procesos[j].t_com, procesos[j].t_fin, procesos[j].t_ret, procesos[j].t_esp);

    }
    
}
