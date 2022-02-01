/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package systeme.tp2_ex3_vivet;

/**
 *
 * @author flvivet
 */
public class Client implements Runnable{
    
    public String nom;
    public Patisserie patisserie;

    public Client(String nom, Patisserie patisserie) {
        this.nom = nom;
        this.patisserie = patisserie;
    }

    @Override
    public void run() {
        int i = 0;
        while(i < 10){
            Gateau gateau = this.patisserie.achete();      
            System.out.println(this.nom + " a acheté un gateau");
            i++;
        }
    }
}

