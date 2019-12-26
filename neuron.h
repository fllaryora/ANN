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

enum {
   BIAS_NONE, //do not use bias 
	BIAS_POSITIVE,  //x0 = 1
   BIAS_NEGATIVE //x0 = -1
};

class Neuron{
public:

   Neuron(); //It doesn't anything
   /*
   biasType = it is the enum of the bias. Is the artifitiall entry.
   activationType = it is the enum of the function activation
   numberOfDentrites = it count only the real entries.
   */
   void init(int numberOfDentrites, int activationType, int biasType);
   ~Neuron();
   void setSynapses(int inputLength, const double* const synapses);
   double* getSynapses();
   double getBoundSynapses(int entryNumber);
   double getOutput(int inputLength, const double* const inputs); 
   double getLastOutcome();
   double getLastSigma();

  /*
  Return real dentrites+bias dentrite if it exists.
  */
   int getNumberOfDentrites();

  /*
  Return bias type.
  */
   int getBiasType();

   /*
  Return getActivation Type.
  */
   int getActivationType();
   /*
   return sigma of the neuron
   */
   double calculateSigma(double summation);
   /*
    inputLength = number of elements of inputs,
   inputs = values of the enties,
   alpha = the punishment rate of the mistake,
   sigma =the rate of mistake.
   */
   void fixSynapses(int inputLength, const double* const inputs, double alpha);

private:
   int numberOfDentrites;
   int activationType;
   int biasType;
   double * synapses;
   double lastOutcome;
   double lastSigma;
   double activationFunction(double vk);
   double activationFunctionDerivated(double vk);
   void validateNeuronInputs(int numberOfDentrites, int activationType, int biasType);
   void validateDentrites(int numberOfDentrites);
   void validateInputs(int inputs);
   void validateBound(int entry);

};
#endif //_NEURON_H_

