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
   //printf("========= getLayer layerIndex is less than 0 or greather than %i ============ \n", layersAmount-1);
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
   //use the pointer always otherwise at the end of the scope it will call the destructor.
    Layer* layer = &layertArray[layerIndex];
   int neuronAmount = layer->getLayerNeuronAmount();
    for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
      // printf("=========PRE===%i=====%i==== \n", layerIndex,neuronIndex);
      output[neuronIndex] = layer->getNeuronAt(neuronIndex)->getOutput(length, inputs);
     // printf("=========POST============ \n");
   }
   return neuronAmount;
}

void
ArtificialNeuralNetwork::copyOutput() {
   Layer* layer = &layertArray[layersAmount-1];
   int neuronAmount = layer->getLayerNeuronAmount();
   for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
     //  printf("=========COPY===%i=====%i==== \n", layersAmount-1, neuronIndex);
      outputOfTheLastLayer[neuronIndex] = layer->getNeuronAt(neuronIndex)->getLastOutcome();
      //printf("=========POST COPY============ \n");
   }
   return;
}

int
ArtificialNeuralNetwork::copyOutputOfLayer(int layerIndex, double* output) {
   Layer* layer = &layertArray[layerIndex];
   int neuronAmount = layer->getLayerNeuronAmount();
   for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++) {
      // printf("=========COPY===%i=====%i==== \n", layersAmount-1, neuronIndex);
      output[neuronIndex] = layer->getNeuronAt(neuronIndex)->getLastOutcome();
      //printf("=========POST COPY============ \n");
   }
   return neuronAmount;
}

void ArtificialNeuralNetwork::fixSynapses( double alpha,
      int lengthOfInput, const double* const inputs,
      int lengthOfOutput, const double* const expectedOutput) {
      
   //First set each sigma to each neuron.
   applySigmaForLastLayer( lengthOfOutput, expectedOutput );
   for (int layerIndex = layersAmount-2; layerIndex >= 0 ;layerIndex-- ){
      applySigmaForLayer(layerIndex);
   }

   double* temporalInputLayer = new double [maxAmountOfNeuronsInALayer];
   int inputLength = lengthOfInput;
   for(int neuronIndex = 0; neuronIndex < inputLength ; neuronIndex++) {
      // printf("=========COPY===%i=====%i==== \n", layersAmount-1, neuronIndex);
      temporalInputLayer[neuronIndex] = inputs[neuronIndex];
      //printf("=========POST COPY============ \n");
   }
   for(int layerIndex = 0; layerIndex < layersAmount ; layerIndex++) {
      Layer* layer = &layertArray[layerIndex];
      int neuronAmount = layer->getLayerNeuronAmount();
      for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++){
         layer->getNeuronAt(neuronIndex)->fixSynapses(inputLength, temporalInputLayer, alpha);
      }
      inputLength = copyOutputOfLayer(layerIndex, temporalInputLayer);
   }
   
   delete [] temporalInputLayer;
   return;
}

void ArtificialNeuralNetwork::applySigmaForLastLayer(int lengthOfOutput, const double* const expectedOutput ) {
//for the last layer...
   Layer* layer = &layertArray[(layersAmount-1)];
   int neuronAmount = layer->getLayerNeuronAmount();
   assert(lengthOfOutput == neuronAmount);
   for(int neuronIndex = 0; neuronIndex < neuronAmount ; neuronIndex++){
      double lastOutcome = layer->getNeuronAt(neuronIndex)->getLastOutcome();
      layer->getNeuronAt(neuronIndex)->calculateSigma(expectedOutput[neuronIndex]-lastOutcome);
   }
}

void ArtificialNeuralNetwork::applySigmaForLayer(int layerIndex) {
      if( layerIndex >= (layersAmount-1) || layerIndex < 0) {
         //printf("=========applySigmaForLayer BAD INDEX===%i========= \n", layerIndex);
         assert(false);
      }
      Layer* nextLayer = &layertArray[layerIndex+1];
      int nextAmount = nextLayer->getLayerNeuronAmount();
      Layer* thisLayer = &layertArray[layerIndex];
      int neuronAmount2 = thisLayer->getLayerNeuronAmount();
      for(int neuronIndex = 0; neuronIndex < neuronAmount2 ; neuronIndex++){
         double summation = 0.0;
         for(int neuronIndexPast = 0; neuronIndexPast < nextAmount ; neuronIndexPast++){
            double sigma = nextLayer->getNeuronAt(neuronIndexPast)->getLastSigma();
            //this is the bound between this neuron with the other
            double synaps = nextLayer->getNeuronAt(neuronIndexPast)->getBoundSynapses(neuronIndex);
            summation += sigma * synaps;
         }
         thisLayer->getNeuronAt(neuronIndex)->calculateSigma(summation);
      }
   return;
}
