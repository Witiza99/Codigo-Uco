/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package principal;

/**
 *
 * @author i72gogia
 */
public class Operadores {
    
    public static double suma(double valor1, double valor2){  
        double number=valor1+valor2;
        return Math.round(number * 100000d) / 100000d;
    }
    
    public static double resta(double valor1, double valor2){     
        double number=valor1-valor2;
        return Math.round(number * 100000d) / 100000d;
    }
    
    public static double multiplicacion(double valor1, double valor2){     
        double number=valor1*valor2;
        return Math.round(number * 100000d) / 100000d;
    }
    
    public static double division(double valor1, double valor2){     
        double number=valor1/valor2;
        return number;
    }
    
    public static double mod(double valor1, double valor2){
        if(valor1==0){
            return 0;
        }else{
            double number=valor1%valor2;
            return Math.round(number * 100000d) / 100000d;
        }
    }
      
}
