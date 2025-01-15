#pragma once

#include <initializer_list>
#include <vector>

#include "../math/mtrx.hpp"
#include "../math/vec.hpp"

namespace ActivationFunctions {
	float arctg(float x);
	float tanh(float x);
	float relu(float x);

	float logistic(float x);
}

class NeuralNetwork {
public:
	NeuralNetwork(const std::initializer_list<uMtrx>& weights);
	NeuralNetwork(const std::vector<uMtrx>& weights);

	// WARNING !!! MEMORY LEAK
	NeuralNetwork* clone();
	// set first neuron layer
	int set_input(const uVec& vector);

	// get answer from net
	void direct_distribution();

	const uVec& get_output();

private:

	float (*act_func) (float) { ActivationFunctions::tanh};

	int layer_count{0};

	std::vector<uVec> neural_values;

	// do not forgot, neural_weights.sx = neuron in left layer + 1
	// neural_weights[0][n] - weights of bias neuron
	std::vector<uMtrx> neural_weights;

	void create_neural_values();
};