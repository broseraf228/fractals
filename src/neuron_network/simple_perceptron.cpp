#include "simple_perceptron.hpp"

#include <math.h>

NNSimplePerceptron::NNSimplePerceptron(const std::vector<uMtrxF>& weights) : NeuronNetworkI() {

	for (int i = 0; i < weights.size() - 1; i++)
		if (weights[i].gsy() + 1 != weights[i + 1].gsx())
			throw("try to create neuron networc with mistmatches size of weights");

	this->weights = weights;

	layers.resize(weights.size() + 1);
	clear_and_resize();
}	
NNSimplePerceptron::NNSimplePerceptron(const std::initializer_list<uMtrxF>& weightsIN) : NeuronNetworkI() {

	this->weights = weightsIN;

	for (int i = 0; i < weights.size() - 1; i++)
		if (weights[i].gsy() + 1 != weights[i + 1].gsx())
			throw("try to create neuron network with mistmatches size of weights");

	layers.resize(weights.size() + 1);
	clear_and_resize();
}

const uVecF& NNSimplePerceptron::getOutput() const {
	return layers.back();
}


void NNSimplePerceptron::setInput(const uVecF& v) {
	layers[0] = v;
}

void NNSimplePerceptron::forward() {

	for (int i = 0; i < weights.size(); i++) {
		layers[i].apply_function(&tanh, 1);
		uVecF::mulOnuMtrxF(weights[i], &(layers[i]), &(layers[i + 1]), 1);
	}
	layers[layers.size()-1].apply_function(&tanh, 1);
}

void NNSimplePerceptron::clear_and_resize() {
	for (int i = 0; i < weights.size(); i++)
		layers[i] = uVecF(weights[i].gsx(), 0);
	layers.back() = uVecF(weights.back().gsy() + 1, 0);

	for (int i = 0; i < layers.size(); i++)
		layers[i][0] = 1;
}