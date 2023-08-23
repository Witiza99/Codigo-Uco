/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

/**
 *
 * @author in2gasae
 */
public class Excepciones {
    
    public static void main( String args[] ) {
        
        String Saludos[] = {
            "Hola Mundo!",
            "HOLA Mundo!!",
            "HOLA MUNDO!!!"
        };

        try {
            
	   for(int i=0;i<5;i++)
             System.out.println( Saludos[i] );   
           
        } catch( ArrayIndexOutOfBoundsException e ) {
             System.out.println( "Saludos desbordado" );
        } catch( Exception e ) {
             // Cualquier otra excepción
               System.out.println( e.toString() );  
        } finally {
               System.out.println( "Esto se imprime siempre!" );
        }

    }
}
