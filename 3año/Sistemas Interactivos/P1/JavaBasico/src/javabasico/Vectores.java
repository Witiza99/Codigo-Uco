/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

import java.util.Vector;

/**
 *
 * @author in2gasae
 */
public class Vectores {
    
    public static void main( String args[] ) {
        
        Vector v = new Vector();
        
        v.addElement("uno");
        v.addElement("dos");
        v.addElement("cuatro");
        v.addElement("cinco");
        v.addElement("seis");
        v.addElement("siete");
        v.addElement("ocho");
        v.addElement("nueve");
        v.addElement("diez");
        v.addElement("once");
        v.addElement("doce");
        
        for( int i=0; i < v.size(); i++ ) { 
            System.out.println(v.elementAt(i)+"\t");
        }
        
        v.insertElementAt("tres", 2);
        
        v.removeElement("once");
        
        System.out.println("------Vector despues:");
        for( int i=0; i < v.size(); i++ ) { 
            System.out.println(v.get(i)+"\t");
        }
        
        if(v.contains("doce")){
            System.out.println("Encontrado doce");
        }
    }
}
