#include <stdio.h>
#include "connector.h"
#include "neuron.h"
#include "layer.h"
#include <assert.h>

int main() {
   int numberOfInputs = 2;
   double inputs[numberOfInputs] = {1.3, 0.4};

   int amountOfLayers = 3;
   int* amountOfNeuronsPerLayer = new int [amountOfLayers];
   amountOfNeuronsPerLayer[0] = 2;
   amountOfNeuronsPerLayer[1] = 2;
   amountOfNeuronsPerLayer[2] = 1;
   
   //layer 1 N 1 
   double* w11 = new double [3];
   w11[0] = 0.1; //bias
   w11[1] = 0.2; //x1
   w11[2] = 0.3; //x2
   
   double expectedOutcome11 = w11[0] + inputs[0] * w11[1] + inputs[1] * w11[2];
   expectedOutcome11 = SIGMOID(expectedOutcome11);
   //printf("expectedOutcome11 == %f \n",expectedOutcome11);
   //layer 1 N 2 
   double* w12 = new double [3];
   w12[0] = 0.4; //bias
   w12[1] = 0.5; //x1
   w12[2] = 1.6; //x2
   
   double expectedOutcome12 = w12[0] + inputs[0] * w12[1] + inputs[1] * w12[2];
   expectedOutcome12 = SIGMOID(expectedOutcome12);
   //printf("expectedOutcome12 == %f \n",expectedOutcome12);
   //layer 2 N 1 
   double* w21 = new double [3];
   w21[0] = 0.7; //bias
   w21[1] = 0.8; //x1
   w21[2] = 0.9; //x2
   double expectedOutcome21 = w21[0] + expectedOutcome11 * w21[1] + expectedOutcome12 * w21[2];
   expectedOutcome21 = SIGMOID(expectedOutcome21);
   //printf("expectedOutcome21 == %f \n",expectedOutcome21);

   //layer 2 N 2 
   double* w22 = new double [3];
   w22[0] = 0.9; //bias
   w22[1] = 1.0; //x1
   w22[2] = 1.1; //x2
   double expectedOutcome22 = w22[0] + expectedOutcome11 * w22[1] + expectedOutcome12 * w22[2];
   expectedOutcome22 = SIGMOID(expectedOutcome22);
   //printf("expectedOutcome22 == %f \n",expectedOutcome22);
   //layer 3 N 1 
   double* w31 = new double [3];
   w31[0] = 1.2; //bias
   w31[1] = 1.3; //x1
   w31[2] = 1.4; //x2
   double expectedOutcome31 = w31[0] + expectedOutcome21 * w31[1] + expectedOutcome22 * w31[2];
   expectedOutcome31 = SIGMOID(expectedOutcome31);
   //printf("expectedOutcome31 == %f \n",expectedOutcome31);

   ArtificialNeuralNetwork ann = ArtificialNeuralNetwork(
      amountOfLayers,
      numberOfInputs,
      amountOfNeuronsPerLayer,
      ACTIVATION_FUNCTION_SIGMOID,
      ACTIVATION_FUNCTION_SIGMOID,
      BIAS_POSITIVE);

   ann.getLayer(0)->getNeuronAt(0)->setSynapses(3, w11);
   ann.getLayer(0)->getNeuronAt(1)->setSynapses(3, w12);
   ann.getLayer(1)->getNeuronAt(0)->setSynapses(3, w21);
   ann.getLayer(1)->getNeuronAt(1)->setSynapses(3, w22);
   ann.getLayer(2)->getNeuronAt(0)->setSynapses(3, w31);
   
   double* output = ann.getOutput(2, inputs);
   
   printf("output  %f == %f \n",*output, expectedOutcome31);
   assert(abs(*output - expectedOutcome31) < 0.01);
   
   //create a new expectedOutcome by adding a error in expectedOutcome31 
   double expectedOutcome = expectedOutcome31 - 0.654321;
   double alpha = 0.5;

   for (int i = 0; i < 800 ; i++) {
      printf("======Loop==%i=======\n", i);
      ann.fixSynapses(alpha,2,inputs, 1, &expectedOutcome);
      output = ann.getOutput(2, inputs);
      printf("Aproximating  %f == %f \n",*output, expectedOutcome);
   }
   printf("Aproximating  %f == %f \n",*output, expectedOutcome);
   assert(abs(*output - expectedOutcome) < 0.0001);

   ann.getLayer(0)->getNeuronAt(0)->setSynapses(3, w11);
   ann.getLayer(0)->getNeuronAt(1)->setSynapses(3, w12);
   ann.getLayer(1)->getNeuronAt(0)->setSynapses(3, w21);
   ann.getLayer(1)->getNeuronAt(1)->setSynapses(3, w22);
   ann.getLayer(2)->getNeuronAt(0)->setSynapses(3, w31);

   expectedOutcome = expectedOutcome31 - 0.543219;
    alpha = 0.5;

   for (int i = 0; i < 800 ; i++) {
      printf("======Loop==%i=======\n", i);
      ann.fixSynapses(alpha,2,inputs, 1, &expectedOutcome);
      output = ann.getOutput(2, inputs);
      printf("Aproximating  %f == %f \n",*output, expectedOutcome);
   }
   printf("Aproximating  %f == %f \n",*output, expectedOutcome);
   assert(abs(*output - expectedOutcome) < 0.0001);

   printf("======End of main=========\n");
	return 0;
}
