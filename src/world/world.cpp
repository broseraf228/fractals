#include "world.hpp"


Snake::Snake(World* world, const Vec2& position) : world{world} {

	fragments = new snake_fragment[MAX_SNAKE_LENGHT];
	fragments[lenght++] = snake_fragment();
	fragments[lenght].position = position;
}


void Snake::move() {
	
}

//########################
World::World(){}

void World::update() {
	step++;
}

World_Cell_I* & World::get_cell_l(const Vec2& v) {
	int x, y;
	x = v.x; y = v.y;

	if (v.y < 0)
		y = 0;

	if (v.y > size.y)
		y = size.y - 1;

	if (x < 0)
		x += size.x;

	if (x > size.x)
		x -= size.x;

	return map[x][y];
}

const Vec2& World::get_size() {
	return size;
}
int World::get_step() {
	return step;
}

void World::generate_maps() {
	// CLEAR AND RESIZE
	map.clear();
	map.resize(size.x);
	blocks_map.clear();
	blocks_map.resize(size.x);

	for (int x = 0; x < size.x; x++)
	{
		map[x].clear();
		map[x].resize(size.y);
		blocks_map[x].clear();
		blocks_map[x].resize(size.y);
	}
}