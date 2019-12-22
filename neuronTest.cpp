#include <stdio.h>
#include "neuron.h"
#include <assert.h>
#define indexW(d,i,j) (d*i+j)
int main() {

    int neuronAmount = 3; //one per each activation type
    int numberOfDentrites = 7;
    Neuron* neuronArray = new Neuron [neuronAmount];
    double* synapses = new double[numberOfDentrites];
    double* weights = new double[numberOfDentrites*neuronAmount];
    double* inputs = new double[numberOfDentrites*neuronAmount];
    double* temporalWeights = weights;
    double initialWeight = 0.01; 
    double temporalWeight = initialWeight;
    //create weights & input map
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        for(int weightsIndex = 0 ; weightsIndex < numberOfDentrites;weightsIndex++ ){
            weights[indexW(numberOfDentrites, neuronIndex, weightsIndex)] = temporalWeight;
            inputs[indexW(numberOfDentrites, neuronIndex, weightsIndex)] = temporalWeight * 10.0;
            temporalWeight += 0.01;
        }
    }

    neuronArray[0].init(numberOfDentrites, ACTIVATION_FUNCTION_LINEAL);
    neuronArray[1].init(numberOfDentrites, ACTIVATION_FUNCTION_SIGMOID);
    neuronArray[2].init(numberOfDentrites, ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT);
    
    temporalWeight = initialWeight;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        temporalWeights = &weights[indexW(numberOfDentrites,neuronIndex,0)];
        neuronArray[neuronIndex].setSynapses(temporalWeights);
    }

    //validate synapsis values
    temporalWeight = initialWeight;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        temporalWeights = &weights[indexW(numberOfDentrites,neuronIndex,0)];
        double* temporalSynapsis = neuronArray[neuronIndex].getSynapses();
         for(int weightsIndex = 0 ; weightsIndex < numberOfDentrites;weightsIndex++ ){
             printf("Validating synapsis, the element %i %f == %f \n",weightsIndex,
              temporalWeights[weightsIndex] , temporalSynapsis[weightsIndex]);
             assert( temporalWeights[weightsIndex] == temporalSynapsis[weightsIndex]);
             temporalWeight += 0.01;
         }
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        temporalWeights = &inputs[indexW(numberOfDentrites,neuronIndex,0)];
        double outputCollection = neuronArray[neuronIndex].thresshold(temporalWeights); 
        printf("Validating output, the element %i == %f \n", neuronIndex, outputCollection);
        switch (neuronIndex){
        case 0:
            assert( outputCollection > 0.139 && outputCollection < 0.141);
            break;
        case 1:
            assert( outputCollection > 0.704 && outputCollection < 0.706);
            break;
        case 2:
            assert( outputCollection > 0.97 && outputCollection < 0.98);
            break;
        default:
            break;
        }
    }

    delete [] inputs;
    delete [] weights;
    delete [] synapses;
    delete [] neuronArray;
    return 0; 
} 
