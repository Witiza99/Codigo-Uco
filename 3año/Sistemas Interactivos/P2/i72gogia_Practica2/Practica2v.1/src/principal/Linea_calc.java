/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package principal;

/**
 *
 * @author Antonio
 */
public class Linea_calc {
    
    double Numero1;
    double Numero2;
    double auxiliar;
    char operator;
    boolean Resultado_hecho;
    boolean Numero1_Introducido;
    boolean necesita_op;

    public Linea_calc() {
        Numero1=0.0;
        Numero2=0.0;
        Resultado_hecho=false;
        Numero1_Introducido=false;
        necesita_op=true;
    }

    public double getNumero1() {
        return Numero1;
    }
    
    public double getNumero2() {
        return Numero2;
    }

     public char getOperator() {
        return operator;
    }

    public boolean isNecesita_op() {
        return necesita_op;
    }

    public boolean isNumero1_Introducido() {
        return Numero1_Introducido;
    }

    public boolean isResultado_hecho() {
        return Resultado_hecho;
    }

    public void setNumero1(double Numero1) {
        this.Numero1 = Numero1;
    }
    
    public void setNumero2(double Numero2) {
        this.Numero2 = Numero2;
    }

    public void setOperator(char operator) {
        this.operator = operator;
    }

    public void setNumero1_Introducido(boolean Numero1_Introducido) {
        this.Numero1_Introducido = Numero1_Introducido;
    }

    public void setResultado_hecho(boolean Resultado_hecho) {
        this.Resultado_hecho = Resultado_hecho;
    } 

    public void setNecesita_op(boolean necesita_op) {
        this.necesita_op = necesita_op;
    }
    
    public double calcular(char valor){
        
        if(valor=='+'){
            return Operadores.suma(Numero1,Numero2);
        }else if(valor=='-'){
            return Operadores.resta(Numero1,Numero2);
        }else if(valor=='*'){
            return Operadores.multiplicacion(Numero1,Numero2);
        }else if(valor=='/'){
            return Operadores.division(Numero1,Numero2);
        }else if(valor=='%'){
            return Operadores.mod(Numero1,Numero2);
        }
        return 0;
    }

}
