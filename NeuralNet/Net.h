#pragma once
#include <vector>
class Net
{
public:
	Net(const std::vector<unsigned> &topology);
	void feedForward(const std::vector<double> &inputValues);
	void backProp(const std::vector<double> &targetValues);
	void getResults(std::vector<double> &resultValues) const;
	int main();

private:
};




