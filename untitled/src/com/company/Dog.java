package com.company;

public class Dog {

    public String name;
    private String says;

    public String getName() {
        return this.name;
    }

    public String getSays() {
        System.out.println(this.says + " " + this.name);
        return this.says;
    }

    public Dog(String n, String s){
        this.name = n;
        this.says = s;
    }
}
