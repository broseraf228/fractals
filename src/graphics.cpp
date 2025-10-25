#include "graphics.hpp"

Graphics::Graphics(int x, int y){
	
	//text_info.setFont(*font);
	//text_info.setPosition(1000, 10);
	//text_info.setCharacterSize(16);
	//text_info.setFillColor(sf::Color::Red);
	//text_info.setString("1452345");

	window = new sf::RenderWindow(sf::VideoMode(x, y), "fractals");

	screen_va.setPrimitiveType(sf::Points);
	screen_va.resize(window->getSize().x * window->getSize().y);

	for(int y = 0; y < window->getSize().y; y++)
		for (int x = 0; x < window->getSize().x; x++) {
			screen_va[window->getSize().x * y + x].position.x = x;
			screen_va[window->getSize().x * y + x].position.y = y;
		}
}

void Graphics::draw_pixel(int x, int y, const sf::Color& color){
	screen_va[window->getSize().x * y + x].color = color;
}

void Graphics::set_text(const std::string& s){
	//text_info.setString(s);
}

void Graphics::display(){
	//window->draw(text_info);
	window->draw(screen_va);
	window->display();
	window->clear();
}