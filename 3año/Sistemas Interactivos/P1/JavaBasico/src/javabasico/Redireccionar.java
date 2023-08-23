/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;

/**
 *
 * @author in2gasae
 */
public class Redireccionar {
    
// Throw exceptions to console:
  public static void main(String[] args) throws IOException {
      
    BufferedInputStream in = new BufferedInputStream(new FileInputStream(
          "fichero.txt"));
    PrintStream out = new PrintStream(new BufferedOutputStream(
          new FileOutputStream("test.out")));
    
    System.setIn(in);
    System.setOut(out);
    System.setErr(out);

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    String s;
    while((s = br.readLine()) != null)
      System.out.println(s);  // Se escribe al archivo test.out en lugar de pantalla
    out.close(); 
  }    
}
