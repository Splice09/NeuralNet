#include "Neuron.h"
#include <cstdlib>


/*
	Constructor
*/
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

//========================================================================================
//	PUBLIC FUNCTIONS
//========================================================================================
/*
====================================================================================
	Runs calculates the weight of the input data and then runs the input through the
	internal function to find output value.
====================================================================================
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
====================================================================================
	Transfer function -- using a hyperbolic tangent function
====================================================================================
*/
double Neuron::transferFunction(double x){
	// tanh - output range [-1.0 .. 1.0]
	return tanh(x);
}

/*
====================================================================================
	Derivative of transfer function
====================================================================================
*/
double Neuron::transferFunctionDerivative(double x){
	//tanh derivative approximation
	return 1.0 - x * x;
}

/*
====================================================================================
	Look at the difference between the target value that it's supposed to have and the value it does have
	and multiply that by the derivative of that output value.
====================================================================================
*/
void Neuron::calcOutputGradients(double targetVal){
	double delta = targetVal - m_outputValue;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputValue);
}

/*
====================================================================================
	Similar to the output gradients calculation except it's output value is
	the sum of the derivatives of the weights of the next layer.
====================================================================================
*/
void Neuron::calcHiddenGradients (const Layer &nextLayer){
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputValue);
}

/*
====================================================================================
	Loop through the neurons in the previous layer and get the connection weights to the current layer
	and update the connection weights.
====================================================================================
*/
void Neuron::updateInputWeights(Layer & previousLayer){
	for (unsigned n = 0; n < previousLayer.size(); ++n){
		Neuron &neuron = previousLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight = 
			// Individual input, magnified by the gradient and train rate:
			eta
			* neuron.getOutputValue()
			* m_gradient
			// Also add momentum = a fraction of the previous delta weight
			+ alpha
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;

	}
}

//========================================================================================
//	PRIVATE FUNCTIONS
//========================================================================================

/*
====================================================================================
	Sum our contributions of the errors at the nodes we feed in the next layer
====================================================================================
*/
double Neuron::sumDOW(const Layer &nextLayer) const{
	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; ++n){
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

/*
====================================================================================
	Random weight generator for connection weights
====================================================================================
*/
double Neuron::randomWeight(void){
	return  std::rand() / double(RAND_MAX);
}


/*
====================================================================================
	Setter and Getter methods for Neuron output values
====================================================================================
*/
void Neuron::setOutputValue(double value){
	m_outputValue = value;
}

double Neuron::getOutputValue(void) const{
	return m_outputValue;
}

