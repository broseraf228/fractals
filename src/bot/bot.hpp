#pragma once

#include "../math/vec.hpp"
#include "../math/list.hpp"

namespace sf {
	class Color;
}
class World;

#define MAX_SNAKE_LENGHT 30 

class Cell_I {
public:
	Cell_I();
	virtual const sf::Color& get_color() const = 0;
};



// fragment of snake
class snake_fragment : public Cell_I {
public:
	snake_fragment(const Vec2& pos = 0);
	Vec2 position;

	virtual const sf::Color& get_color() const;
};
// SNAKE
class Snake {
private:

	// array of snake fragments
	snake_fragment* fragments{ nullptr };
	int lenght{ 0 };

	// world ptr
	World* world{ nullptr };

	int direction{ 0 };
	bool alive{ 0 };
public:
	cir_doub_elem<Snake*>* list_pointer{ nullptr };

	// initialisate the snake and add his to map
	Snake(World* world, const Vec2& position);

	void update();

	void move();
};