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
   delete []synapses;
}

void
Neuron::setSynapses(const double* const newSynapses){
   int i;
   for(i = 0; i < numberOfDentrites ; i++)
      synapses[i] = newSynapses[i];
   return;
}

double* Neuron::getSynapses(){
   return synapses;
}

double
Neuron::thresshold(const double* const inputs) {
   int inputIndex;
   double vk;
   int inputsAmount;
   int synapsesOffset;

   switch (biasType) {
      case BIAS_NONE:
         inputsAmount = numberOfDentrites;
         vk = 0.0;
         synapsesOffset = 0;
         break;
      case BIAS_POSITIVE:
         inputsAmount = numberOfDentrites - 1;
         synapsesOffset = 1;
         vk = synapses[0];
         break;
      case BIAS_NEGATIVE:
         inputsAmount = numberOfDentrites - 1;
         synapsesOffset = 1;
         vk = -synapses[0];
         break;
      default: break;
   }

   for(inputIndex = 0; inputIndex < inputsAmount ; inputIndex++){
      vk += synapses[inputIndex+synapsesOffset] * inputs[inputIndex];
      printf("vk %f == %f >  %f \n",synapses[inputIndex+synapsesOffset], inputs[inputIndex], vk );
   }

   switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
         lastExit = tanh(vk);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         lastExit = SIGMOID(vk);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         lastExit = vk;
         break;
      default: break;
   }

   //printf("fron neuron %f \n", lastExit);
   return lastExit;
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
   double error = expectedOutput -lastExit;
   double sigma ;
   switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
         sigma = -error*2.0*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         sigma = -error*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         sigma = -error;
         break;
      default: break;
   }
   return sigma;
}

/*
sigma =summation  * f'()
*/
double Neuron::currentNeuronSigma(double summation){
   double sigma ;
   switch (activationType) {
      case ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT:
         sigma = summation*2.0*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_SIGMOID:
         sigma = summation*lastExit*(1.0-lastExit);
         break;
      case ACTIVATION_FUNCTION_LINEAL:
         sigma = summation;
         break;
      default: break;
   }
   return sigma;
}
