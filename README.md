# ANN
artificial neural network.

compile neuron
g++ -c -Wall neuron.cpp

test neuron
g++ -o exe -Wall neuronTest.cpp neuron.o

compile layer
g++ -c -Wall neuron.o layer.cpp

test layer
g++ -o exe -Wall layerTest.cpp  neuron.o layer.o

compile connector
g++ -c  neuron.o layer.o connector.cpp

test connector
Ha ha ha

