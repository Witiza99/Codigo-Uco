/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package internacionalizacion;

import java.util.Locale;
import java.util.ResourceBundle;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 *
 * @author Antonio
 */
public class intenacionalizacion1 extends javax.swing.JFrame {

    /**
     * Creates new form intenacionalizacion1
     */
    private static Locale locale;
    private int flag_a, flag_b, flag_c, flag_d = 0;
    Info info = new Info();
    
    public intenacionalizacion1() {
        initComponents();   
        this.setTitle("Internacionalizacion");
        locale = Locale.getDefault();
        ResourceBundle rb = ResourceBundle.getBundle("internacionalizacion.Bundle", locale);
        Apellidos_texto2.setText(rb.getString("intenacionalizacion1.Apellidos_texto2.text"));
        Dinero_label2.setText(rb.getString("intenacionalizacion1.Dinero_label2.text"));
        Nombre_texto2.setText(rb.getString("intenacionalizacion1.Nombre_texto2.text"));
        Fecha_label2.setText(rb.getString("intenacionalizacion1.Fecha_label2.text"));
        Aceptar_button2.setText(rb.getString("intenacionalizacion1.Aceptar_button2.text"));
        Apellidos_label2.setText(rb.getString("intenacionalizacion1.Apellidos_label2.text"));
        Nombre_label2.setText(rb.getString("intenacionalizacion1.Nombre_label2.text"));
        Text_form2.setText(rb.getString("intenacionalizacion1.Text_form2.text"));
        Dinero_texto2.setText(rb.getString("intenacionalizacion1.Dinero_texto2.text"));
        Fecha_texto2.setText(rb.getString("intenacionalizacion1.Fecha_texto2.text"));
    }
    
