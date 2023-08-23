/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package principal;

import java.io.IOException;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.swing.ImageIcon;
import javax.swing.JFrame;



/**
 *
 * @author Antonio
 */
public class Calculadora extends javax.swing.JFrame {

    /**
    * Creates new form Calculadora
    */

    public Calculadora() {
        initComponents();
        this.setTitle("Calculator");
        Texto_Primario.setText("0");
        Texto_Secundario.setText("");
    }
    
    /**
     * Variables propias
     */
    Linea_calc l_calc = new Linea_calc();
    boolean Pantalla_vacia=true;
    int tecla_anterior;
    double resultado=0.0;
    
    
    /**
     * Métodos
     */

    private void audio(char valor){
         try {
            if(valor=='.'){valor='p';}
            else if(valor=='%'){valor='m';}
            else if(valor=='+'){valor='s';}
            else if(valor=='-'){valor='r';}
            else if(valor=='*'){valor='n';}
            else if(valor=='/'){valor='v';}
            Clip audio = AudioSystem.getClip();
            String ruta = "/audio/audio"+valor+".wav";
            audio.open(AudioSystem.getAudioInputStream(getClass().getResourceAsStream(ruta)));
            audio.start();
        } catch (IOException | LineUnavailableException | UnsupportedAudioFileException e) {
            System.out.println("" + e);
        }  
    }
    
    private void decirSolucion(){
        decirSolucion(0);
    }
    
