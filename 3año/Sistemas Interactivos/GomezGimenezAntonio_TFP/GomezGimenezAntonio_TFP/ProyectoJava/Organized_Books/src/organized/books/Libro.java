/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package organized.books;

/**
 *
 * @author Antonio
 */

//clase libro que hace referencia a la información que podríamos encontrar de los libro en el mundo real
public class Libro {
    
    int id;
    String nombre_libro;
    String autor;
    String resumen;
    String lugar;
    int opinion;

    public Libro() {
        
    }
    
    public Libro(Libro auxlibro) {
        this.id = auxlibro.getId();
        this.nombre_libro = auxlibro.getNombre_libro();
        this.autor = auxlibro.getAutor();
        this.resumen = auxlibro.getResumen();
        this.lugar = auxlibro.getLugar();
        this.opinion = auxlibro.getOpinion();
    }
    
    public Libro(int id, String nombre_libro, String autor, String resumen, String lugar, int opinion) {
        this.id = id;
        this.nombre_libro = nombre_libro;
        this.autor = autor;
        this.resumen = resumen;
        this.lugar = lugar;
        this.opinion = opinion;
    }

    public int getId() {
        return id;
    }

    public String getNombre_libro() {
        return nombre_libro;
    }

    public String getAutor() {
        return autor;
    }

    public String getResumen() {
        return resumen;
    }

    public String getLugar() {
        return lugar;
    }

    public int getOpinion() {
        return opinion;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setNombre_libro(String nombre_libro) {
        this.nombre_libro = nombre_libro;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public void setResumen(String resumen) {
        this.resumen = resumen;
    }

    public void setLugar(String lugar) {
        this.lugar = lugar;
    }

    public void setOpinion(int opinion) {
        this.opinion = opinion;
    }
    
}
