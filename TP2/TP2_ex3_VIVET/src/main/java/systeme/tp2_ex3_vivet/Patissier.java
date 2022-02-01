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
public class Patissier implements Runnable{
    
    public String nom;
    public Patisserie patisserie;

    public Patissier(String nom, Patisserie patisserie) {
        this.nom = nom;
        this.patisserie = patisserie;
    }
    
    @Override
    public void run() {
        int i = 0;
        boolean continuer = true;
        while(continuer) {
            continuer = this.patisserie.depose(new Gateau());
            System.out.println(this.nom + " a déposé un gateau");
            i++;
        }
    }
}

