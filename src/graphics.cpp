#include "graphics.hpp"

Graphics::Graphics(int x, int y){
	
	//text_info.setFont(*font);
	//text_info.setPosition(1000, 10);
	//text_info.setCharacterSize(16);
	//text_info.setFillColor(sf::Color::Red);
	//text_info.setString("1452345");

	window = new sf::RenderWindow(sf::VideoMode(x, y), "fractals");

	fractal_va.setPrimitiveType(sf::Points);
	fractal_va.resize(window->getSize().x * window->getSize().y);

	for(int y = 0; y < window->getSize().y; y++)
		for (int x = 0; x < window->getSize().x; x++) {
			fractal_va[window->getSize().x * y + x].position.x = x;
			fractal_va[window->getSize().x * y + x].position.y = y;
		}

	sound_va.setPrimitiveType(sf::Lines);
	sound_va.resize(sound_va_size);
	for (int i = 0; i < sound_va_size; i++) {
		fractal_va[i].color = sf::Color(255 / sound_va_size * i);
	}
	clear_line_fragment();
}

void Graphics::draw_pixel(int x, int y, const sf::Color& color){
	fractal_va[window->getSize().x * y + x].color = color;
}

void Graphics::set_text(const std::string& s){
	//text_info.setString(s);
}

void Graphics::display(){
	//window->draw(text_info);
	window->draw(fractal_va);
	window->draw(sound_va);
	window->display();
	window->clear();
}

void Graphics::add_line_fragment(int x, int y) {
	for (int i = 0; i < sound_va_size-1; i++) {
		sound_va[i] = sound_va[i + 1];
	}

	sound_va[sound_va_size-1].position.x = x;
	sound_va[sound_va_size-1].position.y = y;
	sound_va[sound_va_size - 1].color.a = 255;
}
void Graphics::clear_line_fragment(){
	for (int i = 0; i < sound_va_size; i++) {
		//sound_va[i].position.x = window->getSize().x * 0.5;
		//sound_va[i].position.y = window->getSize().y * 0.5;
		sound_va[i].color.a = 0;
	}
}