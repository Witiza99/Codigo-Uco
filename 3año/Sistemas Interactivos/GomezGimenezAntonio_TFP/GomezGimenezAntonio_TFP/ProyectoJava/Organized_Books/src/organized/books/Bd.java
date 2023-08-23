/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package organized.books;

import java.util.ArrayList;

/**
 *
 * @author Antonio
 */

//clase que simula una base de datos
public class Bd {
    
    public static ArrayList<Libro> v_librosFisicos;
    public static ArrayList<Libro> v_librosDigitales;
   


    public Bd() {
        this.v_librosFisicos = new ArrayList();
        this.v_librosDigitales = new ArrayList();
        
        v_librosFisicos.add(new Libro(0,"Harry Potter y la piedra Filosofal", "J.K. Rowling", "breve resumen", "0Cocina", 0));
        v_librosFisicos.add(new Libro(1,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "1Cocina", 0));
        v_librosFisicos.add(new Libro(2,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "2Cocina", 0));
        v_librosFisicos.add(new Libro(3,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "3Cocina", 0));
        v_librosFisicos.add(new Libro(4,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "4Cocina", 0));
        v_librosFisicos.add(new Libro(5,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "5Cocina", 0));
        v_librosFisicos.add(new Libro(6,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "6Cocina", 0));
        v_librosFisicos.add(new Libro(7,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "7Cocina", 0));
        v_librosFisicos.add(new Libro(8,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "8Cocina", 0));
        v_librosFisicos.add(new Libro(9,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "9Cocina", 0));
        v_librosFisicos.add(new Libro(10,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "10Cocina", 0));
        v_librosFisicos.add(new Libro(11,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "11Cocina", 0));
        v_librosFisicos.add(new Libro(12,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "12Cocina", 0));
        v_librosFisicos.add(new Libro(13,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "13Cocina", 0));
        v_librosFisicos.add(new Libro(14,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "14Cocina", 0));
        v_librosFisicos.add(new Libro(15,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "15Cocina", 0));
        v_librosFisicos.add(new Libro(16,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "16Cocina", 0));
        v_librosFisicos.add(new Libro(17,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "17Cocina", 0));
        v_librosFisicos.add(new Libro(18,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "18Cocina", 0));
        v_librosFisicos.add(new Libro(19,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "19Cocina", 0));
        v_librosFisicos.add(new Libro(20,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "20Cocina", 0));
        v_librosFisicos.add(new Libro(21,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "21Cocina", 0));
        v_librosFisicos.add(new Libro(22,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "22Cocina", 0));
        v_librosFisicos.add(new Libro(23,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "23Cocina", 0));
        v_librosFisicos.add(new Libro(24,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "24Cocina", 0));
        v_librosFisicos.add(new Libro(25,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "25Cocina", 0));
        v_librosFisicos.add(new Libro(26,"Test", "J.K. Rowling", "breve resumen", "25Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(27,"Test", "J.K. Rowling", "breve resumen", "26Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(28,"Test", "J.K. Rowling", "breve resumen", "27Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(29,"Test", "J.K. Rowling", "breve resumen", "28Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(30,"Test", "J.K. Rowling", "breve resumen", "29Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(31,"Test", "J.K. Rowling", "breve resumen", "30Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(32,"Test", "J.K. Rowling", "breve resumen", "31Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(33,"Test", "J.K. Rowling", "breve resumen", "32Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(34,"Test", "J.K. Rowling", "breve resumen", "33Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(35,"Test", "J.K. Rowling", "breve resumen", "34Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(36,"Test", "J.K. Rowling", "breve resumen", "35Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(37,"Test", "J.K. Rowling", "breve resumen", "36Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(38,"Test", "J.K. Rowling", "breve resumen", "37Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(39,"Test", "J.K. Rowling", "breve resumen", "38Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(40,"Test", "J.K. Rowling", "breve resumen", "39Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(41,"Test", "J.K. Rowling", "breve resumen", "40Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(42,"Test", "J.K. Rowling", "breve resumen", "41Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(43,"Test", "J.K. Rowling", "breve resumen", "42Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(44,"Test", "J.K. Rowling", "breve resumen", "43Cocina-Comedor", 0));
        v_librosFisicos.add(new Libro(45,"Test2", "J.K. Rowling", "breve resumen aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "44Cocina-Comedor", 1));
        
        
        v_librosDigitales.add(new Libro(0,"Harry Potter y la piedra Filosofal", "J.K. Rowling", "breve resumen", "", 0));
        v_librosDigitales.add(new Libro(1,"Harry Potter y la cámara de los secretos", "J.K. Rowling", "breve resumen", "", 0));
    }

    
    //métodos de la clase
    public static ArrayList<Libro> getV_librosFisicos() {
        return v_librosFisicos;
    }

    public static ArrayList<Libro> getV_librosDigitales() {
        return v_librosDigitales;
    }
    
    //se devuelve un libro segun la id que tenga y la bd que pertenezca
    public static Libro libro_Por_ID(int id ,int bd){
        
        String sid = String.valueOf(id);
        ArrayList<Libro> vector = buscarlibro(2, sid, bd);   
        
        Libro aux = new Libro(vector.get(0));
        
        return aux;
    }
    
    //nos devuelve el ultimo id de la bd que pidamos
    public static int getUltimoId(int mode){
        
        if(mode==0){
            return v_librosFisicos.get(v_librosFisicos.size()-1).getId();
        }else{
            return v_librosDigitales.get(v_librosDigitales.size()-1).getId();
        }
    }
    
    //inserta un libro en la bd que queramos
    public static void insertarLibro(Libro libro, int mode){
        if(mode==0){
            v_librosFisicos.add(libro);
        }else{
            v_librosDigitales.add(libro);
        }
    }
    
    //modifica un libro con la id que hayamos pasado en la bd que queramos
    public static void ModificarLibro(int id, Libro libro, int mode){
        if(mode==0){
            v_librosFisicos.set(id, libro);
        }else{
            v_librosDigitales.set(id, libro);
        }
    }
    
    //borra el libro de la id que le pasemos en la bd que digamos
    public static void borrarLibro(int id, int mode){
        if(mode==0){
            for(int i=0;i<v_librosFisicos.size();i++){
                if(id<v_librosFisicos.get(i).getId()){
                    v_librosFisicos.get(i).setId(v_librosFisicos.get(i).getId()-1);
                }
            }
            v_librosFisicos.remove(id);
        }else{
            for(int i=0;i<v_librosDigitales.size();i++){
                if(id<v_librosDigitales.get(i).getId()){
                    v_librosDigitales.get(i).setId(v_librosDigitales.get(i).getId()-1);
                }
            }
            v_librosDigitales.remove(id);
        }
    }
    
    //busca un libro en la bd que digamos y en el modo que seleccionemos (nombre, autor, id)
    public static ArrayList<Libro> buscarlibro(int mode, String comparacion, int bd){
        ArrayList<Libro> vector;
        vector = new ArrayList();
        
        if(bd==0){
            switch (mode) {
                case 0:
                    for(int i=0;i<v_librosFisicos.size();i++){
                        if(comparacion.equals((v_librosFisicos.get(i)).getNombre_libro())){
                            vector.add(v_librosFisicos.get(i));
                        }
                    }   break;
                case 1:
                    for(int i=0;i<v_librosFisicos.size();i++){
                        if(comparacion.equals((v_librosFisicos.get(i)).getAutor())){
                            vector.add(v_librosFisicos.get(i));
                        }
                    }   break;
                case 2:
                    int id = Integer.parseInt(comparacion);
                    for(int i=0;i<v_librosFisicos.size();i++){
                        if(id==(v_librosFisicos.get(i)).getId()){
                            vector.add(v_librosFisicos.get(i));
                        }
                    }   break;
                default:
                    break;
            }
        return vector;
        }else{
            switch (mode) {
                case 0:
                    for(int i=0;i<v_librosDigitales.size();i++){
                        if(comparacion.equals((v_librosDigitales.get(i)).getNombre_libro())){
                            vector.add(v_librosDigitales.get(i));
                        }
                    }   break;
                case 1:
                    for(int i=0;i<v_librosDigitales.size();i++){
                        if(comparacion.equals((v_librosDigitales.get(i)).getAutor())){
                            vector.add(v_librosDigitales.get(i));
                        }
                    }   break;
                case 2:
                    int id = Integer.parseInt(comparacion);
                    for(int i=0;i<v_librosDigitales.size();i++){
                        if(id==(v_librosDigitales.get(i)).getId()){
                            vector.add(v_librosDigitales.get(i));
                        }
                    }   break;
                default:
                    break;
            }
        return vector;
        }    
    }
}
