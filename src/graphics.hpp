#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class World;

class Graphics {
private:
	std::string path;

	//шрифты
	sf::Font* font;

	// interface components
	sf::Text text_info;

	// вертексы для отрисовки мира
	sf::VertexArray screen_va;

public:
	//главное окно для отрисовки всего
	sf::RenderWindow* window{nullptr};

	Graphics(int x, int y);

	//отрисовать 1 пиксель
	void draw_pixel(int x, int y, const sf::Color& color);
	void set_text(const std::string& s);

	//очистить экран, отрисовать все пиксели
	void display();
};