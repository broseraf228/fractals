#include "app.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "world/world.hpp"
#include "bot/bot.hpp"

App* App::self = nullptr;

App::App(char* path) : path {path} {

	window = new sf::RenderWindow(sf::VideoMode(1280, 960), "cyber biology");

	world_va.setPrimitiveType(sf::Quads);

	world = new World;

	std::cout << "application was created" << std::endl;
}
int App::Init(char* path) {
	if (self)
		return 1;

	self = new App(path);
	return 0;
}
App* App::get_self() {
	return self;
}

int App::run() {

	int min_milisec_delay = 20;

	bool run = true;
	while (run) 
	{
		if (!window->isOpen()) // end programm if user close the window 
			return 0;

		auto t1 = std::chrono::high_resolution_clock::now();

		// event handling ( ПЕРЕНЕСИ ЭТО В ОТДЕЛЬНЫЙ КЛАСС ПОЗЖЕ )
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		// обновление мира
		world->update();
		render_world();

		// И ЭТО ТОЖЕ
		window->clear();
		window->draw(world_va);
		window->display();

		// настройка фпс
		auto t2 = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<double>(t2 - t1).count();
		window->setTitle(std::to_string(1 / delta));

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}

void App::render_world(){
	world_va.clear();
	world_va.resize(world->size.x * world->size.y * 4);

	int sy = world->size.y, sx = world->size.x;

	sf::Color COL;	
	int index_offset;

	for (int x = 0; x < sx; x++) {
		for (int y = 0; y < sy; y++) {
			// нахождение места для записи вертексов
			index_offset = x * sy + y;
			index_offset *= 4;

			// поиск подходящего цвета
			if(world->get_cell_p(x, y) == nullptr){
				COL = sf::Color(40,40,40);
				goto ENDCOLDEF;
			}
			COL = world->get_cell_p(x, y)->get_color();
		ENDCOLDEF:

			world_va[index_offset].position.x = x * 7;
			world_va[index_offset].position.y = y * 7;

			world_va[index_offset + 1].position.x = x * 7 + 7;
			world_va[index_offset + 1].position.y = y * 7;

			world_va[index_offset + 2].position.x = x * 7 + 7;
			world_va[index_offset + 2].position.y = y * 7 + 7;

			world_va[index_offset + 3].position.x = x * 7;
			world_va[index_offset + 3].position.y = y * 7 + 7;

			world_va[index_offset].color = COL;
			world_va[index_offset + 1].color = COL;
			world_va[index_offset + 2].color = COL;
			world_va[index_offset + 3].color = COL;
		}
	}
}