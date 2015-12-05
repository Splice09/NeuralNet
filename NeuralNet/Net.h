#pragma once
#include <vector>
#include <iostream>
#include "Neuron.h"


//class Neuron {};
typedef std::vector<Neuron> Layer;

class Net
{

public:
	Net(const std::vector<unsigned> &topology);
	void feedForward(const std::vector<double> &inputValues);
	void backProp(const std::vector<double> &targetValues);
	void getResults(std::vector<double> &resultValues) const;
	int main();

private:
	std::vector<Layer> m_layers;// m_layers[layerNum][neuronNum]
};




