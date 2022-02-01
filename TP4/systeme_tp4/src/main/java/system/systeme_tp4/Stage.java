/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

/**
 *
 * @author flvivet
 */
public class Stage extends Thread{
    
    private ArrayBlockingQueue<Integer> in;
    private ArrayBlockingQueue<Integer> out;
    private int number;

    public Stage(ArrayBlockingQueue in, ArrayBlockingQueue out, int number) {
        this.in = in;
        this.out = out;
        this.number = number;
    }
    
    

    @Override
    public void run() {
        while(true){
            try {
                
                Integer value;
                value = this.in.poll(5000, TimeUnit.MILLISECONDS);
                
                if (value == null){
                    return;
                }
                
                value++;
                this.out.put(value);
            } catch (InterruptedException ex) {
                System.out.println("L'étage " + this.number + "a été interrompu");
            }
        }
    }
    
    
}
