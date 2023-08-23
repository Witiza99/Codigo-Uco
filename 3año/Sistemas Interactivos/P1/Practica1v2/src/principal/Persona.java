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
public class Persona {
    
    //Variables Privadas
    private String _nombre;
    private String _apellidos;
    private int _edad;

    //Constructor
    public Persona(String _nombre, String _apellidos, int _edad) {
        this._nombre = _nombre;
        this._apellidos = _apellidos;
        this._edad = _edad;
    }

    //Setters
    public void setNombre(String _nombre) {
        this._nombre = _nombre;
    }

    public void setApellidos(String _apellidos) {
        this._apellidos = _apellidos;
    }

    public void setEdad(int _edad) {
        this._edad = _edad;
    }
    
    //Getters
    public String getNombre() {
        return _nombre;
    }

    public String getApellidos() {
        return _apellidos;
    }

    public int getEdad() {
        return _edad;
    }
}
