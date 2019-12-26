/*
@Author: Francisco Adrian Llaryora

 Artificial Neural Network represent a set of layers, and their connections.
 The topology is the basic: the axon of the layer i connect with each neurone on the layer i+1.
*/

#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_
#include "layer.h"
#include <stdio.h>

class ArtificialNeuralNetwork{
public:
/*
layers = amount of layers
enties = number of entries of the first layer
neuronsPerLayer = is a collection on amount of neurons in each layer.
activationFunctionType = activation function  for all layers except the last one.
lastLayerActivationFunction = activation function  for  last layer.

So what is the amount of outputs?
The amount of output is the number of neurons of the last layer !!
*/
   ArtificialNeuralNetwork(int layers, int enties, int* neuronsPerLayer,
 int activationFunctionType, int lastLayerActivationFunction,
  int biasType); 
   ~ArtificialNeuralNetwork();
/*
   get layer at layerIndex (start in 0)
   */
   Layer* getLayer(int layerIndex);

/*
 the first input of the collection is equal to one.
return a colection of values of the last layer
It is the output of the neuronal Network
*/
   double* getOutput(int length, const double* const inputs); 


   /* 
   calculate the error gotten and set a new set of synapses.
   using back propagation algorithm.
   alpha = punishment factor
   */
   void fixSynapses(double alpha,
      int lengthOfInput, const double* const inputs,
      int lengthOfOutput, const double* const expectedOutput);

private:
   int layersAmount;
   double* outputOfTheLastLayer;
   Layer* layertArray;
   int maxAmountOfNeuronsInALayer;
   /* return the new input lenght
   */
   int evaluateLayer(int layerIndex, int length, const double* const inputs, double* output);
   void copyOutput();
   int copyOutputOfLayer(int layerIndex, double* output);

   void applySigmaForLayer(int layerIndex);
   void applySigmaForLastLayer(int lengthOfOutput, const double* const expectedOutput );
};
#endif //_CONNECTOR_H_

