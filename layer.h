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

   /**
    * return layer Neuron Amount
    * */
   int getLayerNeuronAmount();
   
private:
   int layerNeuronAmount;
   Neuron* neuronArray;
};
#endif //_LAYER_H_
