
package javabasico;

// En las interfaces los métodos no pueden tener cuerpo
// y son abstractos por defecto, o sea que deben implementarse en
// las clases hijas

interface FiguraGeometrica { 
    void area();
} 

interface Constante { 
    // constante
    final double pi = 3.14;
}

// Las clases abstractas si pueden implementar métodos 
// además de tener otros métodos abstractos
abstract class Abstracta { 
    
    void calcula() {
        int a = 1;
    }
    abstract void perimetro();
}

class Cuadrado implements FiguraGeometrica { 
    int lado; 
    
    public Cuadrado (int lado) { 
        this.lado = lado; 
    }
    
    public void area (){ 
        System.out.println("El area del cuadrado es "+(lado*lado)); 
    } 
} 
 
class Circulo implements FiguraGeometrica, Constante { 
    int radio; 
    
    public Circulo (int radio) { 
        this.radio = radio; 
    }
    
    public void area () { 
        System.out.println("El area del círculo es " + (2 * pi *(radio*radio))); 
    } 
} 
 
class Triangulo implements FiguraGeometrica{ 
    int base, altura; 
    
    public Triangulo (int base, int altura) { 
        this.base=base; 
        this.altura=altura; 
    }
    
    public void area () { 
        System.out.println("El area del triangulo es " + (base*altura)/2); 
    } 
} 

public class EjemploInterfaceAbstract { 
 
    static void dibujaArea(FiguraGeometrica f) { 
        f.area(); 
    } 
    
    public static void main(String[] args) { 
        FiguraGeometrica cuadrado = new Cuadrado(5); 
        FiguraGeometrica circulo = new Circulo(4); 
        FiguraGeometrica triangulo = new Triangulo(16,5); 
        dibujaArea(cuadrado); 
        dibujaArea(circulo); 
        dibujaArea(triangulo); 
    } 
} 
