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
  enties = This is the number of inputs that each neuron will have.
*/
   void init(int neuronAmount, int activationType, int enties);

   ~Layer();

   /*
    For the neuron in position i of the layer (start at 0),
    it will be assigned a list of synapses for each of its corresponding entries.
   */
   void setSynapsesForNeuronAt(int index, const double* const newSynapses);

   /*
   For the neuron in position i of the layer (start at 0),
   return a collection of the current synaps
   */
   double* getSynapsesForNeuronAt(int index);

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

   /**
    * return activation tipe enum
    * */
   int getActivationFunctionType();

private:
   int layerNeuronAmount;
   int eachNeuronEntiesAmount;
   double* outputCollection;
   Neuron* neuronArray;
   int activationFunctionType;
};
#endif //_LAYER_H_
