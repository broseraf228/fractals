#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#include <iostream> 
#include <windows.h> // WinApi header 

#include "graphics.hpp"
#include "sound.hpp"
#include "fractal.hpp"

#define WINDOW_X 1000
#define R_WINDOW_X 1/WINDOW_X
#define WINDOW_Y 1000
#define R_WINDOW_Y 1/WINDOW_Y

// счетчик кадров, прошедших с начала выполнения программы
int frame = 0;
// стандартное время на кадр
double fps = 60;
// дельта времени
double delta = 1/fps;

int max_iterations = 32;
// параметры положения камеры
double view_c_x = -2, view_c_y = 2;
double view_size_x = 4, view_size_y = 4;
// параметры изменеия параметров камеры
double movement_speed = 1; // screen size per frame
double viewsize_scale_speed = 1; // viewsize multiplayer per frame
// модификаторы множества мандельбротта
float mod_x = 0.28, mod_y = 0.0001, modM_x = 0, modM_y = 0;
float smod_x = 0, smod_y = 0, smodM_x = 0, smodM_y = 0;
// параметры текущей точки, которая нужна для визуализации конкретного места в множестве 
double current_point_x = 0, current_point_y = 0;
double current_start_point_x = 0, current_start_point_y = 0;

Graphics graphics(WINDOW_X, WINDOW_Y);

Sounds sounds{};

bool viewbox_input_handler(double);
void current_point_handler(double);

int main(int argc, char* argv[])
{
	std::cout << "Control settings:\n";
	std::cout << "arrows - movement\n";
	std::cout << "R Shift / R Ctrl - zoom\n";
	std::cout << "L Shift / L Ctrl - iterations per point\n\n\nLog:\n";


	Fractal fractal;
	fractal.generate_fractal(view_c_x, view_c_y, view_size_x, view_size_y, WINDOW_X, WINDOW_Y);

	while (graphics.window->isOpen())
	{

		// штука для замера времени
		auto start = std::chrono::high_resolution_clock::now();

		// проверяем все события окна которые сработали с момента последней итерации цикла
		sf::Event event;
		while (graphics.window->pollEvent(event))
		{
			// событие "закрытия": мы закрываем окно
			if (event.type == sf::Event::Closed)
				graphics.window->close();
		}

		// обработка ввода на изменение кол ва итераций
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			max_iterations++;		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			max_iterations--;
		}
		fractal.max_iterations = max_iterations;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			mod_x -= delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			mod_x += delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			mod_y -= delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			mod_y += delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			modM_x -= delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
			modM_x += delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			modM_y -= delta;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
			modM_y += delta;
		}

		

		// обработка ввода на изменение положения и зума камеры и обновление фрактала в случае необходимости
		viewbox_input_handler(delta);

		// обработка текущей отображаемой точки
		current_point_handler(delta);
		
		// положить в шейдер информацию о положинии и размерах камеры
		graphics.set_shader_params(frame, max_iterations, view_c_x, view_c_y, view_size_x, view_size_y, mod_x, mod_y, modM_x, modM_y);

		// отобразить всю эту мазню
		graphics.display();



		// выведение важной инфы в тайтл окна
		graphics.window->setTitle("x:" + std::to_string(view_c_x) + " y:" + std::to_string(view_c_y)
			+ " xs:" + std::to_string(view_size_x) + " ys:" + std::to_string(view_size_y)
			+ " max_iter:" + std::to_string(fractal.max_iterations) 
			+ " delta(sec): " + std::to_string(delta));

		// завершение кадра
		frame++;
		// штука для замера времени
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		delta = (double)(duration.count()) * 0.001 + 0.001;
		// подождать немного, что бы скорость не была бесконечной
		std::chrono::milliseconds timespan(int(1.0/fps*1000) - duration.count());
		std::this_thread::sleep_for(timespan);
	}

	return 0;
}

// обрабатывает нажатие кнопок, перемещает и масштабирует камеру и возвращает 1 если камера была перемещена
bool viewbox_input_handler(double delta) {
	// флаг того, нужно ли перерисовать фрактал
	bool isUpdated{ 0 };
	// считывание кнопок управления
	float dx = 0, dy = 0; double dzoom = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		isUpdated = 1;
		dx += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		isUpdated = 1;
		dx += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		isUpdated = 1;
		dy += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		isUpdated = 1;
		dy += -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		isUpdated = 1;
		dzoom += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) {
		isUpdated = 1;
		dzoom += -1;
	}

	// смещение левого верхнего угла камеры на скорость передвижения
	view_c_x += dx * movement_speed * view_size_x * delta;
	view_c_y += dy * movement_speed * view_size_y * delta;
	// изменение размеров камеры
	view_size_x *= 1.0 + dzoom * viewsize_scale_speed * delta;
	view_size_y *= 1.0 + dzoom * viewsize_scale_speed * delta;
	// камера зумится к ее углу, по этому ее нужно сдвинуть так, что бы она сохраняла центр
	double dVSx = view_size_x - view_size_x / (1.0 + dzoom * viewsize_scale_speed * delta);
	double dVSy = view_size_y - view_size_y / (1.0 + dzoom * viewsize_scale_speed * delta);
	view_c_x -= dVSx * 0.5;
	view_c_y += dVSy * 0.5;

	return isUpdated;
}

void current_point_handler(double delta) {

	// если нажата лкм
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){ 
		// определить положение на экране
		sf::Vector2i window_mouse_position = sf::Mouse::getPosition(*graphics.window);
		// перевести положение в положение математической точки
		double math_x = (double)window_mouse_position.x * R_WINDOW_X * view_size_x + view_c_x;
		double math_y = (WINDOW_Y - (double)window_mouse_position.y) * R_WINDOW_Y * view_size_y + view_c_y;
		// установить координаты полученой точки как координаты текущей точки
		current_start_point_x = math_x;
		current_start_point_y = math_y;
		current_point_x = math_x;
		current_point_y = math_y;

		// очистить вб для отрисовки линий от старых линий
		graphics.clear_line_fragment();
		// добавить первое звено
		graphics.add_line_fragment((current_point_x - view_c_x) * WINDOW_X / view_size_x, WINDOW_Y - (current_point_y - view_c_y) * WINDOW_Y / view_size_y);
	}
	
	// обработка текущей точки по тукущему фрактальному выражению
	double nx = Fractal::calculate_x(current_point_x, current_point_y, current_start_point_x, current_start_point_y);
	double ny = Fractal::calculate_y(current_point_x, current_point_y, current_start_point_x, current_start_point_y);

	graphics.add_line_fragment(
		(current_point_x - view_c_x) * WINDOW_X / view_size_x,
		WINDOW_Y - (current_point_y - view_c_y) * WINDOW_Y / view_size_y);

	current_point_x = nx; current_point_y = ny;	
}