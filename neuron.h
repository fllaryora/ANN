/*
@Author: Francisco Adrian Llaryora 

The neuron class represents a neuron in an artificial neural network (as kwon as A.N.N.).
This class will ignore neither the layer to which it belongs nor its position in it.

Every neuron in an ANN consists of:
- 1 to n entries called inputs.
This entry would correspond to the axon of the previous layer or to the entry of the ANN.
- Each entry is associated with a weight called a synapse.
- Each entry is multiplied with its synapse, this result is called dentrite.
- Optionally there is an extra entry. It is a fixed input (+1 or -1) which is not associated
 with a synapse, like every entry it is multiplied with its synapse, and the result is called bias.
- When all the dentrites and the bias are added together it is called vk.
- Every neuron has one activation function.
This class has implemented only 3 types: sigmoid (also known as logistic),
 Hyperbolic tangent and lineal.
 -The imput of the activation function is the vk
- Every neuron has only 1 wayout called output or axon that is the output of the activation function.
- The output will be taken as input for the next layout or output of the system.  
This class is meant to be a neuron that can learn.
Although this class is not responsible for learning. Another class will set the correct synapses.

*/

#ifndef _NEURON_H_
#define _NEURON_H_
#include <math.h>

#define SIGMOID(x) 1/(1+exp(-x)) ///because sigmoid func doesn't exists on math.h

//activation function posibilities.
enum {
   ACTIVATION_FUNCTION_SIGMOID, //activation funcion: the output is 1 or 0
	ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT,  //Hyperbolic tangent: the output is 1 or -1
   ACTIVATION_FUNCTION_LINEAL // the output is vk
};

class Neuron{
public:

   Neuron(); //It doesn't anything
   void init(int size, int activationType);
   ~Neuron();
   void setSynapses(const double* const synapses);
   double* getSynapses();
   //TODO: rename it only can be consider thresshold if the output of
   //the activation function is  0 or 1.
   double thresshold(const double* const inputs); 
   double getLastExit();
   /*
   If this Neuron is in the last layer it will be called.
   */
   double lastLayerSigma(double expectedOutput);

private:
   int numberOfDentrites;
   int activationType;
   double * synapses;
   double lastExit;
};
#endif //_NEURON_H_

