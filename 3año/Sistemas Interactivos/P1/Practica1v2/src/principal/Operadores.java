/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package principal;

/**
 *
 * @author Antonio
 */
public class Operadores {
    
    public static double factorial(int valor){     
        if(valor<0){
            return 0;
        }
        if(valor==0){
            return 1;
        }else{
            return valor * (factorial(valor-1));
        }     
    }
}
