#include "fractal.hpp"

#include <string>
#include <vector>
#include <math.h>

#include <iostream>

#include <SFML/Graphics.hpp>

#include "graphics.hpp"

extern Graphics graphics;

inline double Fractal::calculate_x(double x, double y, double cx, double cy) {
	//return x * x * x * x - 6 * x * x * y * y + y * y * y * y + cx;
	//return x*x*x*x*x - 10.0 * y*y *x*x*x - 5.0 *x * y*y*y*y + 0.28; 
	//return x * x - y * y + cx;
	return x * x - y * y + cx;
}
inline double Fractal::calculate_y(double x, double y, double cx, double cy) {
	//return 4 * x * x * x * y - 4 * x * y * y * y + cy;
	//return 5.0 * x*x*x*x * y + 10.0 * y*y*y * x*x + y*y*y*y*y + 0.1;
	//return 2 * x * y + + cy;
	return 2 * x * y + cy;
}

int Fractal::calculate_dot(double x, double y) {

	// C = x + iy
	double cx = x, cy = y;
	// Z = x + iy
	double nx = 0, ny = 0;

	int iteration = 0;
	while (iteration < (max_iterations + 1)) {
		nx = calculate_x(x, y, cx, cy);
		ny = calculate_y(x, y, cx, cy);

		if (nx * nx + ny * ny > 4) break; //если модуль координат полученной точки больше двух мы вышли из множества, а занчит нужно преравть цикл

		x = nx; y = ny;

		iteration++;
	}

	return iteration;
}

sf::Color Fractal::get_color(int iteration, int max_iteration) {

	float r = 0, g = 0, b = 0;

	double reduced_iter = (double)iteration / max_iteration;
	double log_reduced_iter = logf(iteration) / logf(max_iteration);

	r = 255.0 * (asin(reduced_iter) * logf(max_iteration) * sin(1 / ((1 - reduced_iter) * 10)));
	b = 255.0 * (asin(reduced_iter) * logf(max_iteration) * sin(1 / ((1 - reduced_iter) * 20)));

	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	if (r < 0) r = 0;
	if (g < 0) g = 0;
	if (b < 0) b = 0;

	if (max_iteration == iteration - 1) {
		r = 0; g = 0; b = 0;
	}
	return sf::Color(r, g, b, 255);
}

// координаты левого верхнего угла зоны просмотра, размеры зоны просмотра
void Fractal::generate_fractal(double x0, double y0, double view_size_x, double view_size_y, int window_size_x, int window_size_y) {
	for (int y = 0; y < window_size_y; y++) {
		for (int x = 0; x < window_size_x; x++) {

			// получить число итераций у этого конкретного пикселя, затем получить на его основе цвет, затем зарасить пиксель на экране
			graphics.draw_pixel(x, y, get_color(
				generate_pixel(x0, y0, view_size_x, view_size_y, window_size_x, window_size_y, x, y), max_iterations
			));
		}}

}

int Fractal::generate_pixel(double x0, double y0, double view_size_x, double view_size_y, int wsx, int wsy, int wpx, int wpy) {
	float r_win_x = 1.0 / wsx, r_win_y = 1.0 / wsy;

	double math_x = (double)wpx * r_win_x * view_size_x + x0; // приведение координат точки в окне к координатам на комплексной плоскости
	double math_y = (wsy - (double)wpy) * r_win_y * view_size_y + y0;

	return calculate_dot(math_x, math_y);
}

Fractal::Fractal() {};