#pragma once

#include "../extends/include/vec2i.hpp"
#include <SFML/Graphics.hpp>

class World;
class Graphics;

// основной класс приложени€
class App { 
	// SINGLETON
private: 
	// указатель на единственный экземпл€р этого класса
	static App* self;
public:
	//создать единственный экземпл€р класса
	static int Init(const std::string& path);
	// получить единственный экземпл€р класса этого обьекта
	static App* get_self();

	~App();

	// OTHER
private:
	// путь до папки с исполн€емым файлом
	std::string path;
	// здесь создаютс€ все основные системы 
	App(const std::string& path);

	Graphics* graphics{nullptr};

	sf::Font* font;

	// окно дл€ отрисовки
	sf::RenderWindow* window;

	int cell_size = 12;

	void handle_events();

	// World
	World* world;

	// режим ручного управлени€
	bool is_manual_operation{ 0 };
	// id выбранной змейки
	int selected_snake{0};
	// координаты клетки на которую нацелена мышка
	Vec2 mouse_position{ 0,0 };
	// координаты клетки на которую нацелена мышка
	Vec2 selected_cell{ 0,0 };
public:
	// запуск приложени€
	int run(); 
};