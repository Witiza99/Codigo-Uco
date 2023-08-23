/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

/**
 *
 * @author in2gasae
 */
public class MiClaseBase extends ClaseBase {
   public static void main(String args[]) { 
       
	MiClaseBase minuevaclase = new MiClaseBase(50); 
	minuevaclase.Suma(10); 
    } 

   public MiClaseBase() {
   
   }
   
   public MiClaseBase(int nuevo) {
        setVar(nuevo);
   }
   
    public void Suma( int j ) { 
	super.Suma(j); 
	System.out.println("El valor final de mivar es: " + getVar()); 
    }  
}
