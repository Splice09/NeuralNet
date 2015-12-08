#include "Neuron.h"
#include <cstdlib>

//Neuron Constructor
Neuron::Neuron(unsigned numOutputs, unsigned myIndex){
	//Here we are making a loop to add a Connection to the end of the outputWeight vector
	//c stands for connections
	for (unsigned c = 0; c < numOutputs; ++c){
		m_outputWeights.push_back(Connection());
		//assign a random weight to the weight stored in connection
		m_outputWeights.back().weight = randomWeight();
	}

	m_myIndex = myIndex;
}

/*
	Computs the math within the neuron
*/
void Neuron::feedForward(const Layer &previousLayer){
	double sum = 0.0;
	
	// loop through and sum the product of the output and connection weight of each neuron from the previous layer
	//  - include the bias node from the previous layer
	for (unsigned n = 0; n < previousLayer.size(); ++n){
		sum += previousLayer[n].getOutputValue() *
			previousLayer[n].m_outputWeights[m_myIndex].weight;
	}

	//apply the activation function (transfer function) to shape neuron output
	m_outputValue = Neuron::transferFunction(sum);
}

/*
	Transfer function -- using a hyperbolic tangent function
*/
double Neuron::transferFunction(double x){
	// tanh - output range [-1.0 .. 1.0]
	return tanh(x);
}

/*
	Derivative of transfer function
*/
double Neuron::transferFunctionDerivative(double x){
	//tanh derivative approximation
	return 1.0 - x * x;
}

/*
	Random weight generator
*/
double Neuron::randomWeight(void){
	return  std::rand() / double(RAND_MAX);
}


/*
	Setter and Getter methods for Neuron output values
*/
void Neuron::setOutputValue(double value){
	m_outputValue = value;
}

double Neuron::getOutputValue(void) const{
	return m_outputValue;
}