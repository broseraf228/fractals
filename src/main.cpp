#include "app.hpp"

#include "math/vec.hpp"
#include "math/mtrx.hpp"
#include "nueron_network/neuron_network.hpp"

int main()
{
	srand(NULL);

	uMtrx mn1 = uMtrx::get_random(3, 2);
	uMtrx mn2 = uMtrx::get_random(3, 2);
	NeuralNetwork nNew{ mn1, mn2};
	mn1.print();
	mn2.print();


	nNew.set_input(uVec(3, 1));
	nNew.direct_distribution();
	nNew.get_output().print();
	
	//App::Init("ghf");
	//App* app = App::get_self();

	//return app->run();
}