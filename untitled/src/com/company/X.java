package com.company;

import javax.swing.plaf.synth.SynthOptionPaneUI;

public class X {
    protected int xMask = 0x00ff;
    protected int fullMask;

    public X(){
        this.fullMask = this.xMask;
    }

    public int mask(int orig) {
        System.out.println("x");
        return (orig & fullMask);
    }
}
