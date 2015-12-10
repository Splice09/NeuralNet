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
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients (const Layer &nextLayer);
	void updateInputWeights(Layer & previousLayer);


private:
	static double randomWeight(void);
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	
	/*
		(eta) - overall net learning rate
			0.0 - slow learner
			0.2 - medium learner
			1.0 - reckless learner

		(alpha) - momentum
			0.0 - no momentum
			0.5 - moderate momentum
	*/
	static double eta;	// [0.0 .. 1.0] overall net training rate
	static double alpha; // [0.0 .. n] multiplier of last weight change (momentum)

	double sumDOW(const Layer &nextLayer) const;
	double m_outputValue;
	double m_gradient;
	unsigned m_myIndex;
	std::vector<Connection> m_outputWeights;

};

