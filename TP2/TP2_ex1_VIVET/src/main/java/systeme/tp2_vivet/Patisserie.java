/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package systeme.tp2_vivet;

import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author flvivet
 */
public class Patisserie {
    
    public ArrayList<Gateau> stock;
    
    public Patisserie() {
        this.stock = new ArrayList<>();
    }
    
    public synchronized void depose(Gateau gateau){
        stock.add(gateau);
        this.notify();
    }
    
    public synchronized Gateau achete(){
        while(stock.isEmpty()){
            try {
                this.wait();
            } catch (InterruptedException ex) {
                Logger.getLogger(Patisserie.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        Gateau gateau = this.stock.remove(0);
        this.notify();
        return gateau;
    }

    public ArrayList<Gateau> getStock() {
        return stock;
    }   
}
