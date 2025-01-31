#include "bot.hpp"

#include "../world/world.hpp"
#include <SFML/Graphics.hpp>

Cell_I::Cell_I() {

};

snake_fragment::snake_fragment(const Vec2& pos) : position{pos} {

}
const sf::Color& snake_fragment::get_color() const{
	return sf::Color(50,150,50);
}

Snake::Snake(World* world, const Vec2& position) : world{ world } {

	// �������, ���� �� ����� ��������� ���� ���-��
	//if (world->get_cell_l(position) != nullptr){
	//	return;
	//}

	// ���������� �����
	alive = 1;

	// �������� ������ ��� ���������
	fragments = new snake_fragment[MAX_SNAKE_LENGHT];

	// �������� ������ ��������
	lenght++;
	fragments[0] = snake_fragment();
	fragments[0].position = position;
	// �������� ������ �������� �� �����
	world->set_cell_p(position.x, position.y, &fragments[0]);
}

void Snake::update() {
	move();
}

void Snake::move() {

	// ���� ����� ����� ��� �� ������
	if (world->get_cell_p(fragments[0].position + Vec2::viev_directions_4[direction]))
		return;

	// ������� � ����� ��������� ��������
	world->set_cell_p(fragments[lenght - 1].position, nullptr);

	// ������� ��� ��������� ����� ������
	for (int i = lenght - 1; i > 0; i--)
		fragments[i].position = fragments[i - 1].position;

	

	// �������� ������ �� ����������� �������
	fragments[0].position += Vec2::viev_directions_4[direction];
	// �������� �� ����� ��������� ������
	world->set_cell_p(fragments[0].position, fragments);
}