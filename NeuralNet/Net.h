#pragma once
class Net
{
public:
	Net(topology);
	void feedForward(inputValues);
	void backProp(inputValues);
	void getResults(resultValues) const;

private:
};

int main(){
	Net myNet(topology);

	myNet.feedForward(inputValues);
	myNet.backProp(targetValues);
	myNet.getResults(resultValues);
}


