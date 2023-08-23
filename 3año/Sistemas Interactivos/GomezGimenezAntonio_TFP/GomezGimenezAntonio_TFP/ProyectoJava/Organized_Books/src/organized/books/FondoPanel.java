/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package organized.books;

import java.awt.Graphics;
import java.awt.Image;
import javax.swing.ImageIcon;

/**
 *
 * @author Antonio
 */

//clase que me permite crear paneles personalizados
class FondoPanel extends javax.swing.JPanel{
    private Image imagen;
    private int _valor=0;
    
    public FondoPanel(int valor) {
        _valor=valor;
    }

    @Override
    public void paint(Graphics g){
        switch (_valor) {
            case 0:
                imagen = new ImageIcon(getClass().getResource("/imagenes/fondo_menu2.jpg")).getImage();
                g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                setOpaque(false);
                super.paint(g);
                break;
            case 1:
                imagen = new ImageIcon(getClass().getResource("/imagenes/busquedalibrofsico.png")).getImage();
                g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                setOpaque(false);
                super.paint(g);
                break;
            case 2:
                imagen = new ImageIcon(getClass().getResource("/imagenes/verlibrofsico.png")).getImage();
                g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                setOpaque(false);
                super.paint(g);
                break;
            default:
                imagen = new ImageIcon(getClass().getResource("/imagenes/libro_abierto2.png")).getImage();
                g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                setOpaque(false);
                super.paint(g);  
                break;
        }
    }       
}