
package javabasico;

/**
 *
 * @author salcines
 */
public class Encapsulacion {
    // Package: acceso sólo desde el paquete 
    int a = 1;
    // Private: acceso sólo desde la clase 
    private int b = 2;
    // Protected: acceso sólo desde clases hijas o de clases que están en el mismo paquete
    protected int c = 3;
    // Public: acceso desde cualquier clase incluso fuera del paquete
    public int d = 3;
}

class Prueba {
    
    void calcula() {
        Encapsulacion p = new Encapsulacion();
        int b = p.c + 1;
    }
}
