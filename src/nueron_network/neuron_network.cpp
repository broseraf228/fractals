#include "neuron_network.hpp"

#include <cmath>


float ActivationFunctions::arctg(float x) {
	return arctg(x);
}
float ActivationFunctions::tanh(float x) {
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}
//---------
NeuralNetwork::NeuralNetwork(const std::initializer_list<uMtrx>& weights){
	neural_weights = std::vector<uMtrx>{ weights };
	layer_count = neural_weights.size() + 1;
	create_neural_values();
}
NeuralNetwork::NeuralNetwork(const std::vector<uMtrx>& weights) {
	neural_weights = std::vector<uMtrx>{ weights };
	layer_count = neural_weights.size() + 1;
	create_neural_values();
}

NeuralNetwork* NeuralNetwork::clone(){
	return new NeuralNetwork(neural_weights);
}

void NeuralNetwork::create_neural_values()
{
	neural_values = {};
	neural_values.resize(layer_count);

	for (int i = 0; i < layer_count-1; i++) {

		neural_values[i] = uVec(neural_weights[i].gsx(), 0 );
	}
	neural_values[layer_count-1] = uVec(neural_weights[layer_count - 2].gsy() + 1, 0); // - 1 need to add space bias neuron
}

int NeuralNetwork::set_input(const uVec& vector){
	if (vector.size() != neural_values[0].size())
		return 1;

	neural_values[0] = vector;
	return 0;
}
const uVec& NeuralNetwork::get_output(){
	return neural_values[layer_count - 1];
}

void NeuralNetwork::direct_distribution() {
	for (int i = 1; i < layer_count; i++) { //

		neural_values[i][0] = 1; // set bias neuron to 1

	}
	neural_values[layer_count - 1][0] = 0;

	for (int i = 1; i < layer_count; i++) { // распростронение сигнала по слоям, с начала к концу

		// рассчер суммы со входов
		uMtrx::multiplication(neural_weights[i - 1], neural_values[i - 1], &neural_values[i], 1);

		// применение ф-ции активации
		neural_values[i].apply_function(act_func, 1);
	}
}