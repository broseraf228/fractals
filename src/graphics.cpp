#include "graphics.hpp"

#include "world/world.hpp"
#include "bot/bot.hpp"

Graphics::Graphics(sf::RenderWindow* window, sf::Font* font) : window{ window }, font{ font } {
	
	text_info.setFont(*font);
	text_info.setPosition(1000, 10);
	text_info.setCharacterSize(16);
	text_info.setFillColor(sf::Color::Red);
	text_info.setString("1452345");

	world_va.setPrimitiveType(sf::Quads);
}

void Graphics::render_world(World* world, Vec2 start, Vec2 size, Vec2 offset){
	world_va.clear();
	world_va.resize(world->get_size().x * world->get_size().y * 4);

	int sy = world->get_size().y, sx = world->get_size().x;

	sf::Color COL;
	int index_offset;

	for (int x = 0; x < sx; x++) {
		for (int y = 0; y < sy; y++) {
			// нахождение индекса текущего вертекса
			index_offset = x * sy + y;
			index_offset *= 4;

			// поиск подходящего цвета
			if (world->get_cell_p(x, y) == nullptr) {
				COL = sf::Color(200, 200, 200);
			}
			else {
				COL = world->get_cell_p(x, y)->get_color();
			}

			world_va[index_offset].position.x = x * cell_size + offset.x;
			world_va[index_offset].position.y = y * cell_size + offset.y;

			world_va[index_offset + 1].position.x = x * cell_size + cell_size + offset.x;
			world_va[index_offset + 1].position.y = y * cell_size + offset.y;

			world_va[index_offset + 2].position.x = x * cell_size + cell_size + offset.x;
			world_va[index_offset + 2].position.y = y * cell_size + cell_size + offset.y;

			world_va[index_offset + 3].position.x = x * cell_size + offset.x;
			world_va[index_offset + 3].position.y = y * cell_size + cell_size + offset.y;

			world_va[index_offset].color = COL;
			world_va[index_offset + 1].color = COL;
			world_va[index_offset + 2].color = COL;
			world_va[index_offset + 3].color = COL;
		}
	}
	window->draw(world_va);
}

void Graphics::set_text(const std::string& s){
	text_info.setString(s);
}

void Graphics::display(){
	window->draw(text_info);
	window->display();
	window->clear();
}