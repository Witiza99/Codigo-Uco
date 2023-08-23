//código creado por Antonio Gómez Giménez
//Esta función simula aun procesador que usa el algoritmo RR con quantum 3 (variable) donde se usa un FIFO pero con tiempos limites de cpu (quantum)
#include <stdio.h>
#include <string.h>

#define NPROC 5
#define quantum 3

typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;
    
} parametros;

int main(){
    
    int i;
    int contador=0;
    int tiempo=0;
    
    // Inicialización de los datos de procesos
    parametros procesos[NPROC]; 
    parametros procesos2[NPROC];   
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;
    procesos2[0].t_ejec = 8;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 1;;
    procesos[1].t_com = 0;
    procesos2[1].t_ejec = 4;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;
    procesos[2].t_com = 0;
    procesos2[2].t_ejec = 9;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 3;
    procesos[3].t_com = 0;
    procesos2[3].t_ejec = 5;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 4;
    procesos[4].t_com = 0;
    procesos2[4].t_ejec = 2;

    printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
    printf("-------------------------------------------------------\n");

	while(tiempo<(procesos2[0].t_ejec+procesos2[1].t_ejec+procesos2[2].t_ejec+procesos2[3].t_ejec+procesos2[4].t_ejec)){//el programa sale del bucle cuando el tiempo pasa el tiempo de ejecucion

    	if(contador==0){//esta parte sirve para rellenar los t_com de los procesos
        	procesos[contador].t_com = 0;
        }else{
        	if(procesos[contador].t_com==0){
        		procesos[contador].t_com=tiempo;
        	}
    	}

    	if(procesos[contador].t_ejec!=0){//compruebo que el proceso no esta terminado

    		for(int x=0;x<quantum;x++){//uso el quantum

    			procesos[contador].t_ejec=procesos[contador].t_ejec-1;//resto uno de tiempo de procesamiento
    			tiempo++;

    			if(procesos[contador].t_ejec==0){//miro si termina antes del quantum
    				procesos[contador].t_fin=tiempo;
    				x=quantum;
    			}

    		}
    	}

    	contador++;

    	if(contador==5){contador=0;}//hago que los procesos sean cíclicos

    }

    for(i=0; i< NPROC; i++)//calculo los datos restantes
    {
 
        procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
        procesos[i].t_esp = procesos[i].t_ret - procesos2[i].t_ejec;

    }
    
    for(int j=0; j< NPROC; j++){//imprimo por pantalla

        printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[j].nombre,procesos[j].t_com, procesos[j].t_fin, procesos[j].t_ret, procesos[j].t_esp);

    }
    
}
