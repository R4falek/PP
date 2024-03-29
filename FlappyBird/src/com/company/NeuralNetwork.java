package com.company;

/*
 * This is the Neural Network class
 * Contains algorithms for Feedforward and Backpropagation
 */

public class NeuralNetwork {

    // Variables for nodes
    private final int inputNodes;
    private final int hiddenNodes;
    private final int outputNodes;

    // Variables for weights
    public Matrix weightsIH;
    public Matrix weightsHO;

    // Variables for baises
    public Matrix hiddenBias;
    public Matrix outputBias;

    // Learning Rate
    private double learningRate;

    // Activation Function
    private String activationFunction;

    NeuralNetwork(int inputNodes, int hiddenNodes, int outputNodes) {

        // Instantiating Layers
        this.inputNodes = inputNodes;
        this.hiddenNodes = hiddenNodes;
        this.outputNodes = outputNodes;

        // Instantiating Weights
        this.weightsIH = Matrix.random(this.hiddenNodes, this.inputNodes);
        this.weightsHO = Matrix.random(this.outputNodes, this.hiddenNodes);

        // Instantiating Biases
        this.hiddenBias = Matrix.random(this.hiddenNodes, 1);
        this.outputBias = Matrix.random(this.outputNodes, 1);

        // Instantiating Learning Rate
        this.learningRate = 0.1;

        // Instantiating Activation Function
        this.activationFunction = "Sigmoid";

    }

    //COPY CONSTRUCTOR
    NeuralNetwork(NeuralNetwork other) {

        // Instantiating Layers
        this.inputNodes = other.inputNodes;
        this.hiddenNodes = other.hiddenNodes;
        this.outputNodes = other.outputNodes;

        // Instantiating Weights
        this.weightsIH = other.weightsIH.copy();
        this.weightsHO = other.weightsHO.copy();

        // Instantiating Biases
        this.hiddenBias = other.hiddenBias.copy();
        this.outputBias = other.outputBias.copy();

        // Instantiating Learning Rate
        this.learningRate = 0.1;

        // Instantiating Activation Function
        this.activationFunction = "Sigmoid";
    }

    // Feedforward algorithm
    public double[] predict(double[] inputsArray) {

        // Variables for each layer
        Matrix inputs;
        Matrix hidden;
        Matrix outputs;

        // Generating each node
        try {

            // Making a matrix from input array
            inputs = Matrix.fromArray(inputsArray);

            // Multiplying weights by inputs to get hidden layer
            hidden = Matrix.multiply(this.weightsIH, inputs);

            // Adding bias to and activating hidden layer
            hidden.add(this.hiddenBias);
            hidden.activate(this.activationFunction);

            // Multiplying weights by outputs to get output layer
            outputs = Matrix.multiply(this.weightsHO, hidden);

            // Adding bias to and activating outputs layer
            outputs.add(this.outputBias);
            outputs.activate(this.activationFunction);

            return outputs.toArray();

        }

        // Printing error, if any
        catch (Exception e) {
            System.out.println(e.getMessage());
        }

        // Returning an empty array if failed ro predict
        return new double[this.outputNodes];

    }

    public double mutate(double x) {
        if(Math.random() < this.learningRate){
            var offset = (Math.random() * (0.1 - -0.1) + -0.1) * 20;
            var newx = x + offset;
            return newx;
            } else return x;
    }

    public void mutate(){
        for(int i = 0 ; i < this.weightsIH.data.length ; i++)
            for (int j = 0 ; j < this.weightsIH.data[i].length ; j++)
                this.weightsIH.data[i][j] = mutate(this.weightsIH.data[i][j]);
        for(int i = 0 ; i < this.weightsHO.data.length ; i++)
            for (int j = 0 ; j < this.weightsHO.data[i].length ; j++)
                this.weightsHO.data[i][j] = mutate(this.weightsHO.data[i][j]);
        for(int i = 0 ; i < this.hiddenBias.data.length ; i++)
            for (int j = 0 ; j < this.hiddenBias.data[i].length ; j++)
                this.hiddenBias.data[i][j] = mutate(this.hiddenBias.data[i][j]);
        for(int i = 0 ; i < this.outputBias.data.length ; i++)
            for (int j = 0 ; j < this.outputBias.data[i].length ; j++)
                this.outputBias.data[i][j] = mutate(this.outputBias.data[i][j]);
    }

    // Backpropagation algorithm
    public void train(double[] inputsArray, double[] labelsArray) {

        // Variables for each layer
        Matrix inputs;
        Matrix hidden;
        Matrix outputs;

        // Variable for labels
        Matrix labels;

        // Generating each node
        // Then propagating backwards
        try {

            // Making a matrix from input array and label array
            inputs = Matrix.fromArray(inputsArray);
            labels = Matrix.fromArray(labelsArray);

            // Feedforward algorithm
            hidden = Matrix.multiply(this.weightsIH, inputs);
            hidden.add(this.hiddenBias);
            hidden.activate(this.activationFunction);

            outputs = Matrix.multiply(this.weightsHO, hidden);
            outputs.add(this.outputBias);
            outputs.activate(this.activationFunction);

            // Calculating error and gradients
            Matrix outputError = Matrix.subtract(labels, outputs);
            Matrix outputGradients = Matrix.deactivate(outputs, this.activationFunction);

            // Multiplying gradients with error and scaling with learning rate
            outputGradients.multiply(outputError);
            outputGradients.scale(this.learningRate);

            // Finding the change of weights
            Matrix hiddenTranspose = Matrix.transpose(hidden);
            Matrix deltaWeightsHO = Matrix.multiply(outputGradients, hiddenTranspose);

            // Fixing the weights and adding to bias
            this.weightsHO.add(deltaWeightsHO);
            this.outputBias.add(outputGradients);

            // Calculating error and gradients
            Matrix weightsHOTranspose = Matrix.transpose(this.weightsHO);
            Matrix hiddenError = Matrix.multiply(weightsHOTranspose, outputError);
            Matrix hiddenGradients = Matrix.deactivate(hidden, this.activationFunction);

            // Multiplying gradients with error and scaling with learning rate
            hiddenGradients.multiply(hiddenError);
            hiddenGradients.scale(this.learningRate);

            // Finding the change of weights
            Matrix inputsTranspose = Matrix.transpose(inputs);
            Matrix deltaWeightsIH = Matrix.multiply(hiddenGradients, inputsTranspose);

            // Fixing the weights and adding to bias
            this.weightsIH.add(deltaWeightsIH);
            this.hiddenBias.add(hiddenGradients);

        }

        // Printing error, if any
        catch(Exception e) {
            System.out.println(e.getMessage());
        }

    }

    // Setter for learning rate
    public void setLearningRate(double newLearningRate) {
        this.learningRate = newLearningRate;
    }

    // Setter for activation function
    public void setActivationFunction(String newActivationFunction) {
        this.activationFunction = newActivationFunction;
    }

}