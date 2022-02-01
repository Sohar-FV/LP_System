/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.system_tp3;

import java.util.ArrayList;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.FutureTask;

/**
 *
 * @author flvivet
 */
public class Harvester {
    
    ArrayList<ArrayList<Banana>> crates;
    ArrayList<FutureTask<Integer>> tasks;
    private Integer numberOfBananasCollected;
    ExecutorService es; 

    public Harvester() {
        this.crates = new ArrayList<>(10);
        this.tasks = new ArrayList<>(10);
        this.numberOfBananasCollected = 0;
        this.es = Executors.newFixedThreadPool(10);
    }
    
    public void harvestBananas() {
        
        for(int i = 0; i< 10; i++) {
            this.crates.add(i,new ArrayList<>());
            Monkey monkey = new Monkey(i, this.crates.get(i));
            FutureTask<Integer> futureTask = new FutureTask<>(monkey);
            this.tasks.add(futureTask);
            this.es.execute(futureTask);
        }
        
            try {
                
                for(FutureTask task : this.tasks){
                    this.numberOfBananasCollected += (Integer)task.get();
                }
                System.out.println(this.numberOfBananasCollected);
                System.out.println(this.crates);
                
                es.shutdown();
                
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        
        }
}

/*

public class Harvester {
    
    ArrayList<Integer> crates;
    ArrayList<FutureTask<Integer>> tasks;
    private Integer numberOfBananasCollected;
    ExecutorService es; 

    public Harvester() {
        this.crates = new ArrayList<>(10);
        this.tasks = new ArrayList<>(10);
        this.numberOfBananasCollected = 0;
        this.es = Executors.newFixedThreadPool(10);
    }
    
    public void harvestBananas() {
        
        for(int i = 0; i< 10; i++) {
            this.crates.add(i,0);
            Monkey monkey = new Monkey(i, this.crates);
            FutureTask<Integer> futureTask = new FutureTask<>(monkey);
            this.tasks.add(futureTask);
            this.es.execute(futureTask);
        }
        
            try {
                
                for(FutureTask task : this.tasks){
                    this.numberOfBananasCollected += (Integer)task.get();
                }
                System.out.println(this.numberOfBananasCollected);
                System.out.println(this.crates);
                
                es.shutdown();
                
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        
        }
}

*/
