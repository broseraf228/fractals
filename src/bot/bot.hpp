#pragma once

#include "../../extends/include/list.hpp"
#include "../../extends/include/vec2i.hpp"

namespace sf {
	class Color;
}
class World;
class Snake;
class NNSimplePerceptron;

#define MAX_SNAKE_LENGHT 30 

class Cell_I {
public:
	Cell_I();
	virtual const sf::Color& get_color() const = 0;

	enum CellType
	{block, bot};
};

class wall : public Cell_I {
public:

	virtual const sf::Color& get_color() const;
};



// fragment of snake
class snake_fragment : public Cell_I {
public:
	snake_fragment(const Vec2& pos = 0, Snake* host_ptr = nullptr);
	Vec2 position;
	Snake* host_ptr;

	virtual const sf::Color& get_color() const;
};
// SNAKE
class Snake {
private:

	// array of snake fragments
	snake_fragment* fragments{ nullptr };
	int lenght{ 0 };
	void add_fragment();
	void remove_fragment();

	// 
	void add_new_snake_prev(Snake*);

	int create_child();

	// world ptr
	World* world{ nullptr };

	int direction{ 0 };

	// id for snakes
	static unsigned int id_counter;
	unsigned int id{0};

	// Snake Brain
	NNSimplePerceptron* brain{ nullptr };
	void generate_brain();
	void put_data_in_brain();
	int viev_distance{ 2 };
	
public:
	cir_doub_elem<Snake*>* list_pointer{ nullptr };
	bool alive{ 0 };

	// initialisate the snake and add his to map
	Snake(World* world, const Vec2& position);

	unsigned int get_id() const;

	void update();

	void move();

	void death();

	friend class World;
};