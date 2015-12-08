#pragma once
#include <vector>
#include <cmath>
class Neuron;

typedef std::vector<Neuron> Layer;

struct Connection{
	double weight;
	double deltaWeight;
};

class Neuron
{
public:
	//pass in the number of neurons in the next layer so we know how many output connections to make
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputValue(double value);
	double getOutputValue(void) const;
	void feedForward(const Layer &previousLayer);


private:
	static double randomWeight(void);
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	double m_outputValue;
	std::vector<Connection> m_outputWeights;
	unsigned m_myIndex;
};

