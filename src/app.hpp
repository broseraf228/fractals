#pragma once

#include "../extends/include/vec2i.hpp"
#include <SFML/Graphics.hpp>

class World;
class Graphics;

// �������� ����� ����������
class App { 
	// SINGLETON
private: 
	// ��������� �� ������������ ��������� ����� ������
	static App* self;
public:
	//������� ������������ ��������� ������
	static int Init(const std::string& path);
	// �������� ������������ ��������� ������ ����� �������
	static App* get_self();

	~App();

	// OTHER
private:
	// ���� �� ����� � ����������� ������
	std::string path;
	// ����� ��������� ��� �������� ������� 
	App(const std::string& path);

	Graphics* graphics{nullptr};

	sf::Font* font;

	// ���� ��� ���������
	sf::RenderWindow* window;

	int cell_size = 12;

	void handle_events();

	// World
	World* world;

	// ����� ������� ����������
	bool is_manual_operation{ 0 };
	// id ��������� ������
	int selected_snake{0};
	// ���������� ������ �� ������� �������� �����
	Vec2 mouse_position{ 0,0 };
	// ���������� ������ �� ������� �������� �����
	Vec2 selected_cell{ 0,0 };
public:
	// ������ ����������
	int run(); 
};