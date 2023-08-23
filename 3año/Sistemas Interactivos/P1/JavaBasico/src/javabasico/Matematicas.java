/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

/**
 *
 * @author in2gasae
 */
public class Matematicas {
    
  public static void main( String args[] ) {
        int x;
        double rand,y,z;
        float max;

        rand = Math.random();
        x = Math.abs( -123 );
        y = Math.round( 123.567 );
        z = Math.pow( 2,4 );
        max = Math.max( (float)1e10,(float)3e9 );

        System.out.println( rand );
        System.out.println( x );
        System.out.println( y );
        System.out.println( z );
        System.out.println( max );
        
        Suma s = new Suma();
        double c = s.Sumar(y, z);
        s.Imprime(c);
        
        for( int i=0; i < 10; i++ )
            System.out.println( "Valor de la variable del bucle i: " + i );
    }  
}

class Suma {
    
    double Sumar(double a, double b) {
        return a+b;
    }
    
    int Sumar(int a, int b) {
        return a+b;
    }
    
    void Imprime(Object variable) {
        System.out.println(variable);
    }
}