/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

/**
 *
 * @author in2gasae
 */
public class ClaseBase {
    int mivar; 

    public ClaseBase() { 
	mivar = 10;  
    } 

    public ClaseBase(int valor) { 
	mivar = valor; 
    } 

    public void Suma( int j ) { 
	mivar += j; 
    }     
    
    public int getVar() {
        return mivar;
    }
    
    public void setVar(int valor) {
        mivar = valor;
    }
}
