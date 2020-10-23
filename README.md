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
In the Neuron i: 
* Each entry x is associated with a synapse's weight w.
* Treat the bias like a fixed entry if it exists.

![equation](https://latex.codecogs.com/gif.latex?vk%20%3D%20%5Csum_%7Bj%3D1%7D%5E%7Be%7D%20%5Cleft%20%28%20w_i_j%20x_i%5Cright%20%29)

In the Neuron i:
* Every neuron has one output value caled a.
* Every neuron has one activation function which is triggered by vk.

![equation](https://latex.codecogs.com/gif.latex?a_i%20%3D%20f%28vk%29)

#### Sigma calculus.
In the Neuron i: 
Another class will set the sigma value by passing a summation value and subsequently the correct synapses.
![equation](https://latex.codecogs.com/gif.latex?%5Cdelta_i%20%3D%20summation%20f%27%28a_i%29)

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

Only the Connector knows which layer is the last layer.

##### In the last layer
The output signal is compared with the desired output and the error is calculated.
In the Neuron i:

![equation](https://latex.codecogs.com/gif.latex?sumation_i%20%3D%20expectedResult_i%20-%20outcome_i)

So:

![equation](https://latex.codecogs.com/gif.latex?%5Cdelta_i%20%3D%20%28%20expectedResult_i%20-%20outcome_i%29%20f%27%28a_i%29)

##### In the hidden layers
The error made by the intermediate neurons is calculated propagating the error backwards from the output layer to all the neurons in each hidden layer that contribute directly to the output.
Without However, the hidden layer neurons only receive a fraction of the total error, based on the contribution that each neuron has made to the output original.

In the bound of Neuron i (of the layer l ) and Neuron j (of the layer l+1 ):
* The outcome of the neuron i is the entry x of the neuron j passing throw the sinaps w.
* The contribution of the total error, is based on the sigma of neuron j and the w.

![equation](https://latex.codecogs.com/gif.latex?contribution_i%20%3D%20w_ij%5Cdelta_j)

So lets suppouse we have n neurons in the layer of the neuron j.
The summation of contribution is:

![equation](https://latex.codecogs.com/gif.latex?summation_i%20%3D%20%5Csum_%7Bj%3D0%7D%5E%7Bn-1%7D%20w_ij%5Cdelta_j)

So:

![equation](https://latex.codecogs.com/gif.latex?%5Cdelta_i%20%3D%20%28%20%5Csum_%7Bj%3D0%7D%5E%7Bn-1%7D%20w_ij%5Cdelta_j%20%29%20f%27%28a_i%29)


##### Updating the synapses in every layer

In the Neuron i, in the time t, for each w:
With a learning rate alpha
The new w  in the time t+1 will be.

![equation](https://latex.codecogs.com/gif.latex?w_{t&plus;1}&space;=&space;w_{t}&space;&plus;&space;\alpha&space;\delta_{i})

Thats all!

