#pragma once

#include "../math/vec.hpp"
#include <vector>
#include <list>

#define MAX_SNAKE_LENGHT 30

class World_Cell_I;
class Organic;

class World;

struct Snake {
	// fragment of snake
	struct snake_fragment{
		Vec2 position;
	};
	snake_fragment* fragments{nullptr};
	int lenght{0};

	// world ptr
	World* world{nullptr};

	// initialisate the snake and add his to map
	Snake(World* world, const Vec2& position);

	Vec2 direction{0, 1};

	void move();

	void add_to_map();

};


class World {
public:
	World();

	bool is_update{ 0 };
	void update();

	// return link to cell ptr
	World_Cell_I* & get_cell_l(const Vec2&);

	const Vec2& get_size();
	int get_step();

private:
	 
	unsigned int step{ 0 };

	Vec2 size{100, 100};

	std::vector<std::vector<World_Cell_I*>> map;
	std::vector<std::vector<World_Cell_I*>> blocks_map;
	void generate_maps(); // resize and clear the maps

	std::list<Snake> snakes;
};