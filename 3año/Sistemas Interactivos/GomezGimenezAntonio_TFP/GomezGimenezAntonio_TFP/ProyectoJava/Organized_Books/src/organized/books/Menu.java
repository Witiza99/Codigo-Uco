/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package organized.books;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

/**
 *
 * @author Antonio
 */
//clase que es el núcleo de la aplicación donde se encuentra casi todo el funcionamiento
//consiste en hacer visibles o no los paneles donde se llaman a las clases que contienen la interfaz correspondiente
public class Menu extends javax.swing.JPanel{

    
    ArrayList<Clase_contenedor> v_contenedores = new ArrayList();
    Componente_lbr libro_encontrado = new organized.books.Componente_lbr();
    NuevoLibroFisico nuevoLibroFisicoClase = new NuevoLibroFisico();
    NuevoLibroEbook nuevoLibroEbookClase = new NuevoLibroEbook();
    VerLibroFisico auxVerLibroFisico = new VerLibroFisico();
    VerLibroEbook auxVerLibroEbook = new VerLibroEbook();
    ModificarLibroFisico auxModificarLibroFisico = new ModificarLibroFisico();
    ModificarLibroEbook auxModificarLibroEbook = new ModificarLibroEbook();
    AlertaBorrarLibro ventanaAlertaBorrarLibro = new AlertaBorrarLibro();
    int modoFisico_o_Ebook;
    int pag_actual;
    private final java.awt.Frame padre;
    
    
    /**
     * Creates new form menu
     * @param padre
     * @param
     */
    //en el constructor se pasa el padre para las alertas, para evitar que pueda usar la aplicación y dejarse la alerta sin cerrar
    public Menu(java.awt.Frame padre) {
        initComponents();
        
        menu1.setVisible(true);
        busquedaLibro.setVisible(false);
        verLibroFisico.setVisible(false);
        modificarLibroFisico.setVisible(false);
        nuevoLibroFisico.setVisible(false);
        verLibroEbook.setVisible(false);
        modificarLibroEbook.setVisible(false);
        nuevoLibroEbook.setVisible(false);
        this.padre = padre;
    }
    
    //función que habilita y desabilita los botones, evitando problema cuanto esta en el máximo de contenedores o el mínimo
    private void desabilitar_botones(){
        try{
            if(v_contenedores.size()<=1){
                btn_siguiente.setEnabled(false);
                btn_atras.setEnabled(false);
            }else if(v_contenedores.get(0).isVisible()){
                btn_siguiente.setEnabled(true);
                btn_atras.setEnabled(false);
            }else if(v_contenedores.get(v_contenedores.size()-1).isVisible()){
                btn_siguiente.setEnabled(false);
                btn_atras.setEnabled(true);
            }else{
                btn_siguiente.setEnabled(true);
                btn_atras.setEnabled(true);
            }
        }catch(Exception e){}
    }
    
    //función para simular pantalla de carga
    /*private void carga() throws InterruptedException{
        panel_vacio.setVisible(false);
        panel_no_vacio.setVisible(true);
        panel_carga.setVisible(true);
        
        desabilitar_botones();
        long inicio = System.currentTimeMillis();
        long fin=inicio;
        double tiempo = (double) fin-inicio;
        double limite=5000;
        while(tiempo<limite){
            
            fin=System.currentTimeMillis();
            tiempo=(double) fin-inicio;
        }
        
        panel_carga.setVisible(false);
        
    }*/
    
