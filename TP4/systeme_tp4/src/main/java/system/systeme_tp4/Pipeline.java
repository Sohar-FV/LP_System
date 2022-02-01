/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;


import java.util.concurrent.ArrayBlockingQueue;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author flvivet
 */
public class Pipeline {

    /**
     * @param args the command line arguments
     */
    static int num = 3;

    public static void main (String argv[]) {
        ArrayBlockingQueue first, in, out = null;
        first = in  = new ArrayBlockingQueue(4);
        for (int i = 0; i < num; i++) 
        {
            out = new ArrayBlockingQueue(4); 
            (new Stage(in,out,i)).start();
            
            in = out; 
        }

        (new Listener(out)).start();// Affichage des résultats de la dernière Queue

        first.add(7);
                try {
                    Thread.sleep(3000);

                } catch (InterruptedException ex) {
                    Logger.getLogger(Pipeline.class.getName()).log(Level.SEVERE, null, ex);
                }


        first.add(2);
                try {
                    Thread.sleep(3000);

                } catch (InterruptedException ex) {
                    Logger.getLogger(Pipeline.class.getName()).log(Level.SEVERE, null, ex);
                } 

    }
}
