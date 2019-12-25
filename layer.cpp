/*
How to use: 
first call init method, with number of input with umbral input inclusive.
then call setRankSynapses with w0 = - theta,
 one by one of each neuron i= 0,1,2,3...and so on.
next call rankThresshold to get the activation function array
*/
#include <stdio.h>
#include "layer.h"
#include "neuron.h"
#include <assert.h>

Layer::Layer(){
}

void
Layer::init(int neuronAmount, int activationType, int enties, int biasType){
   if (neuronAmount <= 0){
      printf("=========neuronAmount per layer must be at least 1============ \n");
      assert(false);
   }
   

   this->layerNeuronAmount = neuronAmount;
   this->neuronArray = new Neuron [neuronAmount];
   
   for(int i = 0; i < neuronAmount; ++i){
      this->neuronArray[i].init(enties, activationType, biasType);
   }
}

/*Get the number of dentrites*/
Layer::~Layer(){
   printf("=========~Layer============ \n");
   delete [] neuronArray;
}

Neuron* Layer:: getNeuronAt(int index){
   return &neuronArray[index];
}

int Layer::getLayerNeuronAmount(){
   return this->layerNeuronAmount;
}