    public String[] cortarCadena(String cadena) {
        return cadena.split("/");
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        panel = new javax.swing.JPanel();
        Apellidos_label2 = new javax.swing.JLabel();
        Text_form2 = new javax.swing.JLabel();
        Nombre_label2 = new javax.swing.JLabel();
        Dinero_texto2 = new javax.swing.JTextField();
        Dinero_label2 = new javax.swing.JLabel();
        Apellidos_texto2 = new javax.swing.JTextField();
        Boton_Ing1 = new javax.swing.JButton();
        Aceptar_button2 = new javax.swing.JButton();
        Boton_Fra1 = new javax.swing.JButton();
        Fecha_texto2 = new javax.swing.JTextField();
        Fecha_label2 = new javax.swing.JLabel();
        Nombre_texto2 = new javax.swing.JTextField();
        Boton_Esp1 = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setBackground(new java.awt.Color(102, 0, 102));
        setResizable(false);

        panel.setBackground(new java.awt.Color(102, 0, 102));

        Apellidos_label2.setForeground(new java.awt.Color(255, 255, 255));
        java.util.ResourceBundle bundle = java.util.ResourceBundle.getBundle("internacionalizacion/Bundle"); // NOI18N
        Apellidos_label2.setText(bundle.getString("intenacionalizacion1.Apellidos_label2.text")); // NOI18N

        Text_form2.setFont(new java.awt.Font("Tahoma", 0, 30)); // NOI18N
        Text_form2.setForeground(new java.awt.Color(255, 255, 255));
        Text_form2.setText(bundle.getString("intenacionalizacion1.Text_form2.text")); // NOI18N

        Nombre_label2.setForeground(new java.awt.Color(255, 255, 255));
        Nombre_label2.setText(bundle.getString("intenacionalizacion1.Nombre_label2.text")); // NOI18N

        Dinero_texto2.setForeground(new java.awt.Color(153, 153, 153));
        Dinero_texto2.setText(bundle.getString("intenacionalizacion1.Dinero_texto2.text")); // NOI18N
        Dinero_texto2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                Dinero_texto2KeyPressed(evt);
            }
        });

        Dinero_label2.setForeground(new java.awt.Color(255, 255, 255));
        Dinero_label2.setText(bundle.getString("intenacionalizacion1.Dinero_label2.text")); // NOI18N

        Apellidos_texto2.setForeground(new java.awt.Color(153, 153, 153));
        Apellidos_texto2.setText(bundle.getString("intenacionalizacion1.Apellidos_texto2.text")); // NOI18N
        Apellidos_texto2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                Apellidos_texto2KeyPressed(evt);
            }
        });

        Boton_Ing1.setBackground(new java.awt.Color(102, 0, 102));
        Boton_Ing1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/ing.png"))); // NOI18N
        Boton_Ing1.setBorder(null);
        Boton_Ing1.setBorderPainted(false);
        Boton_Ing1.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Boton_Ing1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Boton_Ing1MouseClicked(evt);
            }
        });

        Aceptar_button2.setBackground(new java.awt.Color(102, 0, 102));
        Aceptar_button2.setForeground(new java.awt.Color(255, 255, 255));
        Aceptar_button2.setText(bundle.getString("intenacionalizacion1.Aceptar_button2.text")); // NOI18N
        Aceptar_button2.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Aceptar_button2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Aceptar_button2MouseClicked(evt);
            }
        });

        Boton_Fra1.setBackground(new java.awt.Color(102, 0, 102));
        Boton_Fra1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/fra.png"))); // NOI18N
        Boton_Fra1.setBorder(null);
        Boton_Fra1.setBorderPainted(false);
        Boton_Fra1.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Boton_Fra1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Boton_Fra1MouseClicked(evt);
            }
        });

        Fecha_texto2.setForeground(new java.awt.Color(153, 153, 153));
        Fecha_texto2.setText(bundle.getString("intenacionalizacion1.Fecha_texto2.text")); // NOI18N
        Fecha_texto2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                Fecha_texto2KeyPressed(evt);
            }
        });

        Fecha_label2.setForeground(new java.awt.Color(255, 255, 255));
        Fecha_label2.setText(bundle.getString("intenacionalizacion1.Fecha_label2.text")); // NOI18N

        Nombre_texto2.setForeground(new java.awt.Color(153, 153, 153));
        Nombre_texto2.setText(bundle.getString("intenacionalizacion1.Nombre_texto2.text")); // NOI18N
        Nombre_texto2.addKeyListener(new java.awt.event.KeyAdapter() {
            public void keyPressed(java.awt.event.KeyEvent evt) {
                Nombre_texto2KeyPressed(evt);
            }
        });

        Boton_Esp1.setBackground(new java.awt.Color(102, 0, 102));
        Boton_Esp1.setIcon(new javax.swing.ImageIcon(getClass().getResource("/imagenes/esp.png"))); // NOI18N
        Boton_Esp1.setBorder(null);
        Boton_Esp1.setBorderPainted(false);
        Boton_Esp1.setCursor(new java.awt.Cursor(java.awt.Cursor.HAND_CURSOR));
        Boton_Esp1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                Boton_Esp1MouseClicked(evt);
            }
        });

        javax.swing.GroupLayout panelLayout = new javax.swing.GroupLayout(panel);
        panel.setLayout(panelLayout);
        panelLayout.setHorizontalGroup(
            panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(Text_form2, javax.swing.GroupLayout.PREFERRED_SIZE, 148, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(Fecha_label2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(Dinero_label2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(Apellidos_label2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(Nombre_label2, javax.swing.GroupLayout.PREFERRED_SIZE, 130, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(panelLayout.createSequentialGroup()
                        .addGap(75, 75, 75)
                        .addComponent(Boton_Esp1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(Boton_Ing1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(Boton_Fra1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addComponent(Aceptar_button2, javax.swing.GroupLayout.Alignment.TRAILING)
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(Nombre_texto2)
                        .addComponent(Fecha_texto2, javax.swing.GroupLayout.Alignment.TRAILING)
                        .addComponent(Apellidos_texto2, javax.swing.GroupLayout.Alignment.TRAILING)
                        .addComponent(Dinero_texto2, javax.swing.GroupLayout.PREFERRED_SIZE, 240, javax.swing.GroupLayout.PREFERRED_SIZE)))
                .addContainerGap())
        );
        panelLayout.setVerticalGroup(
            panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(panelLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(Text_form2, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, 51, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGroup(panelLayout.createSequentialGroup()
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 8, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(Boton_Fra1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addComponent(Boton_Ing1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE))
                            .addComponent(Boton_Esp1, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addGap(18, 18, 18)
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Nombre_label2, javax.swing.GroupLayout.PREFERRED_SIZE, 14, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(Nombre_texto2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Apellidos_label2, javax.swing.GroupLayout.PREFERRED_SIZE, 14, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(Apellidos_texto2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Fecha_label2, javax.swing.GroupLayout.PREFERRED_SIZE, 14, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(Fecha_texto2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(panelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(Dinero_label2)
                    .addComponent(Dinero_texto2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addComponent(Aceptar_button2)
                .addContainerGap())
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(panel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(panel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void Boton_Fra1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Boton_Fra1MouseClicked
        locale = new Locale("fr","FR");
        ResourceBundle rb = ResourceBundle.getBundle("internacionalizacion.Bundle_fr_FR", locale);
        Apellidos_texto2.setText(rb.getString("intenacionalizacion1.Apellidos_texto2.text"));
        Dinero_label2.setText(rb.getString("intenacionalizacion1.Dinero_label2.text"));
        Nombre_texto2.setText(rb.getString("intenacionalizacion1.Nombre_texto2.text"));
        Fecha_label2.setText(rb.getString("intenacionalizacion1.Fecha_label2.text"));
        Aceptar_button2.setText(rb.getString("intenacionalizacion1.Aceptar_button2.text"));
        Apellidos_label2.setText(rb.getString("intenacionalizacion1.Apellidos_label2.text"));
        Nombre_label2.setText(rb.getString("intenacionalizacion1.Nombre_label2.text"));
        Text_form2.setText(rb.getString("intenacionalizacion1.Text_form2.text"));
        Dinero_texto2.setText(rb.getString("intenacionalizacion1.Dinero_texto2.text"));
        Fecha_texto2.setText(rb.getString("intenacionalizacion1.Fecha_texto2.text"));
        
        flag_a = 0;
        flag_b = 0;
        flag_c = 0;
        flag_d = 0;
        info = new Info();
    }//GEN-LAST:event_Boton_Fra1MouseClicked

    private void Boton_Esp1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Boton_Esp1MouseClicked
        locale = new Locale("es","ES");
        ResourceBundle rb = ResourceBundle.getBundle("internacionalizacion.Bundle_es_ES", locale);
        Apellidos_texto2.setText(rb.getString("intenacionalizacion1.Apellidos_texto2.text"));
        Dinero_label2.setText(rb.getString("intenacionalizacion1.Dinero_label2.text"));
        Nombre_texto2.setText(rb.getString("intenacionalizacion1.Nombre_texto2.text"));
        Fecha_label2.setText(rb.getString("intenacionalizacion1.Fecha_label2.text"));
        Aceptar_button2.setText(rb.getString("intenacionalizacion1.Aceptar_button2.text"));
        Apellidos_label2.setText(rb.getString("intenacionalizacion1.Apellidos_label2.text"));
        Nombre_label2.setText(rb.getString("intenacionalizacion1.Nombre_label2.text"));
        Text_form2.setText(rb.getString("intenacionalizacion1.Text_form2.text"));
        Dinero_texto2.setText(rb.getString("intenacionalizacion1.Dinero_texto2.text"));
        Fecha_texto2.setText(rb.getString("intenacionalizacion1.Fecha_texto2.text"));
        
        flag_a = 0;
        flag_b = 0;
        flag_c = 0;
        flag_d = 0;
        info = new Info();
    }//GEN-LAST:event_Boton_Esp1MouseClicked

    private void Boton_Ing1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Boton_Ing1MouseClicked
        locale = new Locale("en","GB");
        ResourceBundle rb = ResourceBundle.getBundle("internacionalizacion.Bundle_en_GB", locale);
        Apellidos_texto2.setText(rb.getString("intenacionalizacion1.Apellidos_texto2.text"));
        Dinero_label2.setText(rb.getString("intenacionalizacion1.Dinero_label2.text"));
        Nombre_texto2.setText(rb.getString("intenacionalizacion1.Nombre_texto2.text"));
        Fecha_label2.setText(rb.getString("intenacionalizacion1.Fecha_label2.text"));
        Aceptar_button2.setText(rb.getString("intenacionalizacion1.Aceptar_button2.text"));
        Apellidos_label2.setText(rb.getString("intenacionalizacion1.Apellidos_label2.text"));
        Nombre_label2.setText(rb.getString("intenacionalizacion1.Nombre_label2.text"));
        Text_form2.setText(rb.getString("intenacionalizacion1.Text_form2.text"));
        Dinero_texto2.setText(rb.getString("intenacionalizacion1.Dinero_texto2.text"));
        Fecha_texto2.setText(rb.getString("intenacionalizacion1.Fecha_texto2.text"));
        
        flag_a = 0;
        flag_b = 0;
        flag_c = 0;
        flag_d = 0;
        info = new Info();
    }//GEN-LAST:event_Boton_Ing1MouseClicked

    private void Nombre_texto2KeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_Nombre_texto2KeyPressed
        if(flag_a!=1){
            Nombre_texto2.setText("");
        }
        flag_a = 1;
        
    }//GEN-LAST:event_Nombre_texto2KeyPressed

    private void Apellidos_texto2KeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_Apellidos_texto2KeyPressed
        if(flag_b!=1){
            Apellidos_texto2.setText("");
        }
        flag_b = 1;
    }//GEN-LAST:event_Apellidos_texto2KeyPressed

    private void Fecha_texto2KeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_Fecha_texto2KeyPressed
        if(flag_c!=1){
            Fecha_texto2.setText("");
        }
        flag_c = 1;
    }//GEN-LAST:event_Fecha_texto2KeyPressed

    private void Dinero_texto2KeyPressed(java.awt.event.KeyEvent evt) {//GEN-FIRST:event_Dinero_texto2KeyPressed
        if(flag_d!=1){
            Dinero_texto2.setText("");
        }
        flag_d = 1;
    }//GEN-LAST:event_Dinero_texto2KeyPressed

    private void Aceptar_button2MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_Aceptar_button2MouseClicked
        info.setNombre(Nombre_texto2.getText());
        info.setApellidos(Apellidos_texto2.getText());
        String fecha = Fecha_texto2.getText();
        String dia, mes, año;
        Locale esp = new Locale("es","ES");
        Locale fra = new Locale("fr","FR");

        if(locale.equals(esp)||locale.equals(fra)){//cambio formatos dependiendo del idioma
           try{
                String [] auxiliar = cortarCadena(fecha);    
                dia = auxiliar[0]; 
                mes = auxiliar[1]; 
                año = auxiliar[2];
                String aux = Dinero_texto2.getText();
                if(aux.contains(",")){
                    aux = aux.replace(",", ".");
                }
                info.setDinero(Double.parseDouble(aux));
           }catch(Exception e){
                dia="0";
                mes="0";
                año="0";
                info.setDinero(0);
           }
        }else{
            try{
                String [] auxiliar = cortarCadena(fecha);
                mes = auxiliar[0]; 
                dia = auxiliar[1]; 
                año = auxiliar[2]; 

                double dinero_aux = Double.parseDouble(Dinero_texto2.getText());
                info.setDinero(0.88*dinero_aux);  //lo tranformo a euros ya que se almacena en euros

           }catch(Exception e){
                dia="0";
                mes="0";
                año="0";
                info.setDinero(0);
           }
        }
        try{
            info.setDia(Integer.parseInt(dia));
            info.setMes(Integer.parseInt(mes));
            info.setAño(Integer.parseInt(año));
        }catch(NumberFormatException e){
            info.setDia(0);
            info.setMes(0);
            info.setAño(0);
        }
        
        if(locale.equals(esp)){
            String dinero_coma = String.valueOf(info.getDinero());
            if(dinero_coma.contains(".")){
                dinero_coma = dinero_coma.replace(".", ",");
            }
            JOptionPane.showMessageDialog(null,"El usuario "+info.getNombre()+" "+info.getApellidos()+" nacido el "+info.getDia()+" del "+info.getMes()+" del "+info.getAño()+" tiene "+dinero_coma+"€","Formulario enviado",JOptionPane.INFORMATION_MESSAGE);
        }else if(locale.equals(fra)){
            String dinero_coma = String.valueOf(info.getDinero());
            if(dinero_coma.contains(".")){
                dinero_coma = dinero_coma.replace(".", ",");
            }
            JOptionPane.showMessageDialog(null,"L'utilisateur "+info.getNombre() +" "+info.getApellidos()+" né "+info.getDia()+"/"+info.getMes()+"/"+info.getAño()+" a "+dinero_coma+"€","Formulé expédié",JOptionPane.INFORMATION_MESSAGE);
        }else{
            JOptionPane.showMessageDialog(null,"The user "+info.getNombre()+" "+info.getApellidos()+" born "+info.getMes()+"/"+info.getDia()+"/"+info.getAño()+" has "+(info.getDinero()/0.88)+"£","Formulated shipped",JOptionPane.INFORMATION_MESSAGE);
        }
    }//GEN-LAST:event_Aceptar_button2MouseClicked

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
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(intenacionalizacion1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(intenacionalizacion1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(intenacionalizacion1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(intenacionalizacion1.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                intenacionalizacion1 v = new intenacionalizacion1(); 
                v.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 
                v.setVisible(true);
                v.setLocationRelativeTo(null);
                v.setResizable(false);              
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton Aceptar_button2;
    private javax.swing.JLabel Apellidos_label2;
    private javax.swing.JTextField Apellidos_texto2;
    private javax.swing.JButton Boton_Esp1;
    private javax.swing.JButton Boton_Fra1;
    private javax.swing.JButton Boton_Ing1;
    private javax.swing.JLabel Dinero_label2;
    private javax.swing.JTextField Dinero_texto2;
    private javax.swing.JLabel Fecha_label2;
    private javax.swing.JTextField Fecha_texto2;
    private javax.swing.JLabel Nombre_label2;
    private javax.swing.JTextField Nombre_texto2;
    private javax.swing.JLabel Text_form2;
    private javax.swing.JPanel panel;
    // End of variables declaration//GEN-END:variables
}