    //función que realiza la búsqueda de un libro, ya sea ebook o libro físico, también avisa cuando no encuentra el libro por el método buscado
    private void realizar_busqueda(){
        
        //desactivamos y limpiamos vectores y paneles
        panel_vacio.setVisible(false);      
        panel_no_vacio.setVisible(true);
        contenedor_libros.removeAll();
        contenedor_libros.validate();
        contenedor_libros.setVisible(false);
        contenedor_libros.setVisible(true);
        v_contenedores.clear();
        pag_actual=0;
        
        //vemos cuantos libros hemos encontrado por el modo especificado
        int mode = modo.getSelectedIndex();
        String comparacion = textobuscador.getText();    
        ArrayList<Libro> v_librosEncontrados;
        if(modoFisico_o_Ebook==0){
            v_librosEncontrados = Bd.buscarlibro(mode, comparacion, 0);
        }else{
            v_librosEncontrados = Bd.buscarlibro(mode, comparacion, 1);
        }
        
        //comprobamos si esta vacio, si esta vacío dice el porque y sino se procede a la creación de contenedores para mostrar los libros 
        if(!v_librosEncontrados.isEmpty()){
            int posicion=0;
            Clase_contenedor contenedor_libros_aux = new Clase_contenedor();      

            for(int i=0;i<v_librosEncontrados.size();i++){
                
                //si nos hemos pasado del tamaño permitido, se crea un nuevo contenedor de libros donde metemos los componentes_lbr
                if(posicion>360){
                    contenedor_libros_aux.setSize(1090, 403);
                    contenedor_libros_aux.setLocation(0,0);
                    contenedor_libros_aux.setVisible(false);
                    v_contenedores.add(contenedor_libros_aux);
                    contenedor_libros_aux = new Clase_contenedor();
                    posicion = 0;
                    i--;
                }else{
                    libro_encontrado = new organized.books.Componente_lbr(v_librosEncontrados.get(i));
                    libro_encontrado.setSize(1090, 40);
                    libro_encontrado.setLocation(0,posicion);   
                    AccionVerLibro eventoVerLibro = new AccionVerLibro();
                    libro_encontrado.btn_NombreAutor_libro().addActionListener(eventoVerLibro);
                    contenedor_libros_aux.nuevo_componente(libro_encontrado);  
                    
                    posicion = posicion + 30;  
                }            
            }
            contenedor_libros_aux.setSize(1090, 403);
            contenedor_libros_aux.setLocation(0,0);
            contenedor_libros_aux.setVisible(false);
            v_contenedores.add(contenedor_libros_aux);
            
            //una vez hemos tenemos nuestro vector de Clase_contenedor con los libros, los volvemos invibles menos el primero que es el que se va a mostrar
            for(int i=1; i<v_contenedores.size();i++){
                v_contenedores.get(i).setVisible(false);
            }            
            v_contenedores.get(0).setVisible(true);
            
            //por último lo añadimos al panel de menu para verlo
            contenedor_libros.add(v_contenedores.get(0));
            contenedor_libros.validate();
        }else{
            //textos para explicar porque no encuentra el libro
            if(comparacion.isEmpty()){
                Label_texto_vacio.setText("Ups... Me da que se te ha olvidado añadir un texto, busca por autor o por título ;)");
            }else{
                if(mode==0){
                    Label_texto_vacio.setText("Vaya... No tienes ningún libro que se llame "+comparacion+", prueba con otro nombre :)");
                }else{
                    Label_texto_vacio.setText("Vaya... No tienes libros donde su autor se llame "+comparacion+", prueba con otro autor :)");
                }
            }
            
            panel_vacio.setVisible(true);
            panel_no_vacio.setVisible(false);
        } 
        //llamamos a la función desabilitar botones para evitar problemas en el vector
        desabilitar_botones();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     * 
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        menu1 = new FondoPanel(0);
        jLabel1 = new javax.swing.JLabel();
        boton_ebook = new FondoBoton(1);
        boton_libro =  new FondoBoton(0);
        texto_libros = new javax.swing.JLabel();
        texto_libros1 = new javax.swing.JLabel();
        componente_Carga2 = new organized.books.componente_Carga();
        componente_Carga3 = new organized.books.componente_Carga();
        busquedaLibro = new FondoPanel(1);
        boton_nuevo_librof =  new FondoBoton(4);
        lupa =  new FondoBoton(3);
        textobuscador = new javax.swing.JTextField();
        modo = new javax.swing.JComboBox<>();
        panel_vacio = new javax.swing.JPanel();
        Label_texto_vacio = new javax.swing.JLabel();
        panel_no_vacio = new javax.swing.JPanel();
        contenedor_libros = new javax.swing.JPanel();
        cont_botones_indice = new javax.swing.JPanel();
        btn_siguiente = new javax.swing.JButton();
        btn_atras = new javax.swing.JButton();
        boton_volver_menuf =  new FondoBoton(2);
        panel_carga = new javax.swing.JPanel();
        componente_Carga1 = new organized.books.componente_Carga();
        auxiliar_temp = new javax.swing.JLabel();
        verLibroFisico = new FondoPanel(2);
        botonVolverDeLibroFisicoABusqueda =  new FondoBoton(2);
        contenedorVerLibro = new javax.swing.JPanel();
        nuevoLibroFisico = new FondoPanel(2);
        contenedorNuevoLibro = new javax.swing.JPanel();
        boton_nuevo_blf =  new FondoBoton(2);
        modificarLibroFisico = new FondoPanel(2);
        contenedorModificarLibro = new javax.swing.JPanel();
        boton_volverAver_blf =  new FondoBoton(2);
        verLibroEbook = new FondoPanel(2);
        botonVolverDeLibroEbookABusqueda =  new FondoBoton(2);
        contenedorVerLibroe = new javax.swing.JPanel();
        modificarLibroEbook = new FondoPanel(2);
        contenedorModificarLibroe = new javax.swing.JPanel();
        boton_volverAver_ble =  new FondoBoton(2);
        nuevoLibroEbook = new FondoPanel(2);
        contenedorNuevoLibroe = new javax.swing.JPanel();
        boton_nuevo_blfe =  new FondoBoton(2);

        setLayout(new java.awt.FlowLayout(java.awt.FlowLayout.CENTER, 0, 0));

        menu1.setMaximumSize(new java.awt.Dimension(1366, 789));
        menu1.setMinimumSize(new java.awt.Dimension(1366, 789));
        menu1.setPreferredSize(new java.awt.Dimension(1366, 789));

        jLabel1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/nombre2.png"))); // NOI18N

        boton_ebook.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/ebook.png"))); // NOI18N
        boton_ebook.setToolTipText("");
        boton_ebook.setBorder(null);
        boton_ebook.setBorderPainted(false);
        boton_ebook.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_ebook.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_ebook.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_ebook.setOpaque(false);
        boton_ebook.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_ebook.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_ebookMouseClicked(evt);
            }
        });

        boton_libro.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/libro.png"))); // NOI18N
        boton_libro.setToolTipText("");
        boton_libro.setBorder(null);
        boton_libro.setBorderPainted(false);
        boton_libro.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_libro.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_libro.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_libro.setOpaque(false);
        boton_libro.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_libro.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_libroMouseClicked(evt);
            }
        });

        texto_libros.setFont(new java.awt.Font("Comic Sans MS", 0, 24)); // NOI18N
        texto_libros.setForeground(new java.awt.Color(240, 240, 240));
        texto_libros.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        texto_libros.setText("E-BOOKS");

        texto_libros1.setFont(new java.awt.Font("Comic Sans MS", 0, 24)); // NOI18N
        texto_libros1.setForeground(new java.awt.Color(240, 240, 240));
        texto_libros1.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        texto_libros1.setText("LIBROS");

        javax.swing.GroupLayout menu1Layout = new javax.swing.GroupLayout(menu1);
        menu1.setLayout(menu1Layout);
        menu1Layout.setHorizontalGroup(
            menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, menu1Layout.createSequentialGroup()
                .addGap(40, 40, 40)
                .addComponent(componente_Carga3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(jLabel1)
                .addGap(173, 173, 173)
                .addComponent(componente_Carga2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(44, 44, 44))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, menu1Layout.createSequentialGroup()
                .addGap(193, 193, 193)
                .addGroup(menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(boton_libro, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(texto_libros1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(texto_libros, javax.swing.GroupLayout.PREFERRED_SIZE, 256, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(boton_ebook, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(215, 215, 215))
        );
        menu1Layout.setVerticalGroup(
            menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, menu1Layout.createSequentialGroup()
                .addContainerGap(170, Short.MAX_VALUE)
                .addGroup(menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                    .addComponent(componente_Carga2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(menu1Layout.createSequentialGroup()
                        .addGroup(menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(boton_ebook, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(boton_libro, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(18, 18, 18)
                        .addGroup(menu1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                            .addComponent(texto_libros, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(texto_libros1, javax.swing.GroupLayout.PREFERRED_SIZE, 25, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(95, 95, 95)
                        .addComponent(jLabel1))
                    .addComponent(componente_Carga3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(48, 48, 48))
        );

        add(menu1);

        busquedaLibro.setMaximumSize(new java.awt.Dimension(1366, 789));
        busquedaLibro.setMinimumSize(new java.awt.Dimension(1366, 789));

        boton_nuevo_librof.setToolTipText("");
        boton_nuevo_librof.setBorder(null);
        boton_nuevo_librof.setBorderPainted(false);
        boton_nuevo_librof.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_nuevo_librof.setMaximumSize(new java.awt.Dimension(64, 64));
        boton_nuevo_librof.setMinimumSize(new java.awt.Dimension(64, 64));
        boton_nuevo_librof.setOpaque(false);
        boton_nuevo_librof.setPreferredSize(new java.awt.Dimension(64, 64));
        boton_nuevo_librof.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_nuevo_librofMouseClicked(evt);
            }
        });

        lupa.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/lupa.png"))); // NOI18N
        lupa.setToolTipText("");
        lupa.setBorder(null);
        lupa.setBorderPainted(false);
        lupa.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        lupa.setOpaque(false);
        lupa.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                lupaMouseClicked(evt);
            }
        });

        textobuscador.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        textobuscador.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));
        textobuscador.setCursor(new java.awt.Cursor(java.awt.Cursor.TEXT_CURSOR));
        textobuscador.setMargin(new java.awt.Insets(4, 4, 4, 4));
        textobuscador.setMaximumSize(new java.awt.Dimension(56, 44));
        textobuscador.setMinimumSize(new java.awt.Dimension(56, 44));
        textobuscador.setPreferredSize(new java.awt.Dimension(56, 44));
        textobuscador.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                textobuscadorKeyPressed(evt);
            }
        });

        modo.setBackground(new java.awt.Color(153, 102, 0));
        modo.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        modo.setModel(new javax.swing.DefaultComboBoxModel<>(new String[] { "Nombre del libro", "Autor" }));
        modo.setBorder(null);
        modo.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        modo.setMaximumSize(new java.awt.Dimension(107, 27));
        modo.setMinimumSize(new java.awt.Dimension(107, 27));
        modo.setPreferredSize(new java.awt.Dimension(107, 27));

        panel_vacio.setMaximumSize(new java.awt.Dimension(1090, 504));
        panel_vacio.setMinimumSize(new java.awt.Dimension(1090, 504));
        panel_vacio.setOpaque(false);
        panel_vacio.setPreferredSize(new java.awt.Dimension(1090, 504));

        Label_texto_vacio.setFont(new java.awt.Font("Comic Sans MS", 1, 14)); // NOI18N
        Label_texto_vacio.setText("Ups... Parece que no has introducido un libro o no tienes el libro buscado, inténtalo de nuevo o prueba otro libro ;)");

        javax.swing.GroupLayout panel_vacioLayout = new javax.swing.GroupLayout(panel_vacio);
        panel_vacio.setLayout(panel_vacioLayout);
        panel_vacioLayout.setHorizontalGroup(
            panel_vacioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel_vacioLayout.createSequentialGroup()
                .addGap(36, 36, 36)
                .addComponent(Label_texto_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, 991, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(63, Short.MAX_VALUE))
        );
        panel_vacioLayout.setVerticalGroup(
            panel_vacioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel_vacioLayout.createSequentialGroup()
                .addGap(49, 49, 49)
                .addComponent(Label_texto_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, 96, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(359, Short.MAX_VALUE))
        );

        panel_no_vacio.setMaximumSize(new java.awt.Dimension(1090, 504));
        panel_no_vacio.setMinimumSize(new java.awt.Dimension(1090, 504));
        panel_no_vacio.setOpaque(false);

        contenedor_libros.setMaximumSize(new java.awt.Dimension(1090, 403));
        contenedor_libros.setMinimumSize(new java.awt.Dimension(1090, 403));
        contenedor_libros.setOpaque(false);

        javax.swing.GroupLayout contenedor_librosLayout = new javax.swing.GroupLayout(contenedor_libros);
        contenedor_libros.setLayout(contenedor_librosLayout);
        contenedor_librosLayout.setHorizontalGroup(
            contenedor_librosLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedor_librosLayout.setVerticalGroup(
            contenedor_librosLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 403, Short.MAX_VALUE)
        );

        cont_botones_indice.setOpaque(false);

        btn_siguiente.setBackground(new java.awt.Color(153, 102, 0));
        btn_siguiente.setFont(new java.awt.Font("Comic Sans MS", 1, 18)); // NOI18N
        btn_siguiente.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/delante.png"))); // NOI18N
        btn_siguiente.setText("Siguiente");
        btn_siguiente.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        btn_siguiente.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);
        btn_siguiente.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btn_siguienteMouseClicked(evt);
            }
        });

        btn_atras.setBackground(new java.awt.Color(153, 102, 0));
        btn_atras.setFont(new java.awt.Font("Comic Sans MS", 1, 18)); // NOI18N
        btn_atras.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/atras (3).png"))); // NOI18N
        btn_atras.setText("Anterior");
        btn_atras.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        btn_atras.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                btn_atrasMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout cont_botones_indiceLayout = new javax.swing.GroupLayout(cont_botones_indice);
        cont_botones_indice.setLayout(cont_botones_indiceLayout);
        cont_botones_indiceLayout.setHorizontalGroup(
            cont_botones_indiceLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(cont_botones_indiceLayout.createSequentialGroup()
                .addGap(259, 259, 259)
                .addComponent(btn_atras, javax.swing.GroupLayout.PREFERRED_SIZE, 230, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(86, 86, 86)
                .addComponent(btn_siguiente, javax.swing.GroupLayout.PREFERRED_SIZE, 230, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(285, Short.MAX_VALUE))
        );
        cont_botones_indiceLayout.setVerticalGroup(
            cont_botones_indiceLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(cont_botones_indiceLayout.createSequentialGroup()
                .addGap(20, 20, 20)
                .addGroup(cont_botones_indiceLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btn_siguiente, javax.swing.GroupLayout.PREFERRED_SIZE, 55, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btn_atras, javax.swing.GroupLayout.PREFERRED_SIZE, 55, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(20, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout panel_no_vacioLayout = new javax.swing.GroupLayout(panel_no_vacio);
        panel_no_vacio.setLayout(panel_no_vacioLayout);
        panel_no_vacioLayout.setHorizontalGroup(
            panel_no_vacioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(contenedor_libros, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(cont_botones_indice, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        panel_no_vacioLayout.setVerticalGroup(
            panel_no_vacioLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel_no_vacioLayout.createSequentialGroup()
                .addComponent(contenedor_libros, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(cont_botones_indice, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
        );

        boton_volver_menuf.setToolTipText("");
        boton_volver_menuf.setBorder(null);
        boton_volver_menuf.setBorderPainted(false);
        boton_volver_menuf.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_volver_menuf.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_volver_menuf.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_volver_menuf.setOpaque(false);
        boton_volver_menuf.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_volver_menuf.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_volver_menufMouseClicked(evt);
            }
        });

        panel_carga.setMaximumSize(new java.awt.Dimension(1090, 504));
        panel_carga.setMinimumSize(new java.awt.Dimension(1090, 504));
        panel_carga.setOpaque(false);

        javax.swing.GroupLayout panel_cargaLayout = new javax.swing.GroupLayout(panel_carga);
        panel_carga.setLayout(panel_cargaLayout);
        panel_cargaLayout.setHorizontalGroup(
            panel_cargaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel_cargaLayout.createSequentialGroup()
                .addGroup(panel_cargaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(panel_cargaLayout.createSequentialGroup()
                        .addGap(464, 464, 464)
                        .addComponent(componente_Carga1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(panel_cargaLayout.createSequentialGroup()
                        .addGap(510, 510, 510)
                        .addComponent(auxiliar_temp, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(498, Short.MAX_VALUE))
        );
        panel_cargaLayout.setVerticalGroup(
            panel_cargaLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panel_cargaLayout.createSequentialGroup()
                .addGap(154, 154, 154)
                .addComponent(componente_Carga1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(auxiliar_temp, javax.swing.GroupLayout.PREFERRED_SIZE, 0, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(211, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout busquedaLibroLayout = new javax.swing.GroupLayout(busquedaLibro);
        busquedaLibro.setLayout(busquedaLibroLayout);
        busquedaLibroLayout.setHorizontalGroup(
            busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(busquedaLibroLayout.createSequentialGroup()
                .addGap(143, 143, Short.MAX_VALUE)
                .addComponent(panel_no_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(128, 128, 128))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, busquedaLibroLayout.createSequentialGroup()
                .addGap(62, 62, 62)
                .addComponent(boton_volver_menuf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addComponent(modo, javax.swing.GroupLayout.PREFERRED_SIZE, 162, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(textobuscador, javax.swing.GroupLayout.PREFERRED_SIZE, 515, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(lupa)
                .addGap(126, 126, 126)
                .addComponent(boton_nuevo_librof, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(158, 158, 158))
            .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, busquedaLibroLayout.createSequentialGroup()
                    .addContainerGap(149, Short.MAX_VALUE)
                    .addComponent(panel_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(127, 127, 127)))
            .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, busquedaLibroLayout.createSequentialGroup()
                    .addContainerGap(159, Short.MAX_VALUE)
                    .addComponent(panel_carga, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(117, 117, 117)))
        );
        busquedaLibroLayout.setVerticalGroup(
            busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(busquedaLibroLayout.createSequentialGroup()
                .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(busquedaLibroLayout.createSequentialGroup()
                        .addGap(93, 93, 93)
                        .addComponent(lupa))
                    .addGroup(busquedaLibroLayout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(boton_volver_menuf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(textobuscador, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(modo, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE))))
                    .addGroup(busquedaLibroLayout.createSequentialGroup()
                        .addGap(93, 93, 93)
                        .addComponent(boton_nuevo_librof, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGap(47, 47, 47)
                .addComponent(panel_no_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(81, Short.MAX_VALUE))
            .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, busquedaLibroLayout.createSequentialGroup()
                    .addContainerGap(205, Short.MAX_VALUE)
                    .addComponent(panel_vacio, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(80, 80, 80)))
            .addGroup(busquedaLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, busquedaLibroLayout.createSequentialGroup()
                    .addContainerGap(215, Short.MAX_VALUE)
                    .addComponent(panel_carga, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(70, 70, 70)))
        );

        add(busquedaLibro);

        verLibroFisico.setMaximumSize(new java.awt.Dimension(1366, 789));
        verLibroFisico.setMinimumSize(new java.awt.Dimension(1366, 789));

        botonVolverDeLibroFisicoABusqueda.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        botonVolverDeLibroFisicoABusqueda.setToolTipText("");
        botonVolverDeLibroFisicoABusqueda.setBorder(null);
        botonVolverDeLibroFisicoABusqueda.setBorderPainted(false);
        botonVolverDeLibroFisicoABusqueda.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        botonVolverDeLibroFisicoABusqueda.setMaximumSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroFisicoABusqueda.setMinimumSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroFisicoABusqueda.setOpaque(false);
        botonVolverDeLibroFisicoABusqueda.setPreferredSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroFisicoABusqueda.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                botonVolverDeLibroFisicoABusquedaMouseClicked(evt);
            }
        });

        contenedorVerLibro.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorVerLibro.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorVerLibro.setOpaque(false);
        contenedorVerLibro.setPreferredSize(new java.awt.Dimension(1090, 500));

        javax.swing.GroupLayout contenedorVerLibroLayout = new javax.swing.GroupLayout(contenedorVerLibro);
        contenedorVerLibro.setLayout(contenedorVerLibroLayout);
        contenedorVerLibroLayout.setHorizontalGroup(
            contenedorVerLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorVerLibroLayout.setVerticalGroup(
            contenedorVerLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout verLibroFisicoLayout = new javax.swing.GroupLayout(verLibroFisico);
        verLibroFisico.setLayout(verLibroFisicoLayout);
        verLibroFisicoLayout.setHorizontalGroup(
            verLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(verLibroFisicoLayout.createSequentialGroup()
                .addGroup(verLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(verLibroFisicoLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(botonVolverDeLibroFisicoABusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(verLibroFisicoLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorVerLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        verLibroFisicoLayout.setVerticalGroup(
            verLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(verLibroFisicoLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(botonVolverDeLibroFisicoABusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorVerLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(verLibroFisico);

        nuevoLibroFisico.setMaximumSize(new java.awt.Dimension(1366, 789));
        nuevoLibroFisico.setMinimumSize(new java.awt.Dimension(1366, 789));

        contenedorNuevoLibro.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorNuevoLibro.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorNuevoLibro.setOpaque(false);

        javax.swing.GroupLayout contenedorNuevoLibroLayout = new javax.swing.GroupLayout(contenedorNuevoLibro);
        contenedorNuevoLibro.setLayout(contenedorNuevoLibroLayout);
        contenedorNuevoLibroLayout.setHorizontalGroup(
            contenedorNuevoLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorNuevoLibroLayout.setVerticalGroup(
            contenedorNuevoLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        boton_nuevo_blf.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        boton_nuevo_blf.setToolTipText("");
        boton_nuevo_blf.setBorder(null);
        boton_nuevo_blf.setBorderPainted(false);
        boton_nuevo_blf.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_nuevo_blf.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blf.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blf.setOpaque(false);
        boton_nuevo_blf.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blf.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_nuevo_blfMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout nuevoLibroFisicoLayout = new javax.swing.GroupLayout(nuevoLibroFisico);
        nuevoLibroFisico.setLayout(nuevoLibroFisicoLayout);
        nuevoLibroFisicoLayout.setHorizontalGroup(
            nuevoLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(nuevoLibroFisicoLayout.createSequentialGroup()
                .addGroup(nuevoLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(nuevoLibroFisicoLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(boton_nuevo_blf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(nuevoLibroFisicoLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorNuevoLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        nuevoLibroFisicoLayout.setVerticalGroup(
            nuevoLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(nuevoLibroFisicoLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(boton_nuevo_blf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorNuevoLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(nuevoLibroFisico);

        modificarLibroFisico.setMaximumSize(new java.awt.Dimension(1366, 789));
        modificarLibroFisico.setMinimumSize(new java.awt.Dimension(1366, 789));

        contenedorModificarLibro.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorModificarLibro.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorModificarLibro.setOpaque(false);

        javax.swing.GroupLayout contenedorModificarLibroLayout = new javax.swing.GroupLayout(contenedorModificarLibro);
        contenedorModificarLibro.setLayout(contenedorModificarLibroLayout);
        contenedorModificarLibroLayout.setHorizontalGroup(
            contenedorModificarLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorModificarLibroLayout.setVerticalGroup(
            contenedorModificarLibroLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        boton_volverAver_blf.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        boton_volverAver_blf.setToolTipText("");
        boton_volverAver_blf.setBorder(null);
        boton_volverAver_blf.setBorderPainted(false);
        boton_volverAver_blf.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_volverAver_blf.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_volverAver_blf.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_volverAver_blf.setOpaque(false);
        boton_volverAver_blf.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_volverAver_blf.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_volverAver_blfMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout modificarLibroFisicoLayout = new javax.swing.GroupLayout(modificarLibroFisico);
        modificarLibroFisico.setLayout(modificarLibroFisicoLayout);
        modificarLibroFisicoLayout.setHorizontalGroup(
            modificarLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modificarLibroFisicoLayout.createSequentialGroup()
                .addGroup(modificarLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(modificarLibroFisicoLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(boton_volverAver_blf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(modificarLibroFisicoLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorModificarLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        modificarLibroFisicoLayout.setVerticalGroup(
            modificarLibroFisicoLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modificarLibroFisicoLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(boton_volverAver_blf, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorModificarLibro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(modificarLibroFisico);

        verLibroEbook.setMaximumSize(new java.awt.Dimension(1366, 789));
        verLibroEbook.setMinimumSize(new java.awt.Dimension(1366, 789));

        botonVolverDeLibroEbookABusqueda.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        botonVolverDeLibroEbookABusqueda.setToolTipText("");
        botonVolverDeLibroEbookABusqueda.setBorder(null);
        botonVolverDeLibroEbookABusqueda.setBorderPainted(false);
        botonVolverDeLibroEbookABusqueda.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        botonVolverDeLibroEbookABusqueda.setMaximumSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroEbookABusqueda.setMinimumSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroEbookABusqueda.setOpaque(false);
        botonVolverDeLibroEbookABusqueda.setPreferredSize(new java.awt.Dimension(256, 256));
        botonVolverDeLibroEbookABusqueda.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                botonVolverDeLibroEbookABusquedaMouseClicked(evt);
            }
        });

        contenedorVerLibroe.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorVerLibroe.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorVerLibroe.setOpaque(false);

        javax.swing.GroupLayout contenedorVerLibroeLayout = new javax.swing.GroupLayout(contenedorVerLibroe);
        contenedorVerLibroe.setLayout(contenedorVerLibroeLayout);
        contenedorVerLibroeLayout.setHorizontalGroup(
            contenedorVerLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorVerLibroeLayout.setVerticalGroup(
            contenedorVerLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout verLibroEbookLayout = new javax.swing.GroupLayout(verLibroEbook);
        verLibroEbook.setLayout(verLibroEbookLayout);
        verLibroEbookLayout.setHorizontalGroup(
            verLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(verLibroEbookLayout.createSequentialGroup()
                .addGroup(verLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(verLibroEbookLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(botonVolverDeLibroEbookABusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(verLibroEbookLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorVerLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        verLibroEbookLayout.setVerticalGroup(
            verLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(verLibroEbookLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(botonVolverDeLibroEbookABusqueda, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorVerLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(verLibroEbook);

        modificarLibroEbook.setMaximumSize(new java.awt.Dimension(1366, 789));
        modificarLibroEbook.setMinimumSize(new java.awt.Dimension(1366, 789));

        contenedorModificarLibroe.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorModificarLibroe.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorModificarLibroe.setOpaque(false);

        javax.swing.GroupLayout contenedorModificarLibroeLayout = new javax.swing.GroupLayout(contenedorModificarLibroe);
        contenedorModificarLibroe.setLayout(contenedorModificarLibroeLayout);
        contenedorModificarLibroeLayout.setHorizontalGroup(
            contenedorModificarLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorModificarLibroeLayout.setVerticalGroup(
            contenedorModificarLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        boton_volverAver_ble.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        boton_volverAver_ble.setToolTipText("");
        boton_volverAver_ble.setBorder(null);
        boton_volverAver_ble.setBorderPainted(false);
        boton_volverAver_ble.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_volverAver_ble.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_volverAver_ble.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_volverAver_ble.setOpaque(false);
        boton_volverAver_ble.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_volverAver_ble.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_volverAver_bleMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout modificarLibroEbookLayout = new javax.swing.GroupLayout(modificarLibroEbook);
        modificarLibroEbook.setLayout(modificarLibroEbookLayout);
        modificarLibroEbookLayout.setHorizontalGroup(
            modificarLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modificarLibroEbookLayout.createSequentialGroup()
                .addGroup(modificarLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(modificarLibroEbookLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(boton_volverAver_ble, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(modificarLibroEbookLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorModificarLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        modificarLibroEbookLayout.setVerticalGroup(
            modificarLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(modificarLibroEbookLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(boton_volverAver_ble, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorModificarLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(modificarLibroEbook);

        nuevoLibroEbook.setMaximumSize(new java.awt.Dimension(1366, 789));
        nuevoLibroEbook.setMinimumSize(new java.awt.Dimension(1366, 789));

        contenedorNuevoLibroe.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedorNuevoLibroe.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedorNuevoLibroe.setOpaque(false);

        javax.swing.GroupLayout contenedorNuevoLibroeLayout = new javax.swing.GroupLayout(contenedorNuevoLibroe);
        contenedorNuevoLibroe.setLayout(contenedorNuevoLibroeLayout);
        contenedorNuevoLibroeLayout.setHorizontalGroup(
            contenedorNuevoLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 1090, Short.MAX_VALUE)
        );
        contenedorNuevoLibroeLayout.setVerticalGroup(
            contenedorNuevoLibroeLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 500, Short.MAX_VALUE)
        );

        boton_nuevo_blfe.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/flecha.png"))); // NOI18N
        boton_nuevo_blfe.setToolTipText("");
        boton_nuevo_blfe.setBorder(null);
        boton_nuevo_blfe.setBorderPainted(false);
        boton_nuevo_blfe.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        boton_nuevo_blfe.setMaximumSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blfe.setMinimumSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blfe.setOpaque(false);
        boton_nuevo_blfe.setPreferredSize(new java.awt.Dimension(256, 256));
        boton_nuevo_blfe.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                boton_nuevo_blfeMouseClicked(evt);
            }
        });

        javax.swing.GroupLayout nuevoLibroEbookLayout = new javax.swing.GroupLayout(nuevoLibroEbook);
        nuevoLibroEbook.setLayout(nuevoLibroEbookLayout);
        nuevoLibroEbookLayout.setHorizontalGroup(
            nuevoLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(nuevoLibroEbookLayout.createSequentialGroup()
                .addGroup(nuevoLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(nuevoLibroEbookLayout.createSequentialGroup()
                        .addGap(64, 64, 64)
                        .addComponent(boton_nuevo_blfe, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(nuevoLibroEbookLayout.createSequentialGroup()
                        .addGap(131, 131, 131)
                        .addComponent(contenedorNuevoLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap(145, Short.MAX_VALUE))
        );
        nuevoLibroEbookLayout.setVerticalGroup(
            nuevoLibroEbookLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(nuevoLibroEbookLayout.createSequentialGroup()
                .addGap(28, 28, 28)
                .addComponent(boton_nuevo_blfe, javax.swing.GroupLayout.PREFERRED_SIZE, 116, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(contenedorNuevoLibroe, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap(139, Short.MAX_VALUE))
        );

        add(nuevoLibroEbook);
    }// </editor-fold>//GEN-END:initComponents

    //boton que nos lleva desde el menu hasta la busqueda de libros en modo ebooks
    private void boton_ebookMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_ebookMouseClicked
       modoFisico_o_Ebook=1;
       menu1.setVisible(false);
       busquedaLibro.setVisible(true);
       verLibroEbook.setVisible(false);
       nuevoLibroEbook.setVisible(false);
       panel_no_vacio.setVisible(false);
       panel_carga.setVisible(false);
       Label_texto_vacio.setText("Introduce algún libro o autor y si es posible te daré una respuesta : )");
       panel_vacio.setVisible(true);
    }//GEN-LAST:event_boton_ebookMouseClicked

    //boton que nos lleva desde el menu hasta la busqueda de libros en modo libros físicos
    private void boton_libroMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_libroMouseClicked
       modoFisico_o_Ebook=0;
       menu1.setVisible(false);

       busquedaLibro.setVisible(true);
       verLibroFisico.setVisible(false);
       nuevoLibroFisico.setVisible(false);
       panel_no_vacio.setVisible(false);
       panel_carga.setVisible(false);
       Label_texto_vacio.setText("Introduce algún libro o autor y si es posible te daré una respuesta : )");
       panel_vacio.setVisible(true);
        /*try {
            carga();
        } catch (InterruptedException ex) {
            Logger.getLogger(Menu.class.getName()).log(Level.SEVERE, null, ex);
        }*/
    }//GEN-LAST:event_boton_libroMouseClicked

    //boton que nos lleva desde busqueda de libros hasta nuevoLibroFísico o nuevoLibroEbook (a los paneles de menú, después se le añaden la clase apoyo), 
    //según el modo en el que nos encontremos
    private void boton_nuevo_librofMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_nuevo_librofMouseClicked
        busquedaLibro.setVisible(false);
        
        if(modoFisico_o_Ebook==0){
            contenedorNuevoLibro.removeAll();
            contenedorNuevoLibro.validate();

            nuevoLibroFisicoClase = new NuevoLibroFisico();
            nuevoLibroFisicoClase.setSize(1090, 500);
            nuevoLibroFisicoClase.setLocation(0,0); 

            AccionInsertarLibro eventoVerLibro = new AccionInsertarLibro();
            nuevoLibroFisicoClase.getBtn_aceptaNuevoLibro().addActionListener (eventoVerLibro);

            contenedorNuevoLibro.add(nuevoLibroFisicoClase);
            contenedorNuevoLibro.setVisible(true);
            nuevoLibroFisico.setVisible(true);
        }else{
            contenedorNuevoLibroe.removeAll();
            contenedorNuevoLibroe.validate();
System.out.print("hola");
            nuevoLibroEbookClase = new NuevoLibroEbook();
            nuevoLibroEbookClase.setSize(1090, 500);
            nuevoLibroEbookClase.setLocation(0,0); 

            AccionInsertarLibro eventoVerLibro = new AccionInsertarLibro();
            nuevoLibroEbookClase.getBtn_aceptaNuevoLibro().addActionListener (eventoVerLibro);

            contenedorNuevoLibroe.add(nuevoLibroEbookClase);
            contenedorNuevoLibroe.setVisible(true);
            nuevoLibroEbook.setVisible(true);
        }
        
    }//GEN-LAST:event_boton_nuevo_librofMouseClicked

    //boton de la lupa en busqueda de libros que realiza la busqueda
    private void lupaMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_lupaMouseClicked
        /*try {
            carga();
        } catch (InterruptedException ex) {
            Logger.getLogger(Menu.class.getName()).log(Level.SEVERE, null, ex);
        }*/
        realizar_busqueda();
    }//GEN-LAST:event_lupaMouseClicked

    //boton que aparece cuando si existen libros, nos permite movernos hacia delante entre los elementos del vector v_contenedores
    //donde se encuentran la clase auxiliar (Clase_contenedor) con los libros
    private void btn_siguienteMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btn_siguienteMouseClicked
        try{
            contenedor_libros.add(v_contenedores.get(pag_actual+1));
            contenedor_libros.removeAll();
            contenedor_libros.validate();
            contenedor_libros.setVisible(false);
            contenedor_libros.setVisible(true);
            v_contenedores.get(pag_actual).setVisible(false);
            v_contenedores.get(pag_actual+1).setVisible(true);
            contenedor_libros.add(v_contenedores.get(pag_actual+1));
            contenedor_libros.validate();
            pag_actual++;
            desabilitar_botones();           
        }catch(Exception e){}   
    }//GEN-LAST:event_btn_siguienteMouseClicked

    //boton que aparece cuando si existen libros, nos permite movernos hacia detras entre los elementos del vector v_contenedores
    //donde se encuentran la clase auxiliar (Clase_contenedor) con los libros
    private void btn_atrasMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btn_atrasMouseClicked
        try{
            v_contenedores.get(pag_actual-1).setVisible(true);
            contenedor_libros.removeAll();
            contenedor_libros.validate();
            contenedor_libros.setVisible(false);
            contenedor_libros.setVisible(true);
            v_contenedores.get(pag_actual).setVisible(false);
            v_contenedores.get(pag_actual-1).setVisible(true);
            contenedor_libros.add(v_contenedores.get(pag_actual-1));
            contenedor_libros.validate();
            pag_actual--;
            desabilitar_botones();
        }catch(Exception e){}
    }//GEN-LAST:event_btn_atrasMouseClicked

    //boton de enter en la búsqueda de libros que realiza la busqueda
    private void textobuscadorKeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_textobuscadorKeyPressed
        if(evt.getKeyCode() == java.awt.event.KeyEvent.VK_ENTER || evt.getKeyCode() == 48){
            /*try {
                carga();
            } catch (InterruptedException ex) {
                Logger.getLogger(Menu.class.getName()).log(Level.SEVERE, null, ex);
            }*/
            realizar_busqueda();
        }     
    }//GEN-LAST:event_textobuscadorKeyPressed

    //boton que permite volver de verLibroFísico a la busqueda de libros
    private void botonVolverDeLibroFisicoABusquedaMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_botonVolverDeLibroFisicoABusquedaMouseClicked
       verLibroFisico.setVisible(false);
       realizar_busqueda();
       busquedaLibro.setVisible(true);
    }//GEN-LAST:event_botonVolverDeLibroFisicoABusquedaMouseClicked

    //boton que permite volver de la busqueda de libros al menu
    private void boton_volver_menufMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_volver_menufMouseClicked
       busquedaLibro.setVisible(false);
       menu1.setVisible(true);
    }//GEN-LAST:event_boton_volver_menufMouseClicked

    //boton que permite volver de nuevoLibroFisico a la busqueda de libros
    private void boton_nuevo_blfMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_nuevo_blfMouseClicked
        nuevoLibroFisico.setVisible(false);    
        busquedaLibro.setVisible(true);
    }//GEN-LAST:event_boton_nuevo_blfMouseClicked

    //boton que permite volver de verLibroEbook a la busqueda de libros
    private void botonVolverDeLibroEbookABusquedaMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_botonVolverDeLibroEbookABusquedaMouseClicked
       verLibroEbook.setVisible(false);
       realizar_busqueda();
       busquedaLibro.setVisible(true);
    }//GEN-LAST:event_botonVolverDeLibroEbookABusquedaMouseClicked

    //boton que permite volver de modificarLibroEbook a verLibroEbook
    private void boton_volverAver_bleMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_volverAver_bleMouseClicked
       modificarLibroEbook.setVisible(false);
       verLibroEbook.setVisible(true);
    }//GEN-LAST:event_boton_volverAver_bleMouseClicked

    //boton que permite volver de modificarLibroFisico a verLibroFisico
    private void boton_volverAver_blfMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_volverAver_blfMouseClicked
       modificarLibroFisico.setVisible(false);
       verLibroFisico.setVisible(true);
    }//GEN-LAST:event_boton_volverAver_blfMouseClicked

    //boton que permite volver de nuevoLibroEbook a la busqueda de libros
    private void boton_nuevo_blfeMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_boton_nuevo_blfeMouseClicked
       nuevoLibroEbook.setVisible(false);    
       busquedaLibro.setVisible(true);
    }//GEN-LAST:event_boton_nuevo_blfeMouseClicked


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel Label_texto_vacio;
    private javax.swing.JLabel auxiliar_temp;
    private javax.swing.JButton botonVolverDeLibroEbookABusqueda;
    private javax.swing.JButton botonVolverDeLibroFisicoABusqueda;
    private javax.swing.JButton boton_ebook;
    private javax.swing.JButton boton_libro;
    private javax.swing.JButton boton_nuevo_blf;
    private javax.swing.JButton boton_nuevo_blfe;
    private javax.swing.JButton boton_nuevo_librof;
    private javax.swing.JButton boton_volverAver_ble;
    private javax.swing.JButton boton_volverAver_blf;
    private javax.swing.JButton boton_volver_menuf;
    private javax.swing.JButton btn_atras;
    private javax.swing.JButton btn_siguiente;
    private javax.swing.JPanel busquedaLibro;
    private organized.books.componente_Carga componente_Carga1;
    private organized.books.componente_Carga componente_Carga2;
    private organized.books.componente_Carga componente_Carga3;
    private javax.swing.JPanel cont_botones_indice;
    private javax.swing.JPanel contenedorModificarLibro;
    private javax.swing.JPanel contenedorModificarLibroe;
    private javax.swing.JPanel contenedorNuevoLibro;
    private javax.swing.JPanel contenedorNuevoLibroe;
    private javax.swing.JPanel contenedorVerLibro;
    private javax.swing.JPanel contenedorVerLibroe;
    private javax.swing.JPanel contenedor_libros;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JButton lupa;
    private javax.swing.JPanel menu1;
    private javax.swing.JPanel modificarLibroEbook;
    private javax.swing.JPanel modificarLibroFisico;
    private javax.swing.JComboBox<String> modo;
    private javax.swing.JPanel nuevoLibroEbook;
    private javax.swing.JPanel nuevoLibroFisico;
    private javax.swing.JPanel panel_carga;
    private javax.swing.JPanel panel_no_vacio;
    private javax.swing.JPanel panel_vacio;
    private javax.swing.JLabel texto_libros;
    private javax.swing.JLabel texto_libros1;
    private javax.swing.JTextField textobuscador;
    private javax.swing.JPanel verLibroEbook;
    private javax.swing.JPanel verLibroFisico;
    // End of variables declaration//GEN-END:variables
    
    
    //aqui se han creado varias clases, estas clases se han utilizado cuando queríamos controlar algún boton que se encontraba
    //interno en las clases de apoyo y era necesario ver si se activaban para realizar cambios a los paneles en el menu
    //por ello se han creado estas clases que comprueban si se activa un evento y si este coincide con el que busco
    
    //cabe destacar que cada método creado aquí es necesario para que funcione añadirlo al botón donde queremos que se aplique
    
    //comprueba si se activa el boton ver libro que se encuentra en el Componente_lbr
    public class AccionVerLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{
            //se recorren todos los contenedores con todos los libros para ver si la acción recibida coincide con algún ver libro
            for(int i=0; i<v_contenedores.size();i++){
                for(int j=0; j<v_contenedores.get(i).getV_botoneslibros().size();j++){
                    if(ae.getSource().equals(v_contenedores.get(i).getV_botoneslibros().get(j))){
                        //en el caso de que coincida vemos la id del libro para asi poder enviarle este id a la clase VerLibro (funciona para los dos metodos)
                        //de esta forma cuando se cree la clase se añade al panel del menu contenedorVerLibro en el caso de libro físico
                        //o contenedorVerLibroe en el caso de libro ebook. Por último se vuelve visible y se vuelve invisible busquedaLibro
                        int id=v_contenedores.get(i).getV_librosId().get(j);

                        busquedaLibro.setVisible(false);
                        contenedorVerLibro.removeAll();
                        contenedorVerLibro.validate();
                        
                        if(modoFisico_o_Ebook==0){
                            auxVerLibroFisico = new VerLibroFisico(id);
                            auxVerLibroFisico.setSize(1090, 500);
                            auxVerLibroFisico.setLocation(0,0); 

                            Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                            auxVerLibroFisico.getBoton_modificar_librof().addActionListener(eventoIraModificarLibro);


                            contenedorVerLibro.removeAll();
                            contenedorVerLibro.validate();
                            contenedorVerLibro.add(auxVerLibroFisico);
                            contenedorVerLibro.setVisible(true);
                            verLibroFisico.setVisible(true);
                        }else{
                            auxVerLibroEbook = new VerLibroEbook(id);
                            auxVerLibroEbook.setSize(1090, 500);
                            auxVerLibroEbook.setLocation(0,0); 

                            Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                            auxVerLibroEbook.getBoton_modificar_libroe().addActionListener(eventoIraModificarLibro);


                            contenedorVerLibroe.removeAll();
                            contenedorVerLibroe.validate();
                            contenedorVerLibroe.add(auxVerLibroEbook);
                            contenedorVerLibroe.setVisible(true);
                            verLibroEbook.setVisible(true);
                        }
                        
                        
                        //una vez encontrado no tiene sentido seguir con el bucle
                        i=v_contenedores.size();   
                    }  
                }
            }
        }catch(Exception e){} 
      }
   } 
    
    //comprueba si se activa el boton de insertar libro, dándole al boton aceptar
    public class AccionInsertarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{ 
            if(modoFisico_o_Ebook==0){
                if(ae.getSource().equals(nuevoLibroFisicoClase.getBtn_aceptaNuevoLibro())){
                    if(nuevoLibroFisicoClase.hayError()){
                        new Error(padre,true).setVisible(true); 
                    }else{
                        nuevoLibroFisicoClase.insertarLibro();
                        new Acceptar(padre,true).setVisible(true);
                        nuevoLibroFisico.setVisible(false);       

                        auxVerLibroFisico = new VerLibroFisico(nuevoLibroFisicoClase.getId());
                        auxVerLibroFisico.setSize(1090, 500);
                        auxVerLibroFisico.setLocation(0,0); 

                        Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                        auxVerLibroFisico.getBoton_modificar_librof().addActionListener(eventoIraModificarLibro);


                        contenedorVerLibro.removeAll();
                        contenedorVerLibro.validate();
                        contenedorVerLibro.add(auxVerLibroFisico);
                        contenedorVerLibro.setVisible(true);
                        verLibroFisico.setVisible(true);
                    }         
                }
            }else{
                if(ae.getSource().equals(nuevoLibroEbookClase.getBtn_aceptaNuevoLibro())){
                    if(nuevoLibroEbookClase.hayError()){
                        new Error(padre,true).setVisible(true); 
                    }else{
                        nuevoLibroEbookClase.insertarLibro();
                        new Acceptar(padre,true).setVisible(true);
                        nuevoLibroEbook.setVisible(false);       

                        auxVerLibroEbook = new VerLibroEbook(nuevoLibroEbookClase.getId());
                        auxVerLibroEbook.setSize(1090, 500);
                        auxVerLibroEbook.setLocation(0,0); 

                        Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                        auxVerLibroEbook.getBoton_modificar_libroe().addActionListener(eventoIraModificarLibro);


                        contenedorVerLibroe.removeAll();
                        contenedorVerLibroe.validate();
                        contenedorVerLibroe.add(auxVerLibroEbook);
                        contenedorVerLibroe.setVisible(true);
                        verLibroEbook.setVisible(true);
                    }         
                }
            }
            
        }catch(Exception e){} 
      }
   } 
    
    //comprueba si se activa el boton de ir a ModificarLibro, dándole al boton modificar libro que se encuentra dentro de verLibro
    //funciona para VerLibroFisico como verLibroEbook, simplemente se ve el modo en el que estamos
    public class Ir_a_ModificarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{   
            
            if(modoFisico_o_Ebook==0){
                if(ae.getSource().equals(auxVerLibroFisico.getBoton_modificar_librof())){
                
                    verLibroFisico.setVisible(false);
                    auxModificarLibroFisico = new ModificarLibroFisico(auxVerLibroFisico.getId());
                    auxModificarLibroFisico.setSize(1090, 500);
                    auxModificarLibroFisico.setLocation(0,0); 


                    btn_ModificarLibro aceptarModificarLibro = new btn_ModificarLibro();
                    auxModificarLibroFisico.getBtn_aceptaModificacionLibro().addActionListener(aceptarModificarLibro);

                    btn_BorrarLibro Borrar_Libro = new btn_BorrarLibro();
                    auxModificarLibroFisico.getBtn_BorrarLibro().addActionListener(Borrar_Libro);


                    contenedorModificarLibro.removeAll();
                    contenedorModificarLibro.validate();
                    contenedorModificarLibro.add(auxModificarLibroFisico);
                    contenedorModificarLibro.setVisible(true);

                    modificarLibroFisico.setVisible(true);

                }
            }else{
               if(ae.getSource().equals(auxVerLibroEbook.getBoton_modificar_libroe())){
                
                    verLibroEbook.setVisible(false);
                    auxModificarLibroEbook = new ModificarLibroEbook(auxVerLibroEbook.getId());
                    auxModificarLibroEbook.setSize(1090, 500);
                    auxModificarLibroEbook.setLocation(0,0); 


                    btn_ModificarLibro aceptarModificarLibro = new btn_ModificarLibro();
                    auxModificarLibroEbook.getBtn_aceptaModificacionLibro().addActionListener(aceptarModificarLibro);

                    btn_BorrarLibro Borrar_Libro = new btn_BorrarLibro();
                    auxModificarLibroEbook.getBtn_BorrarLibro().addActionListener(Borrar_Libro);


                    contenedorModificarLibroe.removeAll();
                    contenedorModificarLibroe.validate();
                    contenedorModificarLibroe.add(auxModificarLibroEbook);
                    contenedorModificarLibroe.setVisible(true);

                    modificarLibroEbook.setVisible(true);

                } 
            }
            
        }catch(Exception e){} 
      }
   } 
    
    //comprueba si se activa el boton ModificarLibro, dándole al boton aceptar que se encuentra dentro de modificarLibro
    //funciona para ModificarLibroFisico como ModificarLibroEbook, simplemente se ve el modo en el que estamos
    public class btn_ModificarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{
            if(modoFisico_o_Ebook==0){
                if(ae.getSource().equals(auxModificarLibroFisico.getBtn_aceptaModificacionLibro())){
                
                    if(auxModificarLibroFisico.hayError()){
                        new Error(padre,true).setVisible(true); 
                    }else{
                        auxModificarLibroFisico.ModificarLibro();
                        new Acceptar(padre,true).setVisible(true);
                        auxModificarLibroFisico.setVisible(false);       

                        auxVerLibroFisico = new VerLibroFisico(auxModificarLibroFisico.getId());
                        auxVerLibroFisico.setSize(1090, 500);
                        auxVerLibroFisico.setLocation(0,0); 

                        Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                        auxVerLibroFisico.getBoton_modificar_librof().addActionListener(eventoIraModificarLibro);                  

                        contenedorVerLibro.removeAll();
                        contenedorVerLibro.validate();
                        contenedorVerLibro.add(auxVerLibroFisico);
                        contenedorVerLibro.setVisible(true);
                        modificarLibroFisico.setVisible(false);
                        verLibroFisico.setVisible(true);
                    } 
                }
            }else{
                if(ae.getSource().equals(auxModificarLibroEbook.getBtn_aceptaModificacionLibro())){
                
                    if(auxModificarLibroEbook.hayError()){
                        new Error(padre,true).setVisible(true); 
                    }else{
                        auxModificarLibroEbook.ModificarLibro();
                        new Acceptar(padre,true).setVisible(true);
                        auxModificarLibroEbook.setVisible(false);       

                        auxVerLibroEbook = new VerLibroEbook(auxModificarLibroEbook.getId());
                        auxVerLibroEbook.setSize(1090, 500);
                        auxVerLibroEbook.setLocation(0,0); 

                        Ir_a_ModificarLibro eventoIraModificarLibro = new Ir_a_ModificarLibro();
                        auxVerLibroEbook.getBoton_modificar_libroe().addActionListener(eventoIraModificarLibro);                  

                        contenedorVerLibroe.removeAll();
                        contenedorVerLibroe.validate();
                        contenedorVerLibroe.add(auxVerLibroEbook);
                        contenedorVerLibroe.setVisible(true);
                        modificarLibroEbook.setVisible(false);//es necesario volver invisible modificar anterior, sino ocurren problemas
                        verLibroEbook.setVisible(true);
                    } 
                }
            }
            
        }catch(Exception e){} 
      }
   } 
    
   //comprueba si se activa el boton BorrarLibro, dándole al boton borrar que se encuentra dentro de modificarLibro
   //funciona para ModificarLibroFisico como ModificarLibroEbook, simplemente se ve el modo en el que estamos 
   public class btn_BorrarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{   
            if(ae.getSource().equals(auxModificarLibroFisico.getBtn_BorrarLibro())||ae.getSource().equals(auxModificarLibroEbook.getBtn_BorrarLibro())){
                
                ventanaAlertaBorrarLibro = new AlertaBorrarLibro(padre,true);
                
                btn_AceptarBorrarLibro eventoAceptarBorrarLibro = new btn_AceptarBorrarLibro();
                ventanaAlertaBorrarLibro.getBtn_aceptaBorrar().addActionListener(eventoAceptarBorrarLibro);
                
                btn_RechazarBorrarLibro eventoRechazarBorrarLibro = new btn_RechazarBorrarLibro();
                ventanaAlertaBorrarLibro.getBtn_aceptaCancelarBorrar().addActionListener(eventoRechazarBorrarLibro);
                
                ventanaAlertaBorrarLibro.setVisible(true);
                
            }
        }catch(Exception e){} 
      }
   } 
   
   //comprueba si se activa el boton AceptarBorrarLibro, dándole al boton aceptar que se encuentra dentro de Borrar
   //borra libros fisicos y Ebooks
   public class btn_AceptarBorrarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{   
            if(ae.getSource().equals(ventanaAlertaBorrarLibro.getBtn_aceptaBorrar())){
                ventanaAlertaBorrarLibro.dispose();
                
                new AlertaLibroBorrado(padre,true).setVisible(true);
                if(modoFisico_o_Ebook==0){
                    Bd.borrarLibro(auxModificarLibroFisico.getId(), 0);
                    modificarLibroFisico.setVisible(false);
                    realizar_busqueda();
                    busquedaLibro.setVisible(true);
                }else{
                    Bd.borrarLibro(auxModificarLibroFisico.getId(), 1);
                    modificarLibroEbook.setVisible(false);
                    realizar_busqueda();
                    busquedaLibro.setVisible(true);   
                }
        
            }
        }catch(Exception e){} 
      }
   } 
   
   //comprueba si se activa el boton RechazarBorrarLibro, dándole al boton cancelar que se encuentra dentro de Borrar
   public class btn_RechazarBorrarLibro implements ActionListener
   {
      @Override
      public void actionPerformed(ActionEvent ae){
        
        try{   
            if(ae.getSource().equals(ventanaAlertaBorrarLibro.getBtn_aceptaCancelarBorrar())){
                
                ventanaAlertaBorrarLibro.dispose();               
                      
            }
        }catch(Exception e){} 
      }
   } 
   
}

