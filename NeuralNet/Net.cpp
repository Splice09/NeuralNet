#include "Net.h"

double Neuron::eta = 0.15; // [0.0 .. 1.0] overall net training rate
double Neuron::alpha = 0.5; // [0.0 .. n] multiplier of last weight change (momentum)

/*
	Net constructor
*/
Net::Net(const std::vector<unsigned> &topology){
	unsigned numLayers = topology.size();
	//add layers
	for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
		m_layers.push_back(Layer());
		/*
			if the current layer number is the last layer of the specified topology then
			specify the number of outputs to be 0. 
			Else set number of outputs to be the number of nodes in the next layer
		*/
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1];

		//add neurons -- use <= to for one additional loop to add bias neuron
		for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum){
			//gets the last element in the container then pushes a neuron into that layer
			m_layers.back().push_back(Neuron(numOutputs, neuronNum));
			std::cout << "Made a Neuron!" << std::endl;
		}

		// Force the bias node's output value to 1.0. It's the last neuron created above
		m_layers.back().back().setOutputValue(1.0);
	}
}

/*
====================================================================================
	Iterates through the layer assigning each neuron in the layer its input data
	and then iterates through again having each neuron run its internal function 
	to feed forward its output data.
====================================================================================
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

}

/*
====================================================================================
	For the net learning
====================================================================================
*/
void Net::backProp(const std::vector<double> &targetValues){
	// Calculate overall net error (RMS or Root Mean Square Error -- of output neuron errors)
	
	// grab the last layer of the net (the output layer)
	Layer &outputLayer = m_layers.back();
	m_error = 0.0;
	//loop through neurons in the output layer (not including the bias)
	for (unsigned n = 0; n < outputLayer.size() - 1; ++n){
		double delta = targetValues[n] - outputLayer[n].getOutputValue();
		m_error += delta* delta;
	}
	m_error /= outputLayer.size() - 1; //get average error squared
	m_error += sqrt(m_error); //RMS

	// Implement a crecent average measurement:
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
			/ (m_recentAverageSmoothingFactor + 1.0);
	
	// Calculate output layer gradients
	for(unsigned n = 0; n < outputLayer.size() - 1; ++n){
		outputLayer[n].calcOutputGradients(targetValues[n]);
	}

	// Calculate gradients on hidden (bias) layers
	for(unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum){
		Layer &hiddenLayer = m_layers[layerNum];
		Layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n){
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer
	// update connection weights
	for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum){
		Layer &layer = m_layers[layerNum];
		Layer &previousLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size(); ++n){
			layer[n].updateInputWeights(previousLayer);
		}
	}
}

/*
====================================================================================
	Clears out the container that is passed to it.
	loops through the neurons in the output layer and moves their output value onto results vals
====================================================================================
*/
void Net::getResults(std::vector<double> &resultValues) const {
	resultValues.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; ++n){
		resultValues.push_back(m_layers.back()[n].getOutputValue());
	}
}

/*
====================================================================================
	Main Method -- used to specify neural net size
====================================================================================
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