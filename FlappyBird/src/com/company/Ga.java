package com.company;

import java.util.ArrayList;

public class Ga {

    static int counter = 0;
    int population;
    Bird bestBird;

    public Ga(int population){
        this.population = population;
        bestBird = null;
    }

    public ArrayList<Bird> nextGeneration(ArrayList<Bird> birds){
        counter++;
        calculateFitness(birds);
        System.out.println(counter + " Next generation");
        return generate(birds);
    }

    public Bird pickOne(ArrayList<Bird> birds){
        Bird bestBird = null;
        for(Bird bird : birds)
            if(bestBird == null || bestBird.fitness <= bird.fitness)
                bestBird = bird;

        if(this.bestBird == null || this.bestBird.fitness < bestBird.fitness)
            this.bestBird = bestBird;
        return this.bestBird.copy();
    }

    public void calculateFitness(ArrayList<Bird> birds){
        int sum = 0;
        for(Bird bird : birds) sum += bird.score;
        for(Bird bird : birds) bird.fitness = (double) bird.score/sum;
    }

    public ArrayList<Bird> generate(ArrayList<Bird> birds){
        ArrayList<Bird> newBirds = new ArrayList<>();
        NeuralNetwork bestBrain = pickOne(birds).brain;
        for(int i = 0 ; i < 10 ; i++)
            newBirds.add(new Bird(bestBrain, false));
        for(int i = 10 ; i < 20 ; i++)
            newBirds.add(new Bird(null, false));
        for (int i = 20 ; i < population ; i++) newBirds.add(new Bird(bestBrain, true));
        return newBirds;
    }
}
