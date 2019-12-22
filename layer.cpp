/*
How to use: 
first call init method, with number of input with umbral input inclusive.
then call setRankSynapses with w0 = - theta,
 one by one of each neuron i= 0,1,2,3...and so on.
next call rankThresshold to get the activation function array
*/

#include "layer.h"
#include "neuron.h"

Layer::Layer(){
}

void
Layer::init(int neuronAmount, int activationType, int enties, int biasType){
   this->layerNeuronAmount = neuronAmount;
   this->outputCollection = new double [neuronAmount];
   this->neuronArray = new Neuron [neuronAmount];
   
   for(int i = 0; i < neuronAmount; ++i){
      this->neuronArray[i].init(enties, activationType, biasType);
   }
}

/*Get the number of dentrites*/
Layer::~Layer(){
   delete [] outputCollection;
   delete [] neuronArray;
}

Neuron* Layer:: getNeuronAt(int index){
   return &neuronArray[index];
}

double*
Layer::rankThresshold(const double* const inputs){ 
   for(int i = 0; i < layerNeuronAmount; ++i)
     outputCollection[i] = neuronArray[i].thresshold(inputs); 
   return outputCollection;
}

double* Layer::getOutputCollection(){
   return outputCollection;
}

int Layer::getLayerNeuronAmount(){
   return this->layerNeuronAmount;
}

double Layer::lastLayerSigma(int neuronIndex, double expectedOutput){
   return neuronArray[neuronIndex].lastNeuronSigma(expectedOutput);
}

double Layer::currentLayerSigma(int neuronIndex, double summation){
   return neuronArray[neuronIndex].currentNeuronSigma(summation);
}