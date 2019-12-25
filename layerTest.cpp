#include <stdio.h>
#include "neuron.h"
#include "layer.h"
#include <assert.h>

int main() {

    int neuronAmount = 3; 
    int numberOfDentritesSeven = 7;
    int numberOfDentritesSix = 6;
    int layersAmount = 2;

    Layer* layertArray = new Layer [layersAmount];
  
    layertArray[0].init(neuronAmount,
       ACTIVATION_FUNCTION_LINEAL, numberOfDentritesSeven, BIAS_NONE);
    layertArray[1].init(neuronAmount,
       ACTIVATION_FUNCTION_LINEAL, numberOfDentritesSix, BIAS_POSITIVE);

    printf("Neuron amount %i == %i \n",layertArray[0].getLayerNeuronAmount() , neuronAmount);
    assert(layertArray[1].getLayerNeuronAmount() == neuronAmount);

    return 0; 
} 
