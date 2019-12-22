main: neuron.o layer.o connector.o
	g++ -o exe connector.o layer.o neuron.o main.cpp

connector.o: neuron.o layer.o connector.h connector.cpp
	g++ -c  neuron.o layer.o connector.cpp

neuron.o: neuron.h neuron.cpp 
	g++ -c neuron.cpp

layer.o: neuron.o layer.h layer.cpp
	g++ -c neuron.o layer.cpp

clean:
	rm *.o
	rm exe

