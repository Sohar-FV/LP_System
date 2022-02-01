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
    
    private BlockingQueue<Result> b;

    public Listener(BlockingQueue b) {
        this.b = b;
    }

    @Override
    public void run() {
        boolean continuer = true;
        while(continuer){
            try {
                Result result;
                result = this.b.take();
                
                if (result.getValue() == -1){
                    continuer = false;
                } else {
                    System.out.println("resultat :" +result.getValueHistory());
                }
                
            } catch (InterruptedException ex) {
                System.out.println("Le listener a été interrompu");
            }
        }
    }
    
}
