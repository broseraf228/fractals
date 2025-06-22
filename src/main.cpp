#include "app.hpp"

#include "../extends/include/vec2i.hpp"
#include "../extends/include/uMtrxF.hpp"
#include "neuron_network/simple_perceptron.hpp"

#include <iostream>

/*
* ���������
* �������� ������� ���������� �������
* �������� ������ ������ ����������
*/

int main(int argc, char* argv[])
{
	std::string path = argv[0];
	for (int i = path.size() - 1; path[i] != '\\'; i--)
		path.erase(path.end() - 1, path.end());

	srand(NULL);
	
	App::Init(path);
	App* app = App::get_self();

	return app->run();
}