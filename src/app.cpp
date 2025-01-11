#include "app.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

App* App::self = nullptr;

App::App(char* path) : path {path} {

	window = new sf::RenderWindow(sf::VideoMode(200, 200), "cyber biology");
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

	// temp
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);

	int min_milisec_delay = 10;

	bool run = true;
	while (run) 
	{
		if (!window->isOpen()) // end programm if user close the window 
			return 0;

		auto t1 = std::chrono::high_resolution_clock::now();

		// event handling ( ÏÅĞÅÍÅÑÈ İÒÎ Â ÎÒÄÅËÜÍÛÉ ÊËÀÑÑ ÏÎÇÆÅ )
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		window->draw(shape);
		window->display();


		// íàñòğîéêà ôïñ
		auto t2 = std::chrono::high_resolution_clock::now();
		float delta = std::chrono::duration<double>(t2 - t1).count();
		window->setTitle(std::to_string(1 / delta));
	}
	return 0;
}