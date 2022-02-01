/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package systeme.tp2_vivet;

/**
 *
 * @author flvivet
 */
public class Main {
    
    public static void main(String[] args){
        Patisserie patisserie = new Patisserie();
        for (int i = 0; i <= 3; i++) {
            Thread t1 = new Thread(new Client("client "+i, patisserie));     
            Thread t2 = new Thread(new Patissier("patissier "+i, patisserie));
            t1.start();
            t2.start();     
        }
    }
    
}
