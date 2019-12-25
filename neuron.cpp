/*
How to use: 
first call init method, with number of input with umbral input inclusive.
than call setSynapses with w0 = - theta
next call thresshold to get the activation function
*/
#include "neuron.h"
#include <math.h>
#include <stdio.h>

Neuron::Neuron(){}
void 
Neuron::init(int numberOfDentrites, int activationType, int biasType){
   this->biasType = biasType;
   switch (biasType) {
      case BIAS_NONE:
         break;
      case BIAS_POSITIVE:
      case BIAS_NEGATIVE:
         numberOfDentrites++;
         break;
      default: break;
   }
   this->numberOfDentrites = numberOfDentrites;
   this->activationType = activationType;
   synapses = new double[numberOfDentrites];
   return;
}

Neuron::~Neuron(){
   printf("=========~Neuron============ \n");
   delete []synapses;
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
         result = summation*2.0*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         result = summation*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         result = summation;
         break;
      default: break;
   }
   return result;
}

void
Neuron::setSynapses(const double* const newSynapses) {
   int i;
   for(i = 0; i < numberOfDentrites ; i++)
      synapses[i] = newSynapses[i];
   return;
}

double* Neuron::getSynapses(){
   return synapses;
}

double
Neuron::getOutput(const double* const inputs) {
   double vk = 0.0;
   int inputsAmount = numberOfDentrites;
   int synapsesOffset = 0;

   if (biasType != BIAS_NONE) {
      inputsAmount = numberOfDentrites - 1;
      synapsesOffset = 1;
      if(biasType == BIAS_POSITIVE) {
          vk += synapses[0] * 1;
      }
      if(biasType == BIAS_NEGATIVE) {
          vk += synapses[0] * -1;
      }
   }

   for(int inputIndex = 0; inputIndex < inputsAmount ; inputIndex++){
      vk += synapses[inputIndex+synapsesOffset] * inputs[inputIndex];
   }
   this->lastExit = activationFunction(vk);
   return this->lastExit;
}

double Neuron::getLastExit(){
   return lastExit;
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
sigma = -error * f'()
*/
double Neuron::lastNeuronSigma(double expectedOutput){
   return activationFunctionDerivated(lastExit - expectedOutput);
}

/*
sigma = summation  * f'()
*/
double Neuron::currentNeuronSigma(double summation) {
   return activationFunctionDerivated(summation);
}