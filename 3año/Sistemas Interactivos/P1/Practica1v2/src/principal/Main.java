/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package principal;
import java.util.Scanner;

/**
 *
 * @author Antonio
 */
public class Main {
    
    public static void main(String args[]){
    
        int valor = 0;
        double sol;
        int contador = 0;

        while(contador == 0){
            Scanner teclado = new Scanner(System.in);
            System.out.println("Introduzca un número para calcular su factorial");
            try{        
            valor = Integer. parseInt(teclado.nextLine());
            contador++;
            }catch( NumberFormatException e ){
              System.out.println("No se ha introducido un numero o no es correcto");
            }  
        }    

        sol = Operadores.factorial(valor);
        
        if(sol>0){
            System.out.println("El resultado del factorial de "+valor+" es: "+sol);
        }else{
            System.out.println("No se puede calcular el factorial de un número negativo");
        }

        

        Datos_Aleatorios Datos = new Datos_Aleatorios();

        Profesor inst_profesor = new Profesor(Datos.nombre_Random(), Datos.apellidos_Random(), Datos.edad_Random(),
                Datos.universidad_Random(), Datos.idProfesor_Random());

        System.out.println("El profesor "+inst_profesor.getNombre()+" "+inst_profesor.getApellidos()+" con la edad de "
                +inst_profesor.getEdad()+" años, trabaja en la universidad "+inst_profesor.getUniversidad()+" y tiene el id de profesor "
                +inst_profesor.getId_profesor()+".");
    }
}
