#pragma once
#include <vector>

typedef std::vector<Neuron> Layer;

struct Connection{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	//pass in the number of neurons in the next layer so we know how many output connections to make
	Neuron(unsigned numOutputs);
	static double randomWeight(void);
	void setOutputValue(double value);
	double getOutputValue(void);
	void feedForward(const Layer &previousLayer);


private:
	double m_outputValue;
	std::vector<Connection> m_outputWeights;
};

