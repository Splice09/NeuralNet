#include "Neuron.h"
#include <cstdlib>

//Neuron Constructor
Neuron::Neuron(unsigned numOutputs){
	//Here we are making a loop to add a Connection to the end of the outputWeight vector
	//c stands for connections
	for (unsigned c = 0; c < numOutputs; ++c){
		m_outputWeights.push_back(Connection());
		//assign a random weight to the weight stored in connection
		m_outputWeights.back().weight = randomWeight();
	}
}

void Neuron::feedForward(const Layer &previousLayer){
	double sum = 0.0;
}

double Neuron::randomWeight(void){
	return  std::rand() / double(RAND_MAX);
}


/*
	Setter and Getter methods for Neuron output values
*/
void Neuron::setOutputValue(double value){
	m_outputValue = value;
}

double Neuron::getOutputValue(void){
	return m_outputValue;
}