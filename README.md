# ANN
artificial neural network.

The aim of this project is teaching what is a Multilayer Neuronal Network (with supervised learning).

The magick is: the set of training data could be different from the tests.

By now I do not know anything about topology. But there are some papers since 2016. (I leant ANN's in 2011).

## Implementation features.

### Neuron.

The basic unit of the neural network is the neuron:
 * It will ignore neither the layer to which it belongs nor its position in it.
 * Every neuron in an ANN consists of:
 * 1 to n entries called inputs.
 * This entry would correspond to the axon of the previous layer or to the entry of the ANN.
* Each entry is associated with a weight called a synapse.
* Each entry is multiplied with its synapse, this result is called dentrite.
* Optionally there is an extra entry. It is a fixed input (+1 or -1) which is not associated with a synapse, like every entry it is multiplied with its synapse, and the result is called bias.
* When all the dentrites and the bias are added together it is called vk.
* Every neuron has one activation function.
* Every neuron has one sigma value.

#### activation function
Neuron class has implemented only 3 types: sigmoid (also known as logistic),
 Hyperbolic tangent and lineal.
 * The imput of the activation function is the vk
* Every neuron has only 1 wayout called output or axon that is the output of the activation function.
* The output will be taken as input for the next layout or output of the system.

#### Sigma Value
This class is meant to be a neuron that can learn.
Although this class is not responsible for learning.
Another class will set the sigma value by passing a summation value and subsequently the correct synapses.

#### Output calculus.

<Writing...>

### Layer.
A Neuron Layer represent a layer with n neurons. 
 The class does not know if it is an input layer, a hidden layer or an output layer.

### Connector (Scheduler of the propagation values of the ANN).
 The Connector class has 2 responsabilities.
 
#### the propagation values of the ANN
Everything starts by applying a list of values to the network input, this reaches the first layer.
Each neuron in the first layer will calculate its unique output.
The values in the first layer will be propagated to the next layer.
Each neuron in the next layer will calculate its unique output.
The values in that layer will propagate to the next layer and so on.
AS far as  generate an output that will have as many values as the last layer of neurons.

#### Learning calculus.

<Writing...>
