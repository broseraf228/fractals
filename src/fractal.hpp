#pragma once

namespace sf {
	class Color;
}

class Fractal {
	
	// генерирует один конкретный пиксель на экране
	int generate_pixel(double x0, double y0, double view_size_x, double view_size_y, int wsx, int wsy, int wpx, int wpy);
	
	// вычисляет конкретную точку
	int calculate_dot(double x, double y);

	// возвращает цвет конкретного пикселя
	sf::Color get_color(int iteration, int max_iteration);

public:
	Fractal();

	int max_iterations{ 32 };
	void generate_fractal(double x0, double y0, double view_size_x, double view_size_y, int window_size_x, int window_size_y);

	static inline double calculate_x(double x, double y, double cx, double cy);
	static inline double calculate_y(double x, double y, double cx, double cy);
};