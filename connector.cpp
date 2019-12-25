#include "connector.h"
#include "neuron.h"
#include "layer.h"

ArtificialNeuralNetwork::ArtificialNeuralNetwork(int layers, int enties, int* neuronsPerLayer,
 int activationFunctionType, int lastLayerActivationFunction, int biasType){

   maxAmountOfNeuronsInALayer = 0;
   layersAmount = layers;
   int lastLayerIndex = layersAmount-1;

   layertArray = new Layer [layersAmount];

   layertArray[0].init( neuronsPerLayer[0],
                           activationFunctionType,
                           enties, biasType);
   for(int layoutIndex = 1; layoutIndex < lastLayerIndex ; ++layoutIndex){
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

   outputOfTheLastLayer = new double[neuronsPerLayer[lastLayerIndex]];
}

/*Get the number of dentrites*/
ArtificialNeuralNetwork::~ArtificialNeuralNetwork(){
   printf("======~ArtificialNeuralNetwork=========");
   delete [] outputOfTheLastLayer;
   delete [] layertArray;
}

Layer* ArtificialNeuralNetwork::getLayer(int layerIndex){
   return &layertArray[layerIndex];
}

double*
ArtificialNeuralNetwork::getOutput(const double* const inputs){
   double* temporalOutputOfLayer = new double [maxAmountOfNeuronsInALayer];
   double* temporalOutputOfLayer2 = new double [maxAmountOfNeuronsInALayer];

   //a bug of g++ here
   //use the pointer always other wise the end of the for will call the destructor for you.
   Layer* layer = &layertArray[0];
   int neuronAmount = layer->getLayerNeuronAmount();
    for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
       printf("=========PRE===%i=====%i==== \n",0,neuronIndex);
      temporalOutputOfLayer[neuronIndex] = layer->getNeuronAt(neuronIndex)->getOutput(inputs);
      printf("=========POST============ \n");
   }

   for(int layerIndex = 1; layerIndex < layersAmount ; layerIndex++) {
      //a bug of g++ here
      //use the pointer always other wise the end of the for will call the destructor for you.
      Layer* layer = &layertArray[layerIndex];
      int neuronAmount = layer->getLayerNeuronAmount(); 
      for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
         Neuron* neuron = layer->getNeuronAt(neuronIndex);
         if ( layerIndex & 1 ) {
            printf("=========PRE===%i=====%i==== \n",layerIndex,neuronIndex);
            temporalOutputOfLayer2[neuronIndex] = neuron->getOutput(temporalOutputOfLayer);
            printf("=========POS============ \n");
         } else {
            printf("=========PRE===%i=====%i==== \n",layerIndex,neuronIndex);
            temporalOutputOfLayer[neuronIndex] = neuron->getOutput(temporalOutputOfLayer2);
            printf("=========POS============ \n");
         }
      }
   }
   printf("=========COPY TIME============ \n");
   layer = &layertArray[layersAmount-1];
   neuronAmount = layer->getLayerNeuronAmount(); 
   int lastLayerIndex = layersAmount-1;
   if ( lastLayerIndex & 1 ) {
      printf("=========ODD COPY============ \n");
      for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
         printf("=========COPY Neuron : %i==of===%i======= \n", neuronIndex, maxAmountOfNeuronsInALayer);
         outputOfTheLastLayer[neuronIndex] = temporalOutputOfLayer2[neuronIndex];    
      }
   } else {
      printf("=========EVEN COPY============ \n");
      for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
         printf("=========COPY Neuron : %i==of===%i======= \n", neuronIndex, maxAmountOfNeuronsInALayer);
         outputOfTheLastLayer[neuronIndex] = temporalOutputOfLayer[neuronIndex]; 
      }
   }
   delete [] temporalOutputOfLayer2;
   delete [] temporalOutputOfLayer;
   return outputOfTheLastLayer;
}

double ArtificialNeuralNetwork::sigma(int layerIndex, int neuronIndex, double expectedOutput) {
   double sI;
   double* wIN;
   double summation = 0.0;

   //exit condition: If I'm the last layer
   if(layerIndex == (layersAmount-1) ){
      return layertArray[layerIndex].getNeuronAt(neuronIndex)->
         lastNeuronSigma(expectedOutput);
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

   return layertArray[layerIndex].getNeuronAt(neuronIndex)->
      currentNeuronSigma(summation);
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
   //inputReceived = layertArray[layerIndex-1].getOutputCollection();
   WJI = layertArray[layerIndex].getNeuronAt(neuronIndex)->getSynapses();
   sigmaLayerNeuron = sigma(layerIndex,neuronIndex, expectedOutput);
   for(int dentriteIndex = 0; dentriteIndex < amountOfEntrys;dentriteIndex++) {
      //update the synapses
      WJI[dentriteIndex] +=  alpha * sigmaLayerNeuron * inputReceived[dentriteIndex];
   }
   return;
}
