/*
How to use: 
first call init method, with number of input with umbral input inclusive.
than call setSynapses with w0 = - theta
next call thresshold to get the activation function
*/
#include "neuron.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

Neuron::Neuron(){}
void 
Neuron::init(int numberOfDentrites, int activationType, int biasType){
  validateNeuronInputs( numberOfDentrites,  activationType,  biasType);
   
   switch (biasType) {
      case BIAS_NONE:
         break;
      case BIAS_POSITIVE:
      case BIAS_NEGATIVE:
         numberOfDentrites++;
         break;
      default: break;
   }

   this->biasType = biasType;
   this->numberOfDentrites = numberOfDentrites;
   this->activationType = activationType;
   synapses = new double[numberOfDentrites];
   return;
}

Neuron::~Neuron(){
   printf("=========~Neuron============ \n");
   delete []synapses;
}

void
Neuron:: validateNeuronInputs(int numberOfDentrites, int activationType, int biasType) {
 if(numberOfDentrites < 1) {
      printf("=========numberOfDentrites must be >= 1============ \n");
      assert(numberOfDentrites < 1);
   }

   switch (biasType) {
      case BIAS_NONE:
      case BIAS_POSITIVE:
      case BIAS_NEGATIVE: break;
      default:
         printf("=========this biasType is unimplemented============ \n");
         assert( false);
       break;
   }

   switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
      case ACTIVATION_FUNCTION_SIGMOID:
      case ACTIVATION_FUNCTION_LINEAL: break;
      default:
         printf("=========this activationType is unimplemented============ \n");
         assert( false);
      break;
   }
}

 double Neuron::activationFunction(double vk) {
   double result ;
   switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
         result = tanh(vk);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         result = SIGMOID(vk);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         result = vk;
         break;
      default: break;
   }
   printf("vk == %f  \n", vk);
   return result;
 }

double Neuron::activationFunctionDerivated(double summation) {
   double result ;
  switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
         result = summation*2.0*lastOutcome*(1.0-lastOutcome);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         result = summation*lastOutcome*(1.0-lastOutcome);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         result = summation;
         break;
      default: break;
   }
   return result;
}

void
Neuron::setSynapses(int inputLength, const double* const newSynapses) {
   validateDentrites(inputLength);
   for(int dentriteIndex = 0; dentriteIndex < numberOfDentrites ; dentriteIndex++)
      synapses[dentriteIndex] = newSynapses[dentriteIndex];
   return;
}

double* Neuron::getSynapses(){
   return synapses;
}

double Neuron::getBoundSynapses(int entryNumber){
   validateBound(entryNumber);
   int synapsesOffset = 0;
   if (biasType != BIAS_NONE) {
      synapsesOffset = 1;
   }

   return synapses[entryNumber + synapsesOffset];
}

double
Neuron::getOutput(int inputLength, const double* const inputs) {
   validateInputs(inputLength);
   double vk = 0.0;
   
   int synapsesOffset = 0;

   if (biasType != BIAS_NONE) {
      synapsesOffset = 1;
      if(biasType == BIAS_POSITIVE) {
          vk += synapses[0] * 1;
      }
      if(biasType == BIAS_NEGATIVE) {
          vk += synapses[0] * -1;
      }
   }

   for(int inputIndex = 0; inputIndex < inputLength ; inputIndex++){
      vk += synapses[inputIndex+synapsesOffset] * inputs[inputIndex];
   }
   this->lastOutcome = activationFunction(vk);
   return this->lastOutcome;
}

double Neuron::getLastOutcome(){
   return lastOutcome;
}

int Neuron::getNumberOfDentrites(){
   return numberOfDentrites;
}

int Neuron:: getBiasType(){
   return biasType;
}

 int Neuron::getActivationType(){
    return activationType;
 }

/*
sigma = summation  * f'()
*/
double Neuron::calculateSigma(double summation) {
   lastSigma = activationFunctionDerivated(summation);
   return lastSigma;
}

double Neuron::getLastSigma() {
   return lastSigma;
}
void Neuron::validateDentrites(int inputLength){
   if(inputLength != this->numberOfDentrites) {
      printf("=========numberOfDentrites must be == %i============ \n", this->numberOfDentrites);
      assert(false);
   }

   return;
}

void Neuron::validateInputs(int inputs) {
   switch (biasType) {
      case BIAS_NONE:
      if(inputs != this->numberOfDentrites) {
          printf("=========inputs must be == %i ============ \n", this->numberOfDentrites);
         assert( false);
      }
      break;
      case BIAS_POSITIVE:
      case BIAS_NEGATIVE:
      if(inputs != (this->numberOfDentrites-1)) {
          printf("=========inputs must be == %i ============ \n", (this->numberOfDentrites-1));
         assert( false);
      } 
      break;
   }
   return ;
}

void Neuron::validateBound(int entry) {
   if(entry < 0) {
      printf("=========entry must be at least == 0 ============ \n");
      assert( false );
   }

   switch (biasType) {
      case BIAS_NONE:
      if(entry >= this->numberOfDentrites) {
          printf("=========entry must be less than %i ============ \n", this->numberOfDentrites);
         assert( false);
      }
      break;
      case BIAS_POSITIVE:
      case BIAS_NEGATIVE:
      if(entry >= (this->numberOfDentrites-1)) {
          printf("=========entry must be less than %i ============ \n", this->numberOfDentrites-1);
         assert( false);
      }
      break;
   }
   return ;
}

void Neuron::fixSynapses(int inputLength, const double* const inputs, double alpha){
   validateInputs(inputLength);

   int synapsesOffset = 0;

    if (biasType != BIAS_NONE) {
      synapsesOffset = 1;
      if(biasType == BIAS_POSITIVE) {
          synapses[0] -= alpha * lastSigma * 1;
      }
      if(biasType == BIAS_NEGATIVE) {
          synapses[0] -= alpha * lastSigma * -1;
      }
   }
   
   //for each dentrite find each sinaps and their entry
   for(int dentriteIndex = 0; dentriteIndex < inputLength ;dentriteIndex++) {
      synapses[dentriteIndex+synapsesOffset] += alpha * lastSigma * inputs[dentriteIndex];
   }
   return;
}