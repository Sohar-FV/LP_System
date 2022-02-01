/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;

import java.util.concurrent.ArrayBlockingQueue;

/**
 *
 * @author flvivet
 */
public class Stage extends Thread{
    
    private ArrayBlockingQueue<Result> in;
    private ArrayBlockingQueue<Result> out;
    private int number;

    public Stage(ArrayBlockingQueue in, ArrayBlockingQueue out, int number) {
        this.in = in;
        this.out = out;
        this.number = number;
    }
    
    

    @Override
    public void run() {
        boolean continuer = true;
        while(continuer){
            try {
                
                Result result;
                result = this.in.take();
                
                if (result.getValue() == -1){
                    continuer = false;
                } else {  
                    Work.work(this.number, result);
                    /* Avant les works :
                    Integer i = result.getValue();
                    i++;
                    result.getValueHistory().add(i);
                    */
                }                          
                this.out.put(result);
                
            } catch (InterruptedException ex) {
                System.out.println("L'étage " + this.number + "a été interrompu");
            }
        }
    }
    
    
}
