/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.system_tp3;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.UnknownHostException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author flvivet
 */
public class WebVerif implements Runnable{
    
    private String link;

    public WebVerif(String link) {
        this.link = link;
    }

    @Override
    public void run() {
        try {
            URL url = new URL(this.link);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.connect();
            int result = connection.getResponseCode();
            System.out.println(url + " : " + result);
        } catch (UnknownHostException ex) {
            System.out.println(this.link + " n'existe pas");
        } catch (IOException ex) {
            Logger.getLogger(WebVerif.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
    
}
