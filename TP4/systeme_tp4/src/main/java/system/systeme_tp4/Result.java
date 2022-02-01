/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package system.systeme_tp4;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author flvivet
 */
public class Result {
    
    private List<Integer> valueHistory;

    public Result(Integer initialValue) {
        this.valueHistory = new ArrayList<>();
        this.valueHistory.add(initialValue);
    }

    public Integer getValue() {
        return this.valueHistory.get(this.valueHistory.size()-1);
    }

    public List<Integer> getValueHistory() {
        return valueHistory;
    }
    
    
    
    
    
}
