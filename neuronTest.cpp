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

    neuronArray[0].init(numberOfDentrites, ACTIVATION_FUNCTION_LINEAL, BIAS_NONE);
    neuronArray[1].init(numberOfDentrites, ACTIVATION_FUNCTION_SIGMOID, BIAS_NONE);
    neuronArray[2].init(numberOfDentrites, ACTIVATION_FUNCTION_HIPERBOLIC_TANGENT, BIAS_NONE);
    
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
        double outputCollection = neuronArray[neuronIndex].getOutput(temporalWeights); 
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

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        double outputCollection = neuronArray[neuronIndex].getLastExit(); 
        printf("Validating getLastExit, the element %i == %f \n", neuronIndex, outputCollection);
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
    double sigma ;
    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        switch (neuronIndex){
        case 0:
            sigma = neuronArray[neuronIndex].lastNeuronSigma(0.15); 
            printf("Validating sigma  %f \n", sigma);
            assert( sigma > -0.01 && sigma < 0.01);
            break;
        case 1:
             sigma = neuronArray[neuronIndex].lastNeuronSigma(0.708); 
            printf("Validating sigma  %f \n", sigma);
            assert( sigma > -0.01 && sigma < 0.01);
            break;
        case 2:
             sigma = neuronArray[neuronIndex].lastNeuronSigma(0.908);
            printf("Validating sigma  %f \n", sigma); 
            assert( sigma > -0.01 && sigma < 0.01);
            break;
        default:
            break;
        }
    }

    for(int neuronIndex = 0 ;neuronIndex < neuronAmount;neuronIndex++ ){
        switch (neuronIndex){
        case 0:
            sigma = neuronArray[neuronIndex].currentNeuronSigma(0.15); 
            printf("Validating currentNeuronSigma  %f \n", sigma);
            assert( sigma > 0.14 && sigma < 0.16);
            break;
        case 1:
             sigma = neuronArray[neuronIndex].currentNeuronSigma(0.708); 
            printf("Validating currentNeuronSigma  %f \n", sigma);
            assert( sigma > 0.13 && sigma < 0.15);
            break;
        case 2:
             sigma = neuronArray[neuronIndex].currentNeuronSigma(0.908);
            printf("Validating currentNeuronSigma  %f \n", sigma); 
            assert( sigma > 0.02 && sigma < 0.05);
            break;
        default:
            break;
        }
    }

    delete [] inputs;
    delete [] weights;
    delete [] synapses;
    delete [] neuronArray; //invoke the destructor !!
    return 0; 
} 
