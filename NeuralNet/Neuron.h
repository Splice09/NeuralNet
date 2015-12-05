#pragma once
#include <vector>

struct Connection{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	//pass in the number of neurons in the next layer so we know how many output connections to make
	Neuron(unsigned numOutputs);


private:
	double m_outputValue;
	std::vector<Connection> m_outputWeights;
};

