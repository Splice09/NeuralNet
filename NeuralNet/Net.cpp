#include "Net.h"


Net::Net(const std::vector<unsigned> &topology){
	unsigned numLayers = topology.size();
	//add layers
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
		m_layers.push_back(Layer());
		//add neurons
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){
			//gets the last element in the container then pushes a neuron into that layer
			m_layers.back().push_back(Neuron());
			std::cout << "Made a Neuron!" << std::endl;
		}
	}
}

void Net::feedForward(const std::vector<double> &inputValues){};
void Net::backProp(const std::vector<double> &targetValues){};
void Net::getResults(std::vector<double> &resultValues) const {};

int main(){
	//Specifiy how many neurons belong in each layer in the topology vector
	std::vector<unsigned> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);
	Net myNet(topology);

	//Responsible for obtaining the vector values of inputValues and feeding them into the neuron
	std::vector<double> inputValues;
	myNet.feedForward(inputValues);
	
	std::vector<double> targetValues;
	myNet.backProp(targetValues);
	
	std::vector<double> resultValues;
	myNet.getResults(resultValues);
}