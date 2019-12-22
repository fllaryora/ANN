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
Neuron::init(int size, int activationType){
   numberOfDentrites = size;
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
Neuron::thresshold(const double* const inputs){
   int i;
   double vk= 0.0;
   
   for(i = 0; i < numberOfDentrites ; i++){
      //printf("input %f \n", inputs[i]);
      vk += synapses[i] * inputs[i];
      // printf("vk %f == %f >  %f \n",synapses[i], inputs[i], vk );
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

