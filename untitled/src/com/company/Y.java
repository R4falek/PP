package com.company;

public class Y extends X{
    protected int yMask = 0xff00;

    public Y(){
        fullMask = yMask;
    }

    public void yMask(){
        this.yMask = mask(xMask);
    }

    public int mask(int orig) {
        System.out.println("y");
        return (orig & fullMask);
    }
}
