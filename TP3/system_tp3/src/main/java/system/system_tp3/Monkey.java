/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.system_tp3;

import java.util.ArrayList;
import java.util.Random;
import java.util.concurrent.Callable;

/**
 *
 * @author flvivet
 */
public class Monkey implements Callable<Integer>{
    
    private int crateIndex;
    private ArrayList<Banana> crate;
    
    public Monkey(int crateIndex, ArrayList<Banana> crate){
        this.crateIndex = crateIndex;
        this.crate = crate;
    }

    @Override
    public Integer call() throws Exception {
        Random rand = new Random();
        int i = rand.nextInt(20);
        for (int x=0; x<i; x++){ 
            this.crate.set(this.crateIndex, new Banana());
        }
        return this.crate.size();
    }
    
    
    
}
