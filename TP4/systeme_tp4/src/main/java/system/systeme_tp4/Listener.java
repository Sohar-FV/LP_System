/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author flvivet
 */
public class Listener extends Thread{
    
    private BlockingQueue<Integer> b;

    public Listener(BlockingQueue b) {
        this.b = b;
    }

    @Override
    public void run() {
        while(true){
            try {
                Integer value;
                value = this.b.poll(5000, TimeUnit.MILLISECONDS);
                
                if (value == null){
                    return;
                }
                
                System.out.println("resultat :" +value);
            } catch (InterruptedException ex) {
                System.out.println("Le listener a été interrompu");
            }
        }
    }
    
}
