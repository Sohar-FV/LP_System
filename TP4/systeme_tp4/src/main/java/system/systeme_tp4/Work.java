/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;


/**
 *
 * @author flvivet
 */
public class Work {
    
    public static void work(int number, Result result){
        switch(number+1){
            case 1: methode1(result);
                break;
            case 2: methode2(result);
                break;
            case 3: methode3(result);
                break;
        }
    }
    
    public static void methode1(Result result){
        Integer i = result.getValue();
        i++;
        result.getValueHistory().add(i);
    }
    
    public static void methode2(Result result){
        Integer i = result.getValue();
        i = i + 2;
        result.getValueHistory().add(i);
    }
    
    public static void methode3(Result result){
        Integer i = result.getValue();
        i = i + 3;
        result.getValueHistory().add(i);
    }
    
}
