#include "connector.h"
#include "neuron.h"
#include "layer.h"
#include <assert.h>

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
   if( layerIndex < 0 || layerIndex >= layersAmount ) {
   printf("========= getLayer layerIndex is less than 0 or greather than %i ============ \n", layersAmount-1);
      assert(false);
   }
   return &layertArray[layerIndex];
}


double*
ArtificialNeuralNetwork::getOutput(int length, const double* const inputs){
   double* temporalOutputOfEvenLayer = new double [maxAmountOfNeuronsInALayer];
   double* temporalOutputOfOddLayer = new double [maxAmountOfNeuronsInALayer];

   int newInputLength = evaluateLayer(0 ,length, inputs, temporalOutputOfEvenLayer);

   for(int layerIndex = 1; layerIndex < layersAmount ; layerIndex++) {
      if ( layerIndex & 1 ) {
         newInputLength = evaluateLayer(layerIndex ,newInputLength, temporalOutputOfEvenLayer, temporalOutputOfOddLayer);
      } else {
         newInputLength = evaluateLayer(layerIndex ,newInputLength, temporalOutputOfOddLayer, temporalOutputOfEvenLayer);
      }
   }

   copyOutput();
   delete [] temporalOutputOfOddLayer;
   delete [] temporalOutputOfEvenLayer;
   return outputOfTheLastLayer;
}

int
ArtificialNeuralNetwork::evaluateLayer(int layerIndex, int length,
 const double* const inputs, double* output){
    //a bug of g++ here?
   //use the pointer always otherwise at the end of the scope it will call the destructor.
    Layer* layer = &layertArray[layerIndex];
   int neuronAmount = layer->getLayerNeuronAmount();
    for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
       printf("=========PRE===%i=====%i==== \n", layerIndex,neuronIndex);
      output[neuronIndex] = layer->getNeuronAt(neuronIndex)->getOutput(length, inputs);
      printf("=========POST============ \n");
   }
   return neuronAmount;
}

void
ArtificialNeuralNetwork::copyOutput() {
   Layer* layer = &layertArray[layersAmount-1];
   int neuronAmount = layer->getLayerNeuronAmount();
   for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
       printf("=========COPY===%i=====%i==== \n", layersAmount-1, neuronIndex);
      outputOfTheLastLayer[neuronIndex] = layer->getNeuronAt(neuronIndex)->getLastExit();
      printf("=========POST COPY============ \n");
   }
   return;
}

void ArtificialNeuralNetwork::fixSynapses(double alpha, double expectedOutput){
   /*
   double* temporalSigmaOfLayer = new double [maxAmountOfNeuronsInALayer];
   double* temporalSigmaOfLayer2 = new double [maxAmountOfNeuronsInALayer];
   double* synapsesOfCurrentNeuron;

   //First: get last layer sigmas
   int neuronAmount = layertArray[(layersAmount-1)].getLayerNeuronAmount();
   if ( (layersAmount-1) & 1 ) {
       for(int neuronIndex = 0;neuronIndex < neuronAmount ;neuronIndex++){
          synapsesOfCurrentNeuron = layertArray[(layersAmount-1)].
            getNeuronAt(neuronIndex)->getSynapses();
         temporalSigmaOfLayer2[neuronIndex] = layertArray[(layersAmount-1)].
            getNeuronAt(neuronIndex)->lastNeuronSigma(expectedOutput);
         for()
            synapsesOfCurrentNeuron[neuronIndex] +=  alpha * temporalSigmaOfLayer2[neuronIndex] * inputReceived[neuronIndex];
       }
   } else {
       for(int neuronIndex = 0;neuronIndex < neuronAmount ;neuronIndex++){
          synapsesOfCurrentNeuron = layertArray[(layersAmount-1)].
            getNeuronAt(neuronIndex)->getSynapses();
         temporalSigmaOfLayer[neuronIndex] = layertArray[(layersAmount-1)].
            getNeuronAt(neuronIndex)->lastNeuronSigma(expectedOutput);
       }
   }

   //So I need he last layer sigma for the next calculation
   for (int layerIndex = (layersAmount-2); layerIndex >= 0;layerIndex--) {
      /* The amount of entries of the layer i ,
      is equal on the amount of outputs on the layer i-1 (the layer before)
      
      if ( (layersAmount-1) & 1 ) {
         for(int neuronIndex = 0;neuronIndex < neuronAmount ;neuronIndex++){
            temporalSigmaOfLayer2[neuronIndex] = layertArray[(layersAmount-1)].
               getNeuronAt(neuronIndex)->lastNeuronSigma(expectedOutput);
         }
      } else {
         for(int neuronIndex = 0;neuronIndex < neuronAmount ;neuronIndex++){
            temporalSigmaOfLayer[neuronIndex] = layertArray[(layersAmount-1)].
               getNeuronAt(neuronIndex)->lastNeuronSigma(expectedOutput);
         }
      }
   }

   delete [] temporalSigmaOfLayer;
   delete [] temporalSigmaOfLayer2;
   */
   return;
}
