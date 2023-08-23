/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package principal;
import java.util.ArrayList;

/**
 *
 * @author Antonio
 */
public class Datos_Aleatorios {
    //Variables Privadas
    private final ArrayList<String> v_nombres;
    private final ArrayList<String> v_apellidos;
    private final ArrayList<Integer> v_edad;
    private final ArrayList<String> v_universidad;
    private final ArrayList<Integer> v_idProfesor;
    
    //Constructor
    public Datos_Aleatorios() {
        this.v_nombres = new ArrayList();
        this.v_apellidos = new ArrayList();
        this.v_edad = new ArrayList();
        this.v_universidad = new ArrayList();
        this.v_idProfesor = new ArrayList();
        
        v_nombres.add("Antonio");
        v_nombres.add("Fran");
        v_nombres.add("Juan");
        v_nombres.add("Pedro");
        v_nombres.add("María");
        v_nombres.add("Julieta");
        v_nombres.add("Ana");
        v_nombres.add("Rafael");
        v_nombres.add("Andrés");
        v_nombres.add("Cristina");
        
        v_apellidos.add("Gómez");
        v_apellidos.add("Giménez");
        v_apellidos.add("Hormigo");
        v_apellidos.add("Cardenas");
        v_apellidos.add("García");
        v_apellidos.add("De la Torre");
        v_apellidos.add("Ruiz");
        v_apellidos.add("Morales");
        v_apellidos.add("Fernandez");
        v_apellidos.add("Cabello");
        
        v_edad.add(41);
        v_edad.add(30);
        v_edad.add(63);
        v_edad.add(74);
        v_edad.add(27);
        v_edad.add(38);
        v_edad.add(57);
        v_edad.add(48);
        v_edad.add(50);
        v_edad.add(62);
        
        v_universidad.add("UCO");
        v_universidad.add("UNED");
        v_universidad.add("UNEX");
        v_universidad.add("US");
        v_universidad.add("UVA");
        v_universidad.add("VIU");
        v_universidad.add("UPSA");
        v_universidad.add("UIB");
        v_universidad.add("UDC");
        v_universidad.add("CEU");
        
        v_idProfesor.add(1);
        v_idProfesor.add(2);
        v_idProfesor.add(3);
        v_idProfesor.add(4);
        v_idProfesor.add(5);
        v_idProfesor.add(6);
        v_idProfesor.add(7);
        v_idProfesor.add(8);
        v_idProfesor.add(9);
        v_idProfesor.add(10);
    }  
    
    //Métodos
    public String nombre_Random(){
        int random = (int)(Math.random() * 10);
        return v_nombres.get(random);
    }
    
    public String apellidos_Random(){
        int random = (int)(Math.random() * 10);
        return v_apellidos.get(random);
    }
    
    public int edad_Random(){
        int random = (int)(Math.random() * 10);
        return v_edad.get(random);
    }
    
    public String universidad_Random(){
        int random = (int)(Math.random() * 10);
        return v_universidad.get(random);
    }
    
    public int idProfesor_Random(){
        int random = (int)(Math.random() * 10);
        return v_idProfesor.get(random);
    }
    
}
