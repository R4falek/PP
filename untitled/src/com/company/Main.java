package com.company;

import org.w3c.dom.ranges.DocumentRange;

public class Main {
    public static void mama(Dog c2){
        System.out.println(c2);
    }
    public static void main(String[] args) {
        Y y;
        y = new Y();
        y.yMask();

        Dog d1 = new Dog("rex", "Ruff!");
        Dog d2 = new Dog("scruffy", "Wurf!");

       d1.getName();
       d1.getSays();
       d2.getName();
       d2.getSays();

       Dog d3 = d1;
       Dog d4 = new Dog("rex","Ruff!");

       if(d1.name.equals(d3.name))
           System.out.println("tru");

        if(d1.name == d3.name)
            System.out.println("tru");

       mama(d1);
    }
}
