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
public class Profesor extends Persona {
    
    //variables privadas
    private String _universidad;
    private int _id_profesor;

    //constructor
    public Profesor(String _nombre, String _apellidos, int _edad,String _universidad, int _id_profesor) {
        super(_nombre, _apellidos, _edad);
        this._universidad = _universidad;
        this._id_profesor = _id_profesor;
    }
    
    //Setters
    public void setUniversidad(String _universidad) {
        this._universidad = _universidad;
    }

    public void setId_profesor(int _id_profesor) {
        this._id_profesor = _id_profesor;
    }

    //Getters
    public String getUniversidad() {
        return _universidad;
    }

    public int getId_profesor() {
        return _id_profesor;
    }
     
}
