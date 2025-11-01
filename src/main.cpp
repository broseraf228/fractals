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

#define WINDOW_X 1000
#define R_WINDOW_X 1/WINDOW_X
#define WINDOW_Y 1000
#define R_WINDOW_Y 1/WINDOW_Y

const int thread_count{ 10 };

// счетчик кадров, прошедших с начала выполнения программы
int frame = 0;
// стандартное время на кадр
double standart_delta = 1.0 / 30;
// дельта времени
double delta = standart_delta;

// кол-во итераций на точку
int MAX_iterations = 8;
// параметры положения камеры
double view_c_x = -3, view_c_y = -3;
double view_size_x = 6, view_size_y = 6;
// параметры изменеия параметров камеры
double movement_speed = 0.25; // screen size per frame
double viewsize_scale_speed = 0.5; // viewsize multiplayer per frame
// параметры текущей точки, которая нужна для визуализации конкретного места в множестве 
double current_point_x = 0, current_point_y = 0;
double current_start_point_x = 0, current_start_point_y = 0;

Graphics graphics(WINDOW_X, WINDOW_Y);
Sounds sounds{};

void generate_fractal(double, double, double, double);
bool viewbox_input_handler(double);
void current_point_handler(double);

// главные фрактальные функции

float ccx = 0; float ccy = 0;
inline double calculate_x(double x, double y, double cx, double cy) {
	//return x * x * x * x - 6 * x * x * y * y + y * y * y * y + cx;
	//return x*x*x*x*x - 10.0 * y*y *x*x*x - 5.0 *x * y*y*y*y + 0.28; 
	//return x * x - y * y + cx;
	return x * x - y * y + cx;
}
inline double calculate_y(double x, double y, double cx, double cy) {
	//return 4 * x * x * x * y - 4 * x * y * y * y + cy;
	//return 5.0 * x*x*x*x * y + 10.0 * y*y*y * x*x + y*y*y*y*y + 0.1;
	//return 2 * x * y + + cy;
	return 2 * x * y + cy;
}


int main(int argc, char* argv[])
{
	std::cout << "Control settings:\n";
	std::cout << "arrows - movement\n";
	std::cout << "R Shift / R Ctrl - zoom\n";
	std::cout << "L Shift / L Ctrl - iterations per point\n";

	generate_fractal(view_c_x, view_c_y, view_size_x, view_size_y);

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			ccx+=0.01;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			ccx -= 0.01;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			ccy += 0.01;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			ccy -= 0.01;
		}

		// обработка ввода на изменение кол ва итераций
		bool isupd{ 0 };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			MAX_iterations++;
			isupd = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			MAX_iterations--;
			isupd = 1;
		}

		// обработка ввода на изменение положения и зума камеры и обновление фрактала в случае необходимости
		if(viewbox_input_handler(delta) || (isupd))
			generate_fractal(view_c_x, view_c_y, view_size_x, view_size_y);

		// выведение важной инфы в тайтл окна
		graphics.window->setTitle("x:" + std::to_string(view_c_x) + " y:" + std::to_string(view_c_y)
								+ " xs:" + std::to_string(view_size_x) + " ys:" + std::to_string(view_size_y) 
								+ " max_iter:" + std::to_string(MAX_iterations));

		// обработка текущей отображаемой точки
		current_point_handler(delta);

		graphics.display();
		
		frame++;

		// штука для замера времени
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
		delta = (float)duration.count() / 1000;
		// подождать немного, что бы скорость не была бесконечной
		std::chrono::milliseconds timespan((int)standart_delta * 1000 - duration.count());
		std::this_thread::sleep_for(timespan);
	}

	return 0;
}

// обрабатывает нажатие кнопок, перемещает и масштабирует камеру и возвращает 1 если камера была перемещена
bool viewbox_input_handler(double delta) {
	// флаг того, нужно ли перерисовать фрактал
	bool isUpdated{ 0 };
	// считывание кнопок управления
	int dx = 0, dy = 0; double dzoom = 0;
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
	view_c_y -= dVSy * 0.5;

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
	double nx = calculate_x(current_point_x, current_point_y, current_start_point_x, current_start_point_y);
	double ny = calculate_y(current_point_x, current_point_y, current_start_point_x, current_start_point_y);

	graphics.add_line_fragment(
		(current_point_x - view_c_x) * WINDOW_X / view_size_x,
		WINDOW_Y - (current_point_y - view_c_y) * WINDOW_Y / view_size_y);

	current_point_x = nx; current_point_y = ny;	
}

int calculate_dot(double x, double y) {

	// C = x + iy
	double cx = x, cy = y;
	// Z = x + iy
	double nx=0, ny=0;

	int iteration = 0;
	while (iteration < (MAX_iterations + 1)) {
		nx = calculate_x(x, y, cx, cy);
		ny = calculate_y(x, y, cx, cy);

		if (nx * nx + ny * ny > 4) break; //если модуль координат полученной точки больше двух мы вышли из множества, а занчит нужно преравть цикл

		x = nx; y = ny;

		iteration++;
	}

	return iteration;
}

sf::Color get_color_by_iter(int iteration, int max_iteration){

	sf::Color res(0,0,0,255);

	double reduced_iter = (double)iteration / max_iteration;
	
	res.r = 255 * powf(reduced_iter, 1.5);
	res.b = 255 * asin(reduced_iter) / 3.14;

	if (max_iteration == iteration-1)
		res = sf::Color(0, 0, 0, 255);

	return res;
}

// генерирует фрактал с y0 по y1 линию на экране
void generate_part_of_fractal(double c_x, double c_y, double view_size_x, double view_size_y, int y0, int y1) {
	for (int y = y0; y < y1; y++) {
		for (int x = 0; x < WINDOW_X; x++) {

			double math_x = (double)x * R_WINDOW_X * view_size_x + c_x; // приведение координат точки в окне к координатам на комплексной плоскости
			double math_y = (WINDOW_Y - (double)y) * R_WINDOW_Y * view_size_y + c_y;

			graphics.draw_pixel(x, y, get_color_by_iter(calculate_dot(math_x, math_y), MAX_iterations));
		}

	}
}

// координаты левого верхнего угла зоны просмотра, размеры зоны просмотра
void generate_fractal(double c_x, double c_y, double view_size_x, double view_size_y) {
	std::vector<std::thread> threads;
	threads.resize(thread_count);

	int lines_per_thread = WINDOW_Y / thread_count-1;

	for (int i = 0; i < thread_count; i++) {
		threads[i] = std::thread(generate_part_of_fractal, c_x, c_y, view_size_x, view_size_y, i * lines_per_thread, (i+1) * lines_per_thread);
	}
	for (int i = 0; i < thread_count; i++) {
		threads[i].join();
	}

}

void generate_linear_sample(std::vector<sf::Int16>* sample, double a0, double a1){
	double step = (a1 - a0) / sample->size();
	for (int i = 0; i < sample->size(); i++) {
		(*sample)[i] = (a0 + (double)i * step) * 1000;
	}
}