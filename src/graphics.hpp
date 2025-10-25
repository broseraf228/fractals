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
	sf::VertexArray screen_va;

public:
	//������� ���� ��� ��������� �����
	sf::RenderWindow* window{nullptr};

	Graphics(int x, int y);

	//���������� 1 �������
	void draw_pixel(int x, int y, const sf::Color& color);
	void set_text(const std::string& s);

	//�������� �����, ���������� ��� �������
	void display();
};