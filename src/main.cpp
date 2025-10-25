#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "graphics.hpp"

#define WINDOW_X 1000
#define R_WINDOW_X 1/WINDOW_X
#define WINDOW_Y 1000
#define R_WINDOW_Y 1/WINDOW_Y

int MAX_iterations = 8;
double view_c_x = -1, view_c_y = -1;
double view_size_x = 2, view_size_y = 2;
double current_scale = 1;

double movement_speed = 0.5; // screen size per frame
double viewsize_scale_speed = 1; // viewsize multiplayer per frame

Graphics graphics(WINDOW_X, WINDOW_Y);

void generate_fractal(double, double, double, double);
bool viewbox_input_handler(double);

int main(int argc, char* argv[])
{
	std::cout << "Control settings:\n";
	std::cout << "arrows - movement\n";
	std::cout << "R Shift / R Ctrl - zoom\n";
	std::cout << "L Shift / L Ctrl - iterations per point\n";

	generate_fractal(view_c_x, view_c_y, view_size_x, view_size_y);

	while (graphics.window->isOpen())
	{
		// проверяем все события окна которые сработали с момента последней итерации цикла
		sf::Event event;
		while (graphics.window->pollEvent(event))
		{
			// событие "закрытия": мы закрываем окно
			if (event.type == sf::Event::Closed)
				graphics.window->close();
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
		if(viewbox_input_handler(0.1) || (isupd))
			generate_fractal(view_c_x, view_c_y, view_size_x, view_size_y);

		// выведение важной инфы в тайтл окна
		graphics.window->setTitle("x:" + std::to_string(view_c_x) + " y:" + std::to_string(view_c_y)
								+ " xs:" + std::to_string(view_size_x) + " ys:" + std::to_string(view_size_y) 
								+ " max_iter:" + std::to_string(MAX_iterations));

		graphics.display();

		std::chrono::milliseconds timespan(100);
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

int calculate_dot(double x, double y) {

	// C = x + iy
	double cx = x, cy = y;
	// Z = x + iy
	double nx=0, ny=0;

	int iteration = 0;
	while (iteration < (MAX_iterations + 1)) {
		nx = x*x - y*y + cx; //вычисление координат Z_n+1 = Z_n ^2 + C
		ny = 2*x*y + cy;

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

// координаты левого верхнего угла зоны просмотра, размеры зоны просмотра
void generate_fractal(double c_x, double c_y, double view_size_x, double view_size_y) {
	for (int y = 0; y < WINDOW_Y; y++) {
		for (int x = 0; x < WINDOW_X; x++) {

			double math_x = (double)x * R_WINDOW_X * view_size_x + c_x; // приведение координат точки в окне к координатам на комплексной плоскости
			double math_y = (WINDOW_Y - (double)y) * R_WINDOW_Y * view_size_y + c_y;

			graphics.draw_pixel(x, y, get_color_by_iter(calculate_dot(math_x, math_y), MAX_iterations));
		}
		
	}
}