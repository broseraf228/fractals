#include "app.hpp"

#include "math/vec.hpp"
#include "math/mtrx.hpp"

int main()
{

	uVec v1(3, 1);
	v1.print();

	uMtrx m1 = uMtrx::get_random(1, 3);
	m1.print();

	uVec v2 = m1 * v1;
	v2.print();
	
	//App::Init("ghf");
	//App* app = App::get_self();

	//return app->run();
}