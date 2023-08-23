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

//clase que me permite crear botones personalizados
class FondoBoton extends javax.swing.JButton{
        private Image imagen;
        private int _valor=0;
        
        
        public FondoBoton(int valor) {
            _valor=valor;
        }
        
        @Override
        public void paint(Graphics g){
            
            switch (_valor) {
                case 0:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/libro.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                case 1:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/ebook.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                case 2:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/flecha.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                case 3:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/lupa.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                case 4:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/nuevo_libro.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                case 5:
                    imagen = new ImageIcon(getClass().getResource("/imagenes/modificar_libro.png")).getImage();
                    g.drawImage(imagen, 0, 0, getWidth(), getHeight(), this);
                    setContentAreaFilled(false);
                    setOpaque(false);
                    setBorder(null);
                    super.paint(g);
                    break;
                default:   
                    break;
            }
        }
    }   
