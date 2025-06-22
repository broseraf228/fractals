#pragma once

#include <vector>
#include <list>
#include "../../extends/include/list.hpp"
#include "../../extends/include/vec2i.hpp"

class Cell_I;
class Snake;


class World {
public:
	World();

	bool is_update{ 0 };

	void update();

	// return link to cell ptr
	Cell_I* get_cell_p(const Vec2& position);
	Cell_I* get_cell_p(int x, int y);
	int set_cell_p(const Vec2& position, Cell_I* value);
	int set_cell_p(int x, int y, Cell_I* value);

	const Vec2& get_size() const;
	int get_step();

	friend class App;
private:
	 
	unsigned int step{ 0 };

	Vec2 size{64, 48};

	std::vector<std::vector<Cell_I*>> map;
	void generate_maps(); // resize and clear the maps

	cir_doub_elem<Snake*> snakes_list{ nullptr };
};