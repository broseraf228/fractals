#include "world.hpp"

#include "../bot/bot.hpp"

//########################
World::World(){
	generate_maps();
	// добавление первой змейки
	snakes_list.emplace_next(new Snake(this, Vec2(10, 10)));
	snakes_list.next->value->list_pointer = snakes_list.next;
	snakes_list.next->value->generate_brain();
}

void World::update() {
	step++;

	cir_doub_elem<Snake*>* current_snake = snakes_list.next;
	while (current_snake->value) {
		current_snake->value->update();

		current_snake = current_snake->next;

		// kill snake if is death
		if (!current_snake->prev->value->alive) {
			delete current_snake->prev->value;
			current_snake->prev->remove();
		}
	}
}

Cell_I* World::get_cell_p(int x, int y) {
	if (y < 0)
		y = 0;

	if (y >= size.y)
		y = size.y - 1;

	if (x < 0)
		x += size.x;

	if (x >= size.x)
		x -= size.x;

	return map[x][y];
}
Cell_I* World::get_cell_p(const Vec2& pos) {
	int x = pos.x, y = pos.y;
	return get_cell_p(x, y);
}
int World::set_cell_p(int x, int y, Cell_I* value) {
	if (y < 0)
		y = 0;

	if (y > size.y)
		y = size.y - 1;

	if (x < 0)
		x += size.x;

	if (x > size.x)
		x -= size.x;

	map[x][y] = value;
	return 0;
}
int World::set_cell_p(const Vec2& pos, Cell_I* value) {
	int x = pos.x, y = pos.y;
	if (y < 0)
		y = 0;

	if (y > size.y)
		y = size.y - 1;

	if (x < 0)
		x += size.x;

	if (x > size.x)
		x -= size.x;

	map[x][y] = value;
	return 0;
}

const Vec2& World::get_size() const {
	return size;
}
int World::get_step() {
	return step;
}

void World::generate_maps() {
	// CLEAR AND RESIZE
	map.clear();
	map.resize(size.x);

	for (int x = 0; x < size.x; x++)
	{
		map[x].clear();
		map[x].resize(size.y);
	}

	for (int x = 0; x < size.x; x++) {
		map[x][0] = new wall();
		map[x][size.y-1] = new wall();
	}
	for (int y = 0; y < size.y; y++) {
		map[0][y] = new wall();
		map[size.x-1][y] = new wall();
	}
}