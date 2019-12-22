/*
@Author: Francisco Adrian Llaryora

 The Class Layer represent a layer with n neurons. 
 The class does not know if it is an input layer, a hidden layer or an output layer.
 The model is neuron network on the hide layouts.
*/

#ifndef _LAYER_H_
#define _LAYER_H_
#include "neuron.h"

class Layer{
public:

   Layer();// It doesn't anything.
/**
  neuronAmount = amount of neurons in the layer
  activationType = activacion function type read neuron.h for more information.
  biasType = enum of type of bias
  enties = This is the number of inputs that each neuron will have. (not include the bias entry)
  
*/
   void init(int neuronAmount, int activationType, int enties, int biasType);

   ~Layer();

   /*
   For the neuron in position i of the layer (start at 0),
   */
   Neuron* getNeuronAt(int index);

/*
It apply the same inputs for the all neurons in the layer.
Each output of its corresponding neuron is collected 
return the collection of the outputs.
*/
   double* rankThresshold(const double* const inputs);

/**
 * return a collection of last Exit of each neuron in this layer
*/
   double* getOutputCollection();

   /**
    * return layer Neuron Amount
    * */
   int getLayerNeuronAmount();

   /*
      asuming it is the last layer this function will be called.
   */
   double lastLayerSigma(int neuronIndex, double expectedOutput);

   /*
      return sigma of summation
   */
   double currentLayerSigma(int neuronIndex, double summation);
   
private:
   int layerNeuronAmount;
   double* outputCollection;
   Neuron* neuronArray;
};
#endif //_LAYER_H_
