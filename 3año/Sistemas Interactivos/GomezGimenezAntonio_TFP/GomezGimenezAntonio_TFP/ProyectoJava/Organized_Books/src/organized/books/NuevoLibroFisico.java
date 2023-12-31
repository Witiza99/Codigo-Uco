/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package organized.books;

import javax.swing.JButton;



/**
 *
 * @author Antonio
 */

//clase que contiene la interfaz para añadir un libro Fisico
public class NuevoLibroFisico extends javax.swing.JPanel {
    
    /**
     * Creates new form VerLibroFísico
     */
    
    
    int id;
    ComponenteNota comp_nota = new ComponenteNota();
    
  
    
    public NuevoLibroFisico() {
        initComponents();

        id=Bd.getUltimoId(0);
        id++;
        campo_autor.setText("");
        campo_lugar.setText("");
        campo_nombre.setText("");
        campo_resumen.setText("");
        comp_nota.setSize(242, 171);
        comp_nota.setLocation(159,285); 
        contenedor.add(comp_nota);
        contenedor.setVisible(true);
        }

    public JButton getBtn_aceptaNuevoLibro() {
        return btn_aceptaNuevoLibro;
    }

    public boolean hayError(){
        return campo_autor.getText().isEmpty()||campo_lugar.getText().isEmpty()||campo_nombre.getText().isEmpty()||campo_resumen.getText().isEmpty();
    }
    
    public void insertarLibro(){
        Libro libro_elegido = new Libro(id, campo_nombre.getText(), campo_autor.getText(), campo_resumen.getText(), campo_lugar.getText(), comp_nota.getNota());
        Bd.insertarLibro(libro_elegido, 0);
    }

    public int getId() {
        return id;
    }
    

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        contenedor = new FondoPanel(3);
        label_autor = new javax.swing.JLabel();
        campo_lugar = new javax.swing.JTextField();
        label_resumen = new javax.swing.JLabel();
        label_titulo = new javax.swing.JLabel();
        campo_nombre = new javax.swing.JTextField();
        label_lugar = new javax.swing.JLabel();
        campo_autor = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        campo_resumen = new javax.swing.JTextArea();
        label_nota = new javax.swing.JLabel();
        btn_aceptaNuevoLibro = new javax.swing.JButton();

        setMaximumSize(new java.awt.Dimension(1090, 500));
        setMinimumSize(new java.awt.Dimension(1090, 500));
        setPreferredSize(new java.awt.Dimension(1090, 500));

        contenedor.setMaximumSize(new java.awt.Dimension(1090, 500));
        contenedor.setMinimumSize(new java.awt.Dimension(1090, 500));
        contenedor.setPreferredSize(new java.awt.Dimension(1090, 500));

        label_autor.setFont(new java.awt.Font("Comic Sans MS", 1, 14)); // NOI18N
        label_autor.setText("Autor/a");

        campo_lugar.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        campo_lugar.setText("jTextField1");
        campo_lugar.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        label_resumen.setFont(new java.awt.Font("Comic Sans MS", 1, 14)); // NOI18N
        label_resumen.setText("Resumen:");

        label_titulo.setFont(new java.awt.Font("Comic Sans MS", 1, 14)); // NOI18N
        label_titulo.setText("Título:");

        campo_nombre.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        campo_nombre.setText("jTextField1");
        campo_nombre.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        label_lugar.setFont(new java.awt.Font("Comic Sans MS", 1, 14)); // NOI18N
        label_lugar.setText("Lugar");

        campo_autor.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        campo_autor.setText("jTextField1");
        campo_autor.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        campo_resumen.setColumns(20);
        campo_resumen.setFont(new java.awt.Font("Comic Sans MS", 1, 12)); // NOI18N
        campo_resumen.setLineWrap(true);
        campo_resumen.setRows(5);
        campo_resumen.setWrapStyleWord(true);
        campo_resumen.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));
        jScrollPane1.setViewportView(campo_resumen);

        label_nota.setFont(new java.awt.Font("Comic Sans MS", 1, 18)); // NOI18N
        label_nota.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        label_nota.setText("Nota:");

        btn_aceptaNuevoLibro.setBackground(new java.awt.Color(153, 102, 0));
        btn_aceptaNuevoLibro.setFont(new java.awt.Font("Comic Sans MS", 1, 18)); // NOI18N
        btn_aceptaNuevoLibro.setText("Aceptar");
        btn_aceptaNuevoLibro.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        btn_aceptaNuevoLibro.setHorizontalTextPosition(javax.swing.SwingConstants.LEFT);

        javax.swing.GroupLayout contenedorLayout = new javax.swing.GroupLayout(contenedor);
        contenedor.setLayout(contenedorLayout);
        contenedorLayout.setHorizontalGroup(
            contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(contenedorLayout.createSequentialGroup()
                .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(contenedorLayout.createSequentialGroup()
                        .addGap(106, 106, 106)
                        .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(campo_lugar, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(campo_autor, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label_autor, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label_titulo, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(campo_nombre, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(label_lugar, javax.swing.GroupLayout.PREFERRED_SIZE, 342, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addGroup(contenedorLayout.createSequentialGroup()
                        .addGap(231, 231, 231)
                        .addComponent(label_nota, javax.swing.GroupLayout.PREFERRED_SIZE, 104, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 180, Short.MAX_VALUE)
                .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, contenedorLayout.createSequentialGroup()
                        .addComponent(label_resumen, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(229, 229, 229))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, contenedorLayout.createSequentialGroup()
                        .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 371, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(btn_aceptaNuevoLibro, javax.swing.GroupLayout.PREFERRED_SIZE, 138, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(91, 91, 91))))
        );
        contenedorLayout.setVerticalGroup(
            contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(contenedorLayout.createSequentialGroup()
                .addGap(29, 29, 29)
                .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(label_titulo, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(label_resumen, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(contenedorLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(contenedorLayout.createSequentialGroup()
                        .addComponent(campo_nombre, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(11, 11, 11)
                        .addComponent(label_autor, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(4, 4, 4)
                        .addComponent(campo_autor, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(label_lugar, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(campo_lugar, javax.swing.GroupLayout.PREFERRED_SIZE, 30, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addComponent(label_nota))
                    .addGroup(contenedorLayout.createSequentialGroup()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 277, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(60, 60, 60)
                        .addComponent(btn_aceptaNuevoLibro)))
                .addContainerGap(66, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(contenedor, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(contenedor, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
    }// </editor-fold>//GEN-END:initComponents


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btn_aceptaNuevoLibro;
    private javax.swing.JTextField campo_autor;
    private javax.swing.JTextField campo_lugar;
    private javax.swing.JTextField campo_nombre;
    private javax.swing.JTextArea campo_resumen;
    private javax.swing.JPanel contenedor;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel label_autor;
    private javax.swing.JLabel label_lugar;
    private javax.swing.JLabel label_nota;
    private javax.swing.JLabel label_resumen;
    private javax.swing.JLabel label_titulo;
    // End of variables declaration//GEN-END:variables
}
