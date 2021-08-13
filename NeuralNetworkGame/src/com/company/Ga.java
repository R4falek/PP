package com.company;

import java.util.ArrayList;

public class Ga {

    static int counter = 0;
    int population;
    int childNumber;
    NeuralNetwork bestBirdBrain = null;
    double bestScore = 0;

    public Ga(int population, int childNumber){
        this.population = population;
        this.childNumber = childNumber;
    }

    public ArrayList<Bird> nextGeneration(ArrayList<Bird> birds){
        counter++;
        calculateFitness(birds);
        System.out.println(counter + " Next generation");
        return generate(birds);
    }

    public void saveBest(ArrayList<Bird> birds) {
        Bird bestBird = null;
        for(Bird bird : birds)
            if(bestBird == null || bestBird.fitness <= bird.fitness)
                bestBird = bird;

        if((bestBirdBrain == null || bestBird.score > bestScore) && bestBird != null){
            bestScore = bestBird.score;
            bestBirdBrain = new NeuralNetwork(bestBird.brain);
        }
    }

    public Bird pickOne(ArrayList<Bird> birds){
        Bird bestBird = null;
        for(Bird bird : birds)
            if(bestBird == null || bestBird.fitness <= bird.fitness)
                bestBird = bird;

        if((bestBirdBrain == null || bestBird.score > bestScore) && bestBird != null){
            bestScore = bestBird.score;
            bestBirdBrain = new NeuralNetwork(bestBird.brain);
        }

        birds.remove(bestBird);
        return bestBird;
    }

    public void calculateFitness(ArrayList<Bird> birds){
        int sum = 0;
        for(Bird bird : birds) sum += bird.score;
        for(Bird bird : birds) bird.fitness = (double) bird.score/sum;
    }

    public ArrayList<Bird> generate(ArrayList<Bird> birds) {
        ArrayList<Bird> newBirds = new ArrayList<>();
        for (int i = 0; i < population * 0.02; i++)
            newBirds.add(new Bird(null, false));
        for (int i = 0; i < childNumber; i++) {
            NeuralNetwork bestBrain = pickOne(birds).brain;
            newBirds.add(new Bird(bestBrain, false));
            for (int j = 0; j < (population - population * 0.02 - childNumber) / childNumber; j++)
                newBirds.add(new Bird(bestBrain, true));
        }
        return newBirds;
    }
}
