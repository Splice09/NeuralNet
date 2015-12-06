#include "Net.h"


Net::Net(const std::vector<unsigned> &topology){
	unsigned numLayers = topology.size();
	//add layers
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
		m_layers.push_back(Layer());
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		//add neurons -- use <= to for one additional loop to add bias neuron
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){
			//gets the last element in the container then pushes a neuron into that layer
			m_layers.back().push_back(Neuron(numOutputs));
			std::cout << "Made a Neuron!" << std::endl;
		}
	}
}
/*
	
*/
void Net::feedForward(const std::vector<double> &inputValues){
	//if the number of input values is the same as the number of neurons in the layer minus the bias neuron we're good
	assert(inputValues.size() == m_layers[0].size() - 1);

	//loop that iterates through the neurons in a layer and assigns input values
	for (unsigned i = 0; i < inputValues.size(); i++){
		m_layers[0][i].setOutputValue(inputValues[i]);
	}

	//Tell each neuron to feed forward its new input data (forward propagation)
	// - this double for loop skips the bias neuron in each layer
	for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
		Layer &previousLayer = m_layers[layerNum - 1];
		for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
			m_layers[layerNum][n].feedForward(previousLayer);
		}
	}

};
void Net::backProp(const std::vector<double> &targetValues){};
void Net::getResults(std::vector<double> &resultValues) const {};

/*
	Main Method
*/
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