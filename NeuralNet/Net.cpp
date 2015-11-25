#include "Net.h"


int main(){
	//Specifiy how many neurons belong in each layer in the topology vector
	std::vector<unsigned> topology;
	Net myNet(topology);

	//Responsible for obtaining the vector values of inputValues and feeding them into the neuron
	std::vector<double> inputValues;
	myNet.feedForward(inputValues);
	
	std::vector<double> targetValues;
	myNet.backProp(targetValues);
	
	std::vector<double> resultValues;
	myNet.getResults(resultValues);
}