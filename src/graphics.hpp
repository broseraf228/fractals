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
	sf::VertexArray fractal_va;
	int sound_va_size{20};
	sf::VertexArray sound_va;

public:
	//главное окно для отрисовки всего
	sf::RenderWindow* window{nullptr};

	Graphics(int x, int y);

	//отрисовать 1 пиксель
	void draw_pixel(int x, int y, const sf::Color& color);
	void set_text(const std::string& s);

	void add_line_fragment(int x, int y);
	void clear_line_fragment();

	//очистить экран, отрисовать все пиксели
	void display();
};