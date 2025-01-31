#pragma once

#include <SFML/Graphics.hpp>
class World;

// �������� ����� ����������
class App { 
	// SINGLETON
private: 
	// ��������� �� ������������ ��������� ����� ������
	static App* self;
public:
	//������� ������������ ��������� ������
	static int Init(char* path);
	// �������� ������������ ��������� ������ ����� �������
	static App* get_self();


	// OTHER
private:
	// ���� �� ����� � ����������� ������
	char* path; 
	// ����� ��������� ��� �������� ������� 
	App(char* path);

	// GRAPHICS

	// ���� ��� ���������
	sf::RenderWindow* window;
	sf::VertexArray world_va{};

	void render_world();

	// World
	World* world;
public:
	// ������ ����������
	int run(); 
};