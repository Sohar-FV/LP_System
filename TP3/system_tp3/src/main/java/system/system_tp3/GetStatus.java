/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.system_tp3;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 *
 * @author flvivet
 */
public class GetStatus {
    
    private static String[] hostList = { "http://crunchify.com", "http://yahoo.com",
                          "http://www.ebay.com", "http://google.com",
                          "http://www.example.co", "https://paypal.com",
                          "http://bing.com/", "http://techcrunch.com/",
                          "http://mashable.com/", "http://thenextweb.com/",
                          "http://wordpress.com/", "http://wordpress.org/",
                          "http://example.com/", "http://sjsu.edu/",
                          "http://ebay.co.uk/", "http://google.co.uk/",
                          "http://www.wikipedia.org/",
                          "http://en.wikipedia.org/wiki/Main_Page"};
    
    public void checkStatus(){
        ExecutorService es = Executors.newFixedThreadPool(hostList.length);
        
        for(int i = 0; i < hostList.length; i++ ){
            es.execute(new Thread(new WebVerif(hostList[i])));
        }
        
        es.shutdown();
    }
}
