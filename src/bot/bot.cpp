#include "bot.hpp"

#include "../world/world.hpp"
#include <SFML/Graphics.hpp>

#include "../neuron_network/simple_perceptron.hpp"

Cell_I::Cell_I() {

};
const sf::Color& wall::get_color() const {
	return sf::Color(30, 30, 30);
}


snake_fragment::snake_fragment(const Vec2& pos, Snake* host_ptr)  : position{ pos }, host_ptr{host_ptr} {

}
const sf::Color& snake_fragment::get_color() const{
	return sf::Color(50,150,50);
}

//////////////////////////////////////////////////////////

unsigned int Snake::id_counter = 0;

Snake::Snake(World* world, const Vec2& position) : world{ world } {

	// умереть, если на месте появления есть что-то
	if (world->get_cell_p(position) != nullptr){
		return;
	}

	id_counter++;
	id = id_counter;

	// официально ожить
	alive = 1;

	// выделить память под фрагменты
	fragments = new snake_fragment[MAX_SNAKE_LENGHT];

	// добавить первый фрагмент
	lenght++;
	fragments[lenght-1] = snake_fragment(position, this);
	// записать первый фрагмент на карту
	world->set_cell_p(position.x, position.y, &fragments[0]);
}

void Snake::generate_brain() {
	int input_size = (viev_distance * 2 + 1) * (viev_distance * 2 + 1) + 1 + 3;

	brain = new NNSimplePerceptron{ uMtrxF::get_random(input_size, 8), uMtrxF::get_random(9, 8), uMtrxF::get_random(9, 6) };
}
void Snake::put_data_in_brain() {
	int viev_size = (viev_distance * 2 + 1) * (viev_distance * 2 + 1);
	uVecF inp(viev_size + 1 + 3, 0);

	int p = 0; Cell_I* c;
	for (int x = -viev_distance; x <= viev_distance; x++)
		for (int y = -viev_distance; y <= viev_distance; y++) {
			c = world->get_cell_p(fragments[0].position.x + x, fragments[0].position.y + y);
			if (c == nullptr)
				inp[p] = 0;
			else
				inp[p] = c->get_color().r + c->get_color().g;
			p++;
		}

	inp[viev_size] = direction;

	inp[viev_size + 1] = brain->getOutput().at(3) * -100;
	inp[viev_size + 2] = brain->getOutput().at(4) * -100;
	inp[viev_size + 3] = brain->getOutput().at(5) * -100;
	
	brain->setInput(inp);
}

void Snake::update() {
	
	put_data_in_brain();
	brain->forward();
	float doing = brain->getOutput().at(1);

	doing = (doing+1) * 2;

	switch ((int)round(doing)) {
	case 0:
		break;
	case 1:
		move();
		break;
	case 2:
		direction++;
		break;
	case 3:
		((direction - 1) + 8)%8;
		break;
	case 4:
		//add_fragment();
		break;
	}
}

void Snake::add_new_snake_prev(Snake* snake){
	if (!snake)
		return;

	list_pointer->emplace_prev(snake);
	list_pointer->prev->value->list_pointer = list_pointer->prev;
}
int Snake::create_child() {
	if (lenght <= 1)
		return 1;

	Snake* child = new Snake(world, fragments[lenght - 1].position);
	remove_fragment();
	child->direction = direction * -1;
	
	add_new_snake_prev(child);

	return 0;
}

void Snake::add_fragment(){
	if (lenght >= MAX_SNAKE_LENGHT)
		return;
	if (world->get_cell_p(fragments[lenght-1].position - Vec2::viev_directions_4[direction]))
		return;

	fragments[lenght].position = fragments[lenght - 1].position - Vec2::viev_directions_4[direction];
	fragments[lenght].host_ptr = this;
	lenght++;

	world->set_cell_p(fragments[lenght - 1].position, &fragments[lenght - 1]);
}
void Snake::remove_fragment() {
	if (lenght <= 1) {
		return;
	}


	world->set_cell_p(fragments[lenght - 1].position, nullptr);
	//fragments[lenght - 1] = snake_fragment();
	lenght--;

}

void Snake::move() {

	// если перед лицом что то мешает
	if (world->get_cell_p(fragments[0].position + Vec2::viev_directions_4[direction])) {
		remove_fragment();
		return;
	}
		

	// удалить с карты последний фрвгмент
	world->set_cell_p(fragments[lenght - 1].position, nullptr);

	// сдвинуь все фрагменты кроме головы
	for (int i = lenght - 1; i > 0; i--)
		fragments[i].position = fragments[i - 1].position;

	

	// сдвинуть голову по направлению взгляда
	fragments[0].position += Vec2::viev_directions_4[direction];
	// добавить на карту сдвинутую голову
	world->set_cell_p(fragments[0].position, fragments);
}

unsigned int Snake::get_id() const{
	return id;
}