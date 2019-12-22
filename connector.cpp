#include "connector.h"
#include "neuron.h"
#include "layer.h"

#define AMOUNT_OF_NEURON_IN_LAYER_AT(i) amountOfNeuronsPerLayer[i]

#define LAST_LAYER_INDEX(i) i-1

ArtificialNeuralNetwork::ArtificialNeuralNetwork(int layers, int* neuronsPerLayer,
 int activationFunctionType, int lastLayerActivationFunction, int biasType){

   maxAmountOfNeuronsInALayer = 0;
   layersAmount = layers;
   int lastLayerIndex = LAST_LAYER_INDEX(layersAmount);

   layertArray = new Layer [layersAmount];

   for(int layoutIndex = 0; layoutIndex < lastLayerIndex ; ++layoutIndex){
      layertArray[layoutIndex].init( neuronsPerLayer[layoutIndex],
                           activationFunctionType,
                           neuronsPerLayer[layoutIndex-1],biasType);
  }

  layertArray[ lastLayerIndex ].init(neuronsPerLayer[lastLayerIndex],
                                  lastLayerActivationFunction,
                                 neuronsPerLayer[ lastLayerIndex-1], biasType);

   for(int i = 0; i < layersAmount; ++i)
      if(maxAmountOfNeuronsInALayer < neuronsPerLayer[i])
         maxAmountOfNeuronsInALayer = neuronsPerLayer[i];

   maxAmountOfNeuronsInALayer++;
   temporalOutputOfLayer = new double [maxAmountOfNeuronsInALayer];

   outputOfTheLastLayer = new double[neuronsPerLayer[lastLayerIndex]];
}

/*Get the number of dentrites*/
ArtificialNeuralNetwork::~ArtificialNeuralNetwork(){
   delete [] layertArray;
   delete [] temporalOutputOfLayer;
   delete [] outputOfTheLastLayer;
}

Layer* ArtificialNeuralNetwork::getLayer(int layerIndex){
   return &layertArray[layerIndex];
}

double*
ArtificialNeuralNetwork::sThresshold(const double* const inputs){
   //prepare inputs for looping
   int neuronAmount = layertArray[0].getLayerNeuronAmount(); 
   for(int k = 0; k < neuronAmount ; k++) {
      temporalOutputOfLayer[k] = inputs[k];
   }
   
   for(int layerIndex = 0; layerIndex < layersAmount ; ++layerIndex){
      //get the output of the layer
      temporalOutputOfLayer = layertArray[layerIndex].rankThresshold(temporalOutputOfLayer);
   }

   // copy values of last result
   int lastIndex = LAST_LAYER_INDEX(layersAmount);
   neuronAmount = layertArray[lastIndex].getLayerNeuronAmount(); 
   for(int neuronIndex = 0; neuronIndex < neuronAmount ; ++neuronIndex){
      outputOfTheLastLayer[neuronIndex]=temporalOutputOfLayer[neuronIndex];
   }  
     
   return outputOfTheLastLayer;
}

double ArtificialNeuralNetwork::sigma(int layerIndex, int neuronIndex, double expectedOutput){

   double* currentLayerOutcome;
   double sI;
   double* wIN;
   double summation = 0.0;

   //exit condition: If I'm the last layer
   if(layerIndex == LAST_LAYER_INDEX(layersAmount)){
      return layertArray[layerIndex].lastLayerSigma(neuronIndex, currentLayerOutcome[neuronIndex]);
   }
   //otherwise get the summation of
   // the sigmas multiplied by synaptic weight going from the current neuron 
   //to that neuron of next layer
   int neuronAmount = layertArray[layerIndex+1].getLayerNeuronAmount(); 
   for(int neuronIndex = 0;neuronIndex < neuronAmount ;neuronIndex++){
      sI = sigma(layerIndex+1, neuronIndex, expectedOutput);
      wIN = layertArray[layerIndex+1].getNeuronAt(neuronIndex)->getSynapses();
      summation += sI*wIN[neuronIndex];
   }

   return layertArray[layerIndex].currentLayerSigma(neuronIndex, summation);
}

void ArtificialNeuralNetwork::fixSynapses(int layerIndex, int neuronIndex,double alpha, double expectedOutput){
   double* inputReceived;
   double* WJI;
   double sigmaLayerNeuron;

   /* The amount of entries of the layer i ,
   is equal on the amount of outputs on the layer i-1 (the layer before)*/
   int amountOfEntrys = layertArray[layerIndex-1].getLayerNeuronAmount();

   //for each dentrite I look for its synapse and the input it had
   //the outcome of the last layer
   inputReceived = layertArray[layerIndex-1].getOutputCollection();
   WJI = layertArray[layerIndex].getNeuronAt(neuronIndex)->getSynapses();
   sigmaLayerNeuron = sigma(layerIndex,neuronIndex, expectedOutput);
   for(int dentriteIndex = 0; dentriteIndex < amountOfEntrys;dentriteIndex++) {
      //update the synapses
      WJI[dentriteIndex] +=  alpha * sigmaLayerNeuron * inputReceived[dentriteIndex];
   }
   return;
}
