main: neuron.o layer.o connector.o testlayer
	g++ -g -Wall connector.o layer.o neuron.o main.cpp -O0 -o main.exe

testneuron: neuron.o
	g++ -g -Wall neuronTest.cpp neuron.o -O0 -o neuron.exe

testlayer: neuron.o layer.o testneuron
	g++ -g -Wall layerTest.cpp  neuron.o layer.o -O0 -o layer.exe

connector: neuron.o layer.o connector.h connector.cpp
	g++ -c -g neuron.o -Wall layer.o connector.cpp -O0

neuron: neuron.h neuron.cpp 
	g++ -c -g -Wall neuron.cpp -O0

layer: neuron.o layer.h layer.cpp
	g++ -c -g -Wall neuron.o layer.cpp -O0

clean:
	rm *.o
	rm *.exe

