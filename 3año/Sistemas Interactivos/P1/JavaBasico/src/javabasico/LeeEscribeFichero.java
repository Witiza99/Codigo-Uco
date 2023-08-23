/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 *
 * @author in2gasae
 */
public class LeeEscribeFichero {
    
public static void main(String[] args) 
{
    String cadena = "Primera linea.\nSegunda linea.\nUltima linea.";
    String tmp = null;

    try
    {
        BufferedWriter fout = new BufferedWriter(new FileWriter("fichero.txt") ); 
        fout.write(cadena,0,cadena.length());
        fout.close();
        
        BufferedReader fin = new BufferedReader(new FileReader("fichero.txt") ); 

        System.out.println("El contenido del fichero es:");
        while ( (tmp = fin.readLine()) != null )
            System.out.println(tmp);

    } catch(IOException e){
	 System.out.println("Error al escribir");
    }
 }    
}
