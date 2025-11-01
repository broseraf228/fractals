#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class World;

class Graphics {
private:
	std::string path;

	//������
	sf::Font* font;

	// interface components
	sf::Text text_info;

	// �������� ��� ��������� ����
	sf::VertexArray fractal_va;
	int sound_va_size{20};
	sf::VertexArray sound_va;

public:
	//������� ���� ��� ��������� �����
	sf::RenderWindow* window{nullptr};

	Graphics(int x, int y);

	//���������� 1 �������
	void draw_pixel(int x, int y, const sf::Color& color);
	void set_text(const std::string& s);

	void add_line_fragment(int x, int y);
	void clear_line_fragment();

	//�������� �����, ���������� ��� �������
	void display();
};