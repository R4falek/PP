package com.company;

public class Card {

    public enum suit{
        PIK, TREFL, KIER, KARO
    }

    public enum rank{
        '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'
    }

    private String suit;
    private char rank;

    public Card(String s, char r){
        this.suit = s;
        this.rank = r;
    }

    public void to_string(){
        System.out.println();
    }
}
