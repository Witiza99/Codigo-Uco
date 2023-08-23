/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

import java.util.Hashtable;

/**
 *
 * @author in2gasae
 */
public class HashTable {
    
    public static void main( String args[] ) {
        
        Hashtable <String,String> paises = new Hashtable <>();
        
        paises.put("ES", "España");
        paises.put("UK", "Reino Unido");
        paises.put("US", "Estados Unidos");
        paises.put("FR", "Francia");
        
        String clave = "US";
        System.out.println("El valor de la clave " + clave + " es " + paises.get(clave));
        
    }
}
