#include <stdio.h>
#include "connector.h"
#include "neuron.h"
#include "layer.h"
#include <assert.h>

/*   ---- "theReality"  ----- */ 
double theReality (double x1, double x2) {
   if( x1 >= 50.0) {
      if(x2 >= 50.0) {
         return 0.3;
      } else {
         return 0.5;
      }
   } else {
      if(x2 >= 50.0) {
         return 0.1;
      } else {
         return 0.6;
      }
   }
    
}

int main() {
   int numberOfInputs = 2;

   int amountOfLayers = 4;
   int* amountOfNeuronsPerLayer = new int [amountOfLayers];
   amountOfNeuronsPerLayer[0] = 2;
   amountOfNeuronsPerLayer[1] = 3;
   amountOfNeuronsPerLayer[2] = 3;
   amountOfNeuronsPerLayer[3] = 1;
   
   //layer 1 N 1 
   double* w11 = new double [3];
   w11[0] = 1.1; //bias
   w11[1] = -0.2; //x1
   w11[2] = 0.3; //x2
   
   //layer 1 N 2 
   double* w12 = new double [3];
   w12[0] = 0.4; //bias
   w12[1] = -0.5; //x1
   w12[2] = 0.34; //x2
   
   //layer 2 N 1 
   double* w21 = new double [3];
   w21[0] = 0.7; //bias
   w21[1] = 0.73; //x1
   w21[2] = -0.45; //x2

   //layer 2 N 2 
   double* w22 = new double [3];
   w22[0] = 0.9; //bias
   w22[1] = 1.0; //x1
   w22[2] = 1.1; //x2
  
  //layer 2 N 3
   double* w23 = new double [3];
   w23[0] = -0.9; //bias
   w23[1] = 1.56; //x1
   w23[2] = 0.12; //x2

//layer 3 N 1 
   double* w31 = new double [4];
   w31[0] = 0.7; //bias
   w31[1] = 0.73; //x1
   w31[2] = 1.45; //x2
   w31[3] = 0.45; //x3

   //layer 3 N 2 
   double* w32 = new double [4];
   w32[0] = 0.9; //bias
   w32[1] = 1.0; //x1
   w32[2] = -1.1; //x2
   w32[3] = 1.1; //x3
  
  //layer 3 N 3
   double* w33 = new double [4];
   w33[0] = 0.9; //bias
   w33[1] = -0.56; //x1
   w33[2] = 1.12; //x2
   w33[3] = 0.12; //x3

   //layer 4 N 1 
   double* w41 = new double [4];
   w41[0] = 0.25; //bias
   w41[1] = -0.35; //x1
   w41[2] = 1.44; //x2
   w41[3] = 0.55; //x3
  
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
   ann.getLayer(1)->getNeuronAt(2)->setSynapses(3, w23);
   ann.getLayer(2)->getNeuronAt(0)->setSynapses(4, w31);
   
   ////Network can learn test 1

   double alpha = 0.75;
   int zoneAmount = 30;

   double zone[zoneAmount] = { 
      5.0, 9.0, 13.0, 17.0,
      21.0, 25.0, 29.0, 33.0,
      37.0, 41.0, 45.0, 49.0,
      53.0, 57.0, 61.0, 65.0,
      69.0, 73.0, 77.0, 81.0,
      85.0, 89.0, 93.0, 97.0
   };

   for (int i = 0; i < 8000 ; i++) {
      
      for (int x1 = 0 ; x1 < zoneAmount ; x1++) {
         for (int x2 = 0 ; x2 < zoneAmount ; x2++ ) {
            double inputs[numberOfInputs] = {zone[x1], zone[x2]};
            double expectedOutcome = theReality ( zone[x1], zone[x2]);
            ann.getOutput(numberOfInputs, inputs);
            ann.fixSynapses(alpha,numberOfInputs,inputs, 1, &expectedOutcome);
         }
      }
   }

   double moves = 0;
   double matches = 0;

   for (double x1 = 0.0 ; x1 < 100.0 ; x1 = x1 + 1.0) {
      for (double x2 = 0.0 ; x2 < 100.0 ; x2 = x2 + 1.0) {
         double inputs[numberOfInputs] = {x1, x2};
         double expectedOutcome = theReality ( x1, x2);
         double* output = ann.getOutput(numberOfInputs, inputs);
         //printf("Aproximating  %f == %f \n",*output, expectedOutcome);
         moves += 1.0;
         if((*output - expectedOutcome) < 0.2) {
            matches += 1.0;
         }
         
      }
   }

   //assert(abs(*output - expectedOutcome) < 0.1);
   printf("=====Matches = %f ========\n",(matches *100) /moves);
   assert(((matches *100) /moves ) > 90.0);

   printf("======End of main=========\n");
	return 0;

}
