#pragma once

#include <SFML/Graphics.hpp>

#include "../extends/include/vec2i.hpp"
#include <string>

class World;

class Graphics {
private:
	std::string path;
	sf::RenderWindow* window;

	sf::Font* font;

	// interface components
	sf::Text text_info;

	// вертексы для отрисовки мира
	sf::VertexArray world_va;
	// размер одной клетки в пикселях
	int cell_size = 12;

public:
	Graphics(sf::RenderWindow* window, sf::Font* font);

	void render_world(World* world, Vec2 start, Vec2 size, Vec2 offset );
	void set_text(const std::string& s);

	void display();
};