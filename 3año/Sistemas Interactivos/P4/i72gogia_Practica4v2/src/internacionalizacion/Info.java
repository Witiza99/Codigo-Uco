/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package internacionalizacion;

/**
 *
 * @author Antonio
 */
public class Info {
    
    String nombre;
    String apellidos;
    //se deberan introducir los datos de forma correcta al recoger la fecha según el formato
    int dia;
    int mes;
    int año;
    double dinero;//se almacena en euros esta informacion, por tanto es necesario que se realice el cambio antes

    public String getNombre() {
        return nombre;
    }

    public String getApellidos() {
        return apellidos;
    }

    public int getDia() {
        return dia;
    }

    public int getMes() {
        return mes;
    }

    public int getAño() {
        return año;
    }

    public double getDinero() {
        return dinero;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setApellidos(String apellidos) {
        this.apellidos = apellidos;
    }

    public void setDia(int dia) {
        this.dia = dia;
    }

    public void setMes(int mes) {
        this.mes = mes;
    }

    public void setAño(int año) {
        this.año = año;
    }
    
    public void setDinero(double dinero) {
        this.dinero = dinero;
    }
}
