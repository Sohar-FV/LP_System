/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.system_tp3;


/**
 *
 * @author flvivet
 */
public class Main {
    
    public static void main(String[] args){
        // Exercice 1
        //GetStatus statusGetter = new GetStatus();
        //statusGetter.checkStatus();
        
        // Exercice 2
        
        Harvester harvester = new Harvester();
        harvester.harvestBananas();
        
    }
    
}

/*

Exercice 1 

A. Classe WebVerif

B. Pas de données partagées : on donne un fragment du tableau à chaque Thread
nbthread : list.length

C. Classe GetStatus

Exercice 2


*/
