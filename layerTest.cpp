#include <stdio.h>
#include "neuron.h"
#include "layer.h"
#include <assert.h>

int main() {

    int neuronAmount = 3; 
    int numberOfDentritesSeven = 7;
    int numberOfDentritesSix = 6;
    int layersAmount = 2;
    double initialWeight = 0.01;
    double temporalWeight = initialWeight;
    double* synapses = new double[numberOfDentritesSeven];
    double* inputs = new double[numberOfDentritesSeven];
    Layer* layertArray = new Layer [layersAmount];
  
    layertArray[0].init(neuronAmount,
       ACTIVATION_FUNCTION_LINEAL, numberOfDentritesSeven);
    layertArray[1].init(neuronAmount,
       ACTIVATION_FUNCTION_LINEAL, numberOfDentritesSix);

    printf("Neuron amount %i == %i \n",layertArray[0].getLayerNeuronAmount() , neuronAmount);
    assert(layertArray[1].getLayerNeuronAmount() == neuronAmount);

    printf("Neuron activation type %i == %i \n",layertArray[1].getActivationFunctionType() , ACTIVATION_FUNCTION_LINEAL);
    assert(layertArray[1].getActivationFunctionType() == ACTIVATION_FUNCTION_LINEAL);

    //create weights & input map
    for(int neuronIndex = 0 ;neuronIndex < numberOfDentritesSeven;neuronIndex++ ){
            synapses[neuronIndex] = temporalWeight;
            inputs[neuronIndex] = temporalWeight*10.0;
            temporalWeight += 0.01;
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        layertArray[0].setSynapsesForNeuronAt(neuronIndex,synapses);
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        layertArray[1].setSynapsesForNeuronAt(neuronIndex,synapses);
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        temporalWeight = initialWeight;
        double* internal = layertArray[0].getSynapsesForNeuronAt(neuronIndex);
        for(int dentriteIndex = 0 ;dentriteIndex < numberOfDentritesSeven;dentriteIndex++ ){
             printf(" Layer0 weights %i - %f == %f \n",dentriteIndex, internal[dentriteIndex], temporalWeight);
            assert(internal[dentriteIndex] == temporalWeight);
            temporalWeight += 0.01;
        }
    }

    temporalWeight = initialWeight;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        temporalWeight = initialWeight;
        double* internal = layertArray[1].getSynapsesForNeuronAt(neuronIndex);
        for(int dentriteIndex = 0 ;dentriteIndex < numberOfDentritesSix;dentriteIndex++ ){
             printf("Layer1 weights %f == %f \n",internal[dentriteIndex], temporalWeight);
            assert(internal[dentriteIndex] == temporalWeight);
            temporalWeight += 0.01;
        }
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        double* internal = layertArray[0].rankThresshold(inputs);
        printf(" Layer0 outputs - %f == %f \n",internal[neuronIndex], 0.14);
        assert( internal[neuronIndex] > 0.139 && internal[neuronIndex] < 0.141);
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        double* internal = layertArray[1].rankThresshold(inputs);
        printf(" Layer1 outputs - %f == %f \n",internal[neuronIndex], 0.091);
        assert( internal[neuronIndex] > 0.09 && internal[neuronIndex] < 0.92);
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        double* internal = layertArray[0].getOutputCollection();
        printf(" Layer0 getOutputCollection - %f == %f \n",internal[neuronIndex], 0.14);
        assert( internal[neuronIndex] > 0.139 && internal[neuronIndex] < 0.141);
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        double* internal = layertArray[1].getOutputCollection();
        printf(" Layer1 getOutputCollection - %f == %f \n",internal[neuronIndex], 0.091);
        assert( internal[neuronIndex] > 0.09 && internal[neuronIndex] < 0.092);
    }

    double sigma ;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        sigma = layertArray[0].lastLayerSigma(neuronIndex, 0.15);
        printf("Validating sigma  %f \n", sigma);
        assert( sigma > -0.01 && sigma < 0.01);
    }

    sigma = 0.0;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        sigma = layertArray[1].lastLayerSigma(neuronIndex, 0.091);
        printf("Validating sigma  %f \n", sigma);
        assert( sigma > -0.01 && sigma < 0.01);
    }

    delete [] inputs;
    delete [] synapses;
    delete [] layertArray;
    return 0; 
} 
