#include "bot.hpp"

#include "../world/world.hpp"
#include <SFML/Graphics.hpp>

Cell_I::Cell_I() {

};

snake_fragment::snake_fragment(const Vec2& pos) : position{pos} {

}
const sf::Color& snake_fragment::get_color() const{
	return sf::Color(50,150,50);
}

Snake::Snake(World* world, const Vec2& position) : world{ world } {

	// умереть, если на месте появления есть что-то
	//if (world->get_cell_l(position) != nullptr){
	//	return;
	//}

	// официально ожить
	alive = 1;

	// выделить память под фрагменты
	fragments = new snake_fragment[MAX_SNAKE_LENGHT];

	// добавить первый фрагмент
	lenght++;
	fragments[0] = snake_fragment();
	fragments[0].position = position;
	// записать первый фрагмент на карту
	world->set_cell_p(position.x, position.y, &fragments[0]);
}

void Snake::update() {
	move();
}

void Snake::move() {

	// если перед лицом что то мешает
	if (world->get_cell_p(fragments[0].position + Vec2::viev_directions_4[direction]))
		return;

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