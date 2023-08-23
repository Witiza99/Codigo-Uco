/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

/**
 *
 * @author in2gasae
 */
public class Array {
    
    public static void main( String args[] ) {
        
        // Vectores
        int vector[] = new int[5];
        
        for( int i=0; i < 3; i++ ) { 
            vector[i] = 2*i;
        }
        
        for( int i=0; i < 3; i++ ) { 
            System.out.println( "vector[" + i+ "]:" + vector[i] ); 
        }
        
        // Matrices    
	int matriz[][] = new int[3][];  
	matriz[0] = new int[2]; 
	matriz[1] = new int[3]; 
	matriz[2] = new int[4]; 
        
	for( int i=0; i < 3; i++ ) { 
	    for( int j=0; j < matriz[i].length; j++ ) {
		matriz[i][j] = i * j; 
          } 
	}
        
	for( int i=0; i < 3; i++ ) {
	    for( int j=0; j < matriz[i].length; j++ )  {
		System.out.print( matriz[i][j] + " "); 
            }
            System.out.println(); 
	}
        
        
    } 
}
