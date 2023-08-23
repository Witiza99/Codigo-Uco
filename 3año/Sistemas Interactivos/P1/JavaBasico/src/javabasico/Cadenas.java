/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package javabasico;

import java.util.StringTokenizer;

/**
 *
 * @author in2gasae
 */
public class Cadenas {
    
    public static void main(String args[]) {
        
        String s = "  Curso de Java ";
        System.out.println(s);
        System.out.println(s.toUpperCase());
        System.out.println(s.toLowerCase());
        System.out.println("["+s+"]");
        s=s.trim();
        System.out.println("["+s+"]");
        s=s.replace('C','X');
        s=s.replace('J','Y');
        System.out.println(s);
        int i1 = s.indexOf('X');
        int i2 = s.indexOf('Y');
        char ch[] = s.toCharArray();
        ch[i1]='C';
        ch[i2]='J';
        s = new String(ch);
        System.out.println(s);
        s = "10";
        String s1 ="20";
        int c = Integer.valueOf(s) + Integer.valueOf(s1);
        System.out.println("c=" + c);      
        
        // Parsear cadenas
        String cadena = "Juan=Ana:Antonio=Rosa:Jose=Maria";
        StringTokenizer st = new StringTokenizer( cadena,"=:" );

        while( st.hasMoreTokens() ) {
            String clave = st.nextToken();
            String valor = st.nextToken();
            System.out.println("clave:" + clave);
            System.out.println("valor:" + valor);
        }
        
    }
}
