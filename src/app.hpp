#pragma once

#include <SFML/Graphics.hpp>

// основной класс приложени€
class App { 
	// SINGLETON
private: 
	// указатель на единственный экземпл€р этого класса
	static App* self;
public:
	//создать единственный экземпл€р класса
	static int Init(char* path);
	// получить единственный экземпл€р класса этого обьекта
	static App* get_self();


	// OTHER
private:
	// путь до папки с исполн€емым файлом
	char* path; 
	// здесь создаютс€ все основные системы 
	App(char* path);

	// GRAPHICS

	// окно дл€ отрисовки
	sf::RenderWindow* window;

	// World

public:
	// запуск приложени€
	int run(); 
};