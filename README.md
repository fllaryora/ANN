# ANN
artificial neural network.

compile neuron
g++ -c -Wall neuron.cpp

test neuron
g++ -o exe -Wall neuronTest.cpp neuron.o

compile layer
g++ -c -Wall neuron.o layer.cpp
