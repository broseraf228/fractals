#pragma once

#include "neuron_network_I.hpp"
#include <vector>
#include "../../extends/include/uMtrxF.hpp"

class NNSimplePerceptron : public NeuronNetworkI {

private:

	std::vector<uMtrxF> weights;
	std::vector<uVecF> layers;

	void clear_and_resize();

public:
	NNSimplePerceptron(const std::vector<uMtrxF> & weights);
	NNSimplePerceptron(const std::initializer_list<uMtrxF>& weights);

	const uVecF& getOutput() const;
	void setInput(const uVecF&);
	void forward();
};