    private void decirSolucion(int flag){
        //String cad_resultado=(String.valueOf(resultado));
        String cad_resultado=(Texto_Primario.getText());
        char cad[];
        cad=cad_resultado.toCharArray();
        if(flag!=1){
            try {
               audio('e');
               Thread.sleep(500);
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        try {
           Thread.sleep(1*1000);
        } catch (InterruptedException e) {
           System.out.println(e);
        }
        try{
            for(int i=0;i<cad_resultado.length();i++){
                audio(cad[i]);
                try {
                   Thread.sleep(1*1000);
                } catch (InterruptedException e) {
                   System.out.println(e);
                }
            }
        }catch (Exception e){
            audio('X');
        }
        
    }
    
    private void Speaker(){
        if(Texto_Secundario.getText().length()!=0){
            String cad_resultado= Texto_Secundario.getText();
            char cad[];
            cad=cad_resultado.toCharArray();
            for(int i=0;i<cad_resultado.length();i++){
                audio(cad[i]);
                try {
                  Thread.sleep(1*1000);
                } catch (InterruptedException e) {
                  System.out.println(e);
                }
            }
            decirSolucion(0);
        }else{
            decirSolucion(1);         
        }
    }

    private void NuevoNumero(char valor){
        if(!l_calc.isResultado_hecho()){
            if(Pantalla_vacia==true){
                if(valor!='0'){
                    Texto_Primario.setText(String.valueOf(valor));
                    Pantalla_vacia=false;
                }
            }else{
                Texto_Primario.setText(Texto_Primario.getText()+valor);
            }
        }else{
           BorrarTodo();
           NuevoNumero(valor);
        }   
    }
    
    private int comprobar_ultimo(){         
        String ulti=Texto_Primario.getText().substring(Texto_Primario.getText().length()-1);
        try{
            return Integer.parseInt(ulti);
        } catch(NumberFormatException e){
            return -1;
        }
    }
    
    private void op(char valor){//botones de borrar
        if(l_calc.isNumero1_Introducido()==false || l_calc.isResultado_hecho()==true){
            if((Texto_Primario.getText().length()-1)==0){
                l_calc.setNumero1(Double.parseDouble(Texto_Primario.getText().substring(Texto_Primario.getText().length()-1)));
            }else{
                l_calc.setNumero1(Double.parseDouble(Texto_Primario.getText().substring(0,Texto_Primario.getText().length())));
            }
            l_calc.setNumero1_Introducido(true);
            l_calc.setOperator(valor);
            Pantalla_vacia=false;
            Texto_Primario.setText(Texto_Primario.getText()+valor);
        }else{
            if(comprobar_ultimo()==-1 || l_calc.isNecesita_op()==true){
                if(l_calc.isNecesita_op()==true){
                    Texto_Primario.setText(Texto_Primario.getText().substring(0,Texto_Primario.getText().length())+valor);
                }else{
                    Texto_Primario.setText(Texto_Primario.getText().substring(0,Texto_Primario.getText().length()-1)+valor);
                }         
                l_calc.setOperator(valor);
            }else{
                char operador_ant = l_calc.getOperator();
                int posicion_op = Texto_Primario.getText().indexOf(operador_ant);
                l_calc.setNumero2(Double.parseDouble(Texto_Primario.getText().substring(posicion_op+1,Texto_Primario.getText().length())));
                l_calc.setOperator(valor);
                if( "".equals(Texto_Secundario.getText())){
                    Texto_Secundario.setText(Texto_Primario.getText());
                }else{
                    if(l_calc.isResultado_hecho()==false){
                        Texto_Secundario.setText(Texto_Secundario.getText()+operador_ant+String.valueOf(l_calc.getNumero2()));
                    }
                }     
                resultado=l_calc.calcular(operador_ant);
                if(!Double.isNaN(resultado) && !Double.isInfinite(resultado)){
                    l_calc.setNumero1(resultado);
                    Texto_Primario.setText(String.valueOf(resultado)+valor);
                }else{
                    BorrarTodo();
                    Texto_Primario.setText("Cannot divide by zero");
                    audio('X');
                }    
            }
        }
        l_calc.setNecesita_op(false);
        l_calc.setResultado_hecho(false);
    }
    
    private void op_igual(){
        if(comprobar_ultimo()==-1){
            if(Texto_Secundario.getText().length()==0){
                Texto_Secundario.setText(Texto_Secundario.getText()+Texto_Primario.getText()+"0");
            }else{
                Texto_Secundario.setText(Texto_Secundario.getText()+l_calc.getOperator()+"0");
            }
            l_calc.setNumero2(0);
            resultado=l_calc.calcular(l_calc.getOperator());
            Texto_Primario.setText(String.valueOf(resultado)); 
            
            resultado=l_calc.calcular(l_calc.getOperator());
            if(!Double.isNaN(resultado) && !Double.isInfinite(resultado)){
                l_calc.setNumero1(resultado);
                Texto_Primario.setText(String.valueOf(resultado));
            }else{
                BorrarTodo();
                Texto_Primario.setText("Cannot divide by zero");
            }
        }else{
            if(l_calc.isNumero1_Introducido()==true){
                if(l_calc.isResultado_hecho()!=true){
                    int posicion_op = Texto_Primario.getText().indexOf(l_calc.getOperator());
                    l_calc.setNumero2(Double.parseDouble(Texto_Primario.getText().substring(posicion_op+1,Texto_Primario.getText().length())));
                    if(Texto_Secundario.getText().length()==0){
                        Texto_Secundario.setText(String.valueOf(l_calc.getNumero1())+l_calc.getOperator()+String.valueOf(l_calc.getNumero2()));
                    }else{
                        Texto_Secundario.setText(Texto_Secundario.getText()+l_calc.getOperator()+String.valueOf(l_calc.getNumero2()));
                    }   
                    resultado=l_calc.calcular(l_calc.getOperator());
                    if(!Double.isNaN(resultado) && !Double.isInfinite(resultado)){
                        l_calc.setNumero1(resultado);
                        Texto_Primario.setText(String.valueOf(resultado));
                    }else{
                        BorrarTodo();
                        Texto_Primario.setText("Cannot divide by zero");
                    }
                }
            }else{
                l_calc.setNumero1(Double.parseDouble(Texto_Primario.getText().substring(0,Texto_Primario.getText().length())));
                resultado=l_calc.getNumero1();
                Texto_Primario.setText(String.valueOf(resultado));
            }
        }
        decirSolucion();
        l_calc.setResultado_hecho(true);
    }
    
    private void MeterPto(){//arreglar
        if(!Texto_Primario.getText().contains(".")){
            if(Texto_Primario.getText().length()>0){
                Texto_Primario.setText(Texto_Primario.getText()+".");
                Pantalla_vacia=false;
            }else{
                Texto_Primario.setText("0.");
                Pantalla_vacia=false;
            }
        }else{
            if(!l_calc.isNecesita_op()){
                
                int posicion, contador = 0;
                //se busca la primera vez que aparece
                posicion = Texto_Primario.getText().indexOf('.');
                while (posicion != -1) {
                    contador++;
                    posicion = Texto_Primario.getText().indexOf('.', posicion + 1);
                }
                
                if(contador<2){
                    Texto_Primario.setText(Texto_Primario.getText()+".");
                }
            }
        }
    }
    
    private void BorraUltimoNumero(){
        int aux = comprobar_ultimo();
        int tam_cadena = Texto_Primario.getText().length();
        if(tam_cadena>1){
            Texto_Primario.setText(Texto_Primario.getText().substring(0,tam_cadena-1));
            if(l_calc.isResultado_hecho()==true){
                l_calc = new Linea_calc();
                Pantalla_vacia=true;
                Texto_Secundario.setText("");
                resultado=0.0;
            }else if(aux==-1 || l_calc.isNecesita_op()==true){
                l_calc.setNecesita_op(true); 
                l_calc.setNumero1_Introducido(false);
                l_calc.setResultado_hecho(true);
            }
        }else if(tam_cadena==1){
            Texto_Primario.setText("0");
            Pantalla_vacia=true;
        }
        
    }
  
    private void BorrarTodo(){
        l_calc = new Linea_calc();
        Pantalla_vacia=true;
        Texto_Primario.setText("0");
        Texto_Secundario.setText("");
        resultado=0.0;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        Pantalla_Arriba = new javax.swing.JPanel();
        Secundario = new javax.swing.JPanel();
        Texto_Secundario = new javax.swing.JLabel();
        Primario = new javax.swing.JPanel();
        Texto_Primario = new javax.swing.JTextField();
        Pantalla_Abajo = new javax.swing.JPanel();
        Barra_Norte = new javax.swing.JPanel();
        Botones = new javax.swing.JPanel();
        Borrar_Todo = new javax.swing.JButton();
        Borra_Ultimo = new javax.swing.JButton();
        Modulo = new javax.swing.JButton();
        Dividir = new javax.swing.JButton();
        Uno = new javax.swing.JButton();
        Dos = new javax.swing.JButton();
        Tres = new javax.swing.JButton();
        Multiplicar = new javax.swing.JButton();
        Cuatro = new javax.swing.JButton();
        Cinco = new javax.swing.JButton();
        Seis = new javax.swing.JButton();
        Restar = new javax.swing.JButton();
        Siete = new javax.swing.JButton();
        Ocho = new javax.swing.JButton();
        Nueve = new javax.swing.JButton();
        Sumar = new javax.swing.JButton();
        Speak = new javax.swing.JButton();
        Cero = new javax.swing.JButton();
        Punto = new javax.swing.JButton();
        Igual = new javax.swing.JButton();
        Barra_Este = new javax.swing.JPanel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DO_NOTHING_ON_CLOSE);
        setBackground(new java.awt.Color(0, 0, 0));
        setForeground(new java.awt.Color(0, 0, 0));
        setIconImage(new ImageIcon(getClass().getResource("/imagenes/calc.png")).getImage());
        addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                formKeyPressed(evt);
            }
        });

        Pantalla_Arriba.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));
        Pantalla_Arriba.setName(""); // NOI18N
        Pantalla_Arriba.setLayout(new javax.swing.BoxLayout(Pantalla_Arriba, javax.swing.BoxLayout.Y_AXIS));

        Secundario.setBackground(new java.awt.Color(255, 255, 255));

        Texto_Secundario.setBackground(new java.awt.Color(255, 255, 255));
        Texto_Secundario.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Texto_Secundario.setHorizontalAlignment(javax.swing.SwingConstants.RIGHT);
        Texto_Secundario.setFocusable(false);

        javax.swing.GroupLayout SecundarioLayout = new javax.swing.GroupLayout(Secundario);
        Secundario.setLayout(SecundarioLayout);
        SecundarioLayout.setHorizontalGroup(
            SecundarioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(Texto_Secundario, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 555, Short.MAX_VALUE)
        );
        SecundarioLayout.setVerticalGroup(
            SecundarioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(Texto_Secundario, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 59, Short.MAX_VALUE)
        );

        Pantalla_Arriba.add(Secundario);

        Primario.setBackground(new java.awt.Color(255, 255, 255));

        Texto_Primario.setEditable(false);
        Texto_Primario.setBackground(new java.awt.Color(255, 255, 255));
        Texto_Primario.setFont(new java.awt.Font("Tahoma", 0, 40)); // NOI18N
        Texto_Primario.setHorizontalAlignment(javax.swing.JTextField.RIGHT);
        Texto_Primario.setText("0");
        Texto_Primario.setActionCommand("<Not Set>");
        Texto_Primario.setAutoscrolls(false);
        Texto_Primario.setBorder(null);
        Texto_Primario.setCaretColor(new java.awt.Color(240, 240, 240));
        Texto_Primario.setFocusable(false);
        Texto_Primario.setPreferredSize(new java.awt.Dimension(10, 49));
        Texto_Primario.setRequestFocusEnabled(false);

        javax.swing.GroupLayout PrimarioLayout = new javax.swing.GroupLayout(Primario);
        Primario.setLayout(PrimarioLayout);
        PrimarioLayout.setHorizontalGroup(
            PrimarioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(Texto_Primario, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        PrimarioLayout.setVerticalGroup(
            PrimarioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(Texto_Primario, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, 66, Short.MAX_VALUE)
        );

        Pantalla_Arriba.add(Primario);

        getContentPane().add(Pantalla_Arriba, java.awt.BorderLayout.NORTH);

        Pantalla_Abajo.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));
        Pantalla_Abajo.setLayout(new java.awt.BorderLayout());

        Barra_Norte.setBackground(new java.awt.Color(102, 0, 102));
        Barra_Norte.setFocusable(false);

        javax.swing.GroupLayout Barra_NorteLayout = new javax.swing.GroupLayout(Barra_Norte);
        Barra_Norte.setLayout(Barra_NorteLayout);
        Barra_NorteLayout.setHorizontalGroup(
            Barra_NorteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 555, Short.MAX_VALUE)
        );
        Barra_NorteLayout.setVerticalGroup(
            Barra_NorteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 47, Short.MAX_VALUE)
        );

        Pantalla_Abajo.add(Barra_Norte, java.awt.BorderLayout.NORTH);

        Botones.setBackground(new java.awt.Color(102, 0, 102));
        Botones.setLayout(new java.awt.GridLayout(5, 4));

        Borrar_Todo.setBackground(new java.awt.Color(204, 204, 204));
        Borrar_Todo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/borrar_todo2.png"))); // NOI18N
        Borrar_Todo.setBorder(new javax.swing.border.SoftBevelBorder(javax.swing.border.BevelBorder.RAISED));
        Borrar_Todo.setBorderPainted(false);
        Borrar_Todo.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Borrar_Todo.setFocusable(false);
        Borrar_Todo.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Borrar_TodoMouseClicked(evt);
            }
        });
        Botones.add(Borrar_Todo);

        Borra_Ultimo.setBackground(new java.awt.Color(204, 204, 204));
        Borra_Ultimo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/goma2.png"))); // NOI18N
        Borra_Ultimo.setBorderPainted(false);
        Borra_Ultimo.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Borra_Ultimo.setFocusable(false);
        Borra_Ultimo.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Borra_UltimoMouseClicked(evt);
            }
        });
        Botones.add(Borra_Ultimo);

        Modulo.setBackground(new java.awt.Color(204, 204, 204));
        Modulo.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/porcentaje.png"))); // NOI18N
        Modulo.setBorderPainted(false);
        Modulo.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Modulo.setFocusable(false);
        Modulo.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                ModuloMouseClicked(evt);
            }
        });
        Botones.add(Modulo);

        Dividir.setBackground(new java.awt.Color(204, 204, 204));
        Dividir.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/division.png"))); // NOI18N
        Dividir.setBorderPainted(false);
        Dividir.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Dividir.setFocusable(false);
        Dividir.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                DividirMouseClicked(evt);
            }
        });
        Botones.add(Dividir);

        Uno.setBackground(new java.awt.Color(255, 255, 255));
        Uno.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Uno.setText("1");
        Uno.setBorderPainted(false);
        Uno.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Uno.setFocusable(false);
        Uno.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                UnoMouseClicked(evt);
            }
        });
        Botones.add(Uno);

        Dos.setBackground(new java.awt.Color(255, 255, 255));
        Dos.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Dos.setText("2");
        Dos.setBorderPainted(false);
        Dos.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Dos.setFocusable(false);
        Dos.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                DosMouseClicked(evt);
            }
        });
        Botones.add(Dos);

        Tres.setBackground(new java.awt.Color(255, 255, 255));
        Tres.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Tres.setText("3");
        Tres.setBorderPainted(false);
        Tres.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Tres.setFocusable(false);
        Tres.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                TresMouseClicked(evt);
            }
        });
        Botones.add(Tres);

        Multiplicar.setBackground(new java.awt.Color(204, 204, 204));
        Multiplicar.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/multiplicacion.png"))); // NOI18N
        Multiplicar.setBorderPainted(false);
        Multiplicar.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Multiplicar.setFocusable(false);
        Multiplicar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                MultiplicarMouseClicked(evt);
            }
        });
        Botones.add(Multiplicar);

        Cuatro.setBackground(new java.awt.Color(255, 255, 255));
        Cuatro.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Cuatro.setText("4");
        Cuatro.setBorderPainted(false);
        Cuatro.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Cuatro.setFocusable(false);
        Cuatro.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                CuatroMouseClicked(evt);
            }
        });
        Botones.add(Cuatro);

        Cinco.setBackground(new java.awt.Color(255, 255, 255));
        Cinco.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Cinco.setText("5");
        Cinco.setBorderPainted(false);
        Cinco.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Cinco.setFocusable(false);
        Cinco.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                CincoMouseClicked(evt);
            }
        });
        Botones.add(Cinco);

        Seis.setBackground(new java.awt.Color(255, 255, 255));
        Seis.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Seis.setText("6");
        Seis.setBorderPainted(false);
        Seis.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Seis.setFocusable(false);
        Seis.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                SeisMouseClicked(evt);
            }
        });
        Botones.add(Seis);

        Restar.setBackground(new java.awt.Color(204, 204, 204));
        Restar.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/resta.png"))); // NOI18N
        Restar.setBorderPainted(false);
        Restar.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Restar.setFocusable(false);
        Restar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                RestarMouseClicked(evt);
            }
        });
        Botones.add(Restar);

        Siete.setBackground(new java.awt.Color(255, 255, 255));
        Siete.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Siete.setText("7");
        Siete.setBorderPainted(false);
        Siete.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Siete.setFocusable(false);
        Siete.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                SieteMouseClicked(evt);
            }
        });
        Botones.add(Siete);

        Ocho.setBackground(new java.awt.Color(255, 255, 255));
        Ocho.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Ocho.setText("8");
        Ocho.setBorderPainted(false);
        Ocho.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Ocho.setFocusable(false);
        Ocho.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                OchoMouseClicked(evt);
            }
        });
        Botones.add(Ocho);

        Nueve.setBackground(new java.awt.Color(255, 255, 255));
        Nueve.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Nueve.setText("9");
        Nueve.setBorderPainted(false);
        Nueve.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Nueve.setFocusable(false);
        Nueve.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                NueveMouseClicked(evt);
            }
        });
        Botones.add(Nueve);

        Sumar.setBackground(new java.awt.Color(204, 204, 204));
        Sumar.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Sumar.setText("+");
        Sumar.setBorderPainted(false);
        Sumar.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Sumar.setFocusable(false);
        Sumar.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                SumarMouseClicked(evt);
            }
        });
        Botones.add(Sumar);

        Speak.setBackground(new java.awt.Color(255, 255, 255));
        Speak.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/speak.png"))); // NOI18N
        Speak.setBorderPainted(false);
        Speak.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Speak.setFocusable(false);
        Speak.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                SpeakMouseClicked(evt);
            }
        });
        Botones.add(Speak);

        Cero.setBackground(new java.awt.Color(255, 255, 255));
        Cero.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Cero.setText("0");
        Cero.setBorderPainted(false);
        Cero.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Cero.setFocusable(false);
        Cero.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                CeroMouseClicked(evt);
            }
        });
        Botones.add(Cero);

        Punto.setBackground(new java.awt.Color(255, 255, 255));
        Punto.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
        Punto.setText(".");
        Punto.setBorderPainted(false);
        Punto.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Punto.setFocusable(false);
        Punto.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                PuntoMouseClicked(evt);
            }
        });
        Botones.add(Punto);

        Igual.setBackground(new java.awt.Color(204, 204, 204));
        Igual.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/igual.png"))); // NOI18N
        Igual.setBorderPainted(false);
        Igual.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        Igual.setFocusable(false);
        Igual.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                IgualMouseClicked(evt);
            }
        });
        Botones.add(Igual);

        Pantalla_Abajo.add(Botones, java.awt.BorderLayout.CENTER);

        Barra_Este.setBackground(new java.awt.Color(102, 0, 102));
        Barra_Este.setFocusable(false);

        javax.swing.GroupLayout Barra_EsteLayout = new javax.swing.GroupLayout(Barra_Este);
        Barra_Este.setLayout(Barra_EsteLayout);
        Barra_EsteLayout.setHorizontalGroup(
            Barra_EsteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 16, Short.MAX_VALUE)
        );
        Barra_EsteLayout.setVerticalGroup(
            Barra_EsteLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 369, Short.MAX_VALUE)
        );

        Pantalla_Abajo.add(Barra_Este, java.awt.BorderLayout.EAST);

        getContentPane().add(Pantalla_Abajo, java.awt.BorderLayout.CENTER);

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void UnoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_UnoMouseClicked
        NuevoNumero('1');
        audio('1');
    }//GEN-LAST:event_UnoMouseClicked

    private void DosMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_DosMouseClicked
        NuevoNumero('2');
        audio('2');
    }//GEN-LAST:event_DosMouseClicked

    private void TresMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_TresMouseClicked
        NuevoNumero('3');
        audio('3');
    }//GEN-LAST:event_TresMouseClicked

    private void CuatroMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_CuatroMouseClicked
        NuevoNumero('4');
        audio('4');
    }//GEN-LAST:event_CuatroMouseClicked

    private void CincoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_CincoMouseClicked
        NuevoNumero('5');
        audio('5');
    }//GEN-LAST:event_CincoMouseClicked

    private void SeisMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_SeisMouseClicked
        NuevoNumero('6');
        audio('6');
    }//GEN-LAST:event_SeisMouseClicked

    private void SieteMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_SieteMouseClicked
        NuevoNumero('7');
        audio('7');
    }//GEN-LAST:event_SieteMouseClicked

    private void OchoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_OchoMouseClicked
        NuevoNumero('8');
        audio('8');
    }//GEN-LAST:event_OchoMouseClicked

    private void NueveMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_NueveMouseClicked
       NuevoNumero('9');
       audio('9');
    }//GEN-LAST:event_NueveMouseClicked

    private void CeroMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_CeroMouseClicked
        NuevoNumero('0');
        audio('0');
    }//GEN-LAST:event_CeroMouseClicked

    private void Borrar_TodoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Borrar_TodoMouseClicked
        BorrarTodo();
        audio('b');
    }//GEN-LAST:event_Borrar_TodoMouseClicked

    private void Borra_UltimoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Borra_UltimoMouseClicked
        BorraUltimoNumero();
        audio('d');
    }//GEN-LAST:event_Borra_UltimoMouseClicked

    private void ModuloMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_ModuloMouseClicked
        op('%');
        audio('m');
    }//GEN-LAST:event_ModuloMouseClicked

    private void DividirMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_DividirMouseClicked
        op('/');
        audio('v');
    }//GEN-LAST:event_DividirMouseClicked

    private void MultiplicarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_MultiplicarMouseClicked
        op('*');
        audio('n');
    }//GEN-LAST:event_MultiplicarMouseClicked

    private void RestarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_RestarMouseClicked
        op('-');
        audio('r');
    }//GEN-LAST:event_RestarMouseClicked

    private void SumarMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_SumarMouseClicked
        op('+');
        audio('s');
    }//GEN-LAST:event_SumarMouseClicked

    private void IgualMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_IgualMouseClicked
        op_igual();
    }//GEN-LAST:event_IgualMouseClicked

    private void SpeakMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_SpeakMouseClicked
        Speaker();
    }//GEN-LAST:event_SpeakMouseClicked

    private void PuntoMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_PuntoMouseClicked
        MeterPto();
        audio('p');
    }//GEN-LAST:event_PuntoMouseClicked

    private void formKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_formKeyPressed
         char entrada;
        entrada = evt.getKeyChar();
            
        if(evt.getKeyCode() == java.awt.event.KeyEvent.VK_ENTER || evt.getKeyCode() == 48 && tecla_anterior==16 || evt.getKeyCode() == 48 && tecla_anterior==16){
            op_igual();
        }else if(evt.getKeyCode() == 32){
            Speaker();
        }else if(evt.getKeyCode() == 45){
            op('-');
            audio('r');
        }else if(evt.getKeyCode() == 42 && tecla_anterior!=16 || evt.getKeyCode() == 521 && tecla_anterior!=16){
            op('+');
            audio('s');
        }else if(evt.getKeyCode() == 42 && tecla_anterior==16 || evt.getKeyCode() == 521 && tecla_anterior==16){
            op('*');
            audio('n');
        }else if(evt.getKeyCode() == 37 && tecla_anterior==16 || evt.getKeyCode() == 53 && tecla_anterior==16){
            op('%');
            audio('m');
        }else if(evt.getKeyCode() == 47 && tecla_anterior==16 || evt.getKeyCode() == 55 && tecla_anterior==16){
            op('/');
            audio('v');
        }
        else if(evt.getKeyCode() == 8){
            BorraUltimoNumero();
            audio('d');
        }
        else if(evt.getKeyCode() == 27){
            BorrarTodo();
            audio('b');
        }
        else if(evt.getKeyCode() == 46){
            MeterPto();
            audio('p');
        }
        else if(entrada=='1'){
            NuevoNumero('1');
            audio('1');
        }
        else if(entrada=='2'){
            NuevoNumero('2');
            audio('2');
        }
        else if(entrada=='3'){
            NuevoNumero('3');
            audio('3');
        }
        else if(entrada=='4'){
            NuevoNumero('4');
            audio('4');
        }
        else if(entrada=='5'){
            NuevoNumero('5');
            audio('5');
        }
        else if(entrada=='6'){
            NuevoNumero('6');
            audio('6');
        }
        else if(entrada=='7'){
            NuevoNumero('7');
            audio('7');
        }
        else if(entrada=='8'){
            NuevoNumero('8');
            audio('8');
        }
        else if(entrada=='9'){
            NuevoNumero('9');
            audio('9');
        }
        else if(entrada=='0'){
            NuevoNumero('0');
            audio('0');
        }
        tecla_anterior=evt.getKeyCode();
    }//GEN-LAST:event_formKeyPressed

    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException | InstantiationException | IllegalAccessException | javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(Calculadora.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                Calculadora v = new Calculadora();
                v.setSize(450, 500); 
                v.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
                v.setVisible(true);
                v.setLocationRelativeTo(null);
                
            }
        });
    }
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel Barra_Este;
    private javax.swing.JPanel Barra_Norte;
    private javax.swing.JButton Borra_Ultimo;
    private javax.swing.JButton Borrar_Todo;
    private javax.swing.JPanel Botones;
    private javax.swing.JButton Cero;
    private javax.swing.JButton Cinco;
    private javax.swing.JButton Cuatro;
    private javax.swing.JButton Dividir;
    private javax.swing.JButton Dos;
    private javax.swing.JButton Igual;
    private javax.swing.JButton Modulo;
    private javax.swing.JButton Multiplicar;
    private javax.swing.JButton Nueve;
    private javax.swing.JButton Ocho;
    private javax.swing.JPanel Pantalla_Abajo;
    private javax.swing.JPanel Pantalla_Arriba;
    private javax.swing.JPanel Primario;
    private javax.swing.JButton Punto;
    private javax.swing.JButton Restar;
    private javax.swing.JPanel Secundario;
    private javax.swing.JButton Seis;
    private javax.swing.JButton Siete;
    private javax.swing.JButton Speak;
    private javax.swing.JButton Sumar;
    private javax.swing.JTextField Texto_Primario;
    private javax.swing.JLabel Texto_Secundario;
    private javax.swing.JButton Tres;
    private javax.swing.JButton Uno;
    // End of variables declaration//GEN-END:variables
}
