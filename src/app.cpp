#include "app.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "world/world.hpp"
#include "bot/bot.hpp"
#include "graphics.hpp"

App* App::self = nullptr;

App::App(const std::string& path) : path {path} {

	window = new sf::RenderWindow(sf::VideoMode(1280, 960), "cyber biology");

	font = new sf::Font();
	font->loadFromFile(path + "font.ttf");

	graphics = new Graphics(window, font);

	world = new World;

	std::cout << "application was created" << std::endl;
}
int App::Init(const std::string& path) {
	if (self)
		return 1;

	self = new App(path);
	return 0;
}
App* App::get_self() {
	return self;
}

App::~App() {
	delete window;
	delete world;
}

int App::run() {

	int min_milisec_delay = 20;

	bool run = true;
	while (run) 
	{
		if (!window->isOpen()) // end programm if user close the window 
			return 0;

		auto t1 = std::chrono::high_resolution_clock::now();

		handle_events();
		graphics->set_text(
			"selected cell: " + std::to_string(selected_cell.x) + 
			" " + std::to_string(selected_cell.y)+
			"\nselected snake id: " + std::to_string(selected_snake));
		
		// обновление мира
		world->update();

		graphics->render_world(world, Vec2(0), world->get_size(), Vec2(0));
		graphics->display();

		// настройка фпс
		auto t2 = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<double>(t2 - t1).count();
		window->setTitle(std::to_string(1 / delta));

		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	return 0;
}

void App::handle_events() {
	mouse_position = Vec2(sf::Mouse::getPosition(*window).x,
		sf::Mouse::getPosition(*window).y);
	selected_cell = mouse_position / cell_size;

	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				snake_fragment* p = dynamic_cast<snake_fragment*>(world->get_cell_p(selected_cell));
				if (p)
					selected_snake = p->host_ptr->get_id();
			}
		}
	}
}