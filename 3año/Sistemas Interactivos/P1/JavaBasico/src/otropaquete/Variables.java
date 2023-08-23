/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package otropaquete;

import javabasico.*;

/**
 *
 * @author salcines
 */
public class Variables {
    
    void calcula() {
        Encapsulacion p = new Encapsulacion();
        int b = p.d + 1;
        
    }
}

class Variables1 extends Encapsulacion {
    
    void calcula() {
        // c es protected, por tanto se puede acceder 
        // desde cualquier clase hija y desde otro paquete
        int b = c + 1;
        
    }
}