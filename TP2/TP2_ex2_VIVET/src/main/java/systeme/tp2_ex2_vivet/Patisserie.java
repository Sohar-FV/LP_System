/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package systeme.tp2_ex2_vivet;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author flvivet
 */
public class Patisserie {
    
    public ArrayBlockingQueue<Gateau> stock;
    
    public Patisserie() {
        this.stock = new ArrayBlockingQueue(10);       
    }
    
    public void depose(Gateau gateau){
        stock.offer(gateau);
    }
    
    public Gateau achete(){
        Gateau gateau = null;
        try {
            gateau = this.stock.take();
        } catch (InterruptedException ex) {
            Logger.getLogger(Patisserie.class.getName()).log(Level.SEVERE, null, ex);
        }
        return gateau;
    }

    public ArrayBlockingQueue<Gateau> getStock() {
        return stock;
    }
}

