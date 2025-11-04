#include "graphics.hpp"
#include <iostream>

std::string base_shader = 
"\
#version 330 core\n\
\
precision mediump float;\n\
\
\
void main() {\
	gl_FragColor = vec4(1.0,0.0,0.0,1.0);\
}\
";

Graphics::Graphics(int x, int y){

	window = new sf::RenderWindow(sf::VideoMode(x, y), "fractals");

	fractal_va.setPrimitiveType(sf::Points);
	fractal_va.resize(window->getSize().x * window->getSize().y);

	for(int y = 0; y < window->getSize().y; y++)
		for (int x = 0; x < window->getSize().x; x++) {
			fractal_va[window->getSize().x * y + x].position.x = x;
			fractal_va[window->getSize().x * y + x].position.y = y;
		}

	sound_va.setPrimitiveType(sf::LinesStrip);
	sound_va.resize(sound_va_size);
	for (int i = 0; i < sound_va_size; i++) {
		fractal_va[i].color = sf::Color(255 / sound_va_size * i);
	}
	clear_line_fragment();
}

void Graphics::draw_pixel(int x, int y, const sf::Color& color){
	fractal_va[window->getSize().x * y + x].color = color;
}

void Graphics::set_text(const std::string& s){
	//text_info.setString(s);
}

void Graphics::display(){
	
	// texture for fractal shader
	sf::Texture tex;
	tex.create(window->getSize().x, window->getSize().y);
	sf::Sprite spr(tex);
	// draw fractal shader
	window->draw(spr, &fractal_shader);

	window->draw(sound_va);
	window->display();
	window->clear();
}

void Graphics::add_line_fragment(int x, int y) {
	for (int i = 0; i < sound_va_size-1; i++) {
		sound_va[i] = sound_va[i + 1];
	}

	sound_va[sound_va_size-1].position.x = x;
	sound_va[sound_va_size-1].position.y = y;
	sound_va[sound_va_size - 1].color.a = 255;
}
void Graphics::clear_line_fragment(){
	for (int i = 0; i < sound_va_size; i++) {
		//sound_va[i].position.x = window->getSize().x * 0.5;
		//sound_va[i].position.y = window->getSize().y * 0.5;
		sound_va[i].color.a = 0;
	}
}

void Graphics::set_shader(const std::string& shader_text){

	if (!fractal_shader.loadFromMemory(shader_text, sf::Shader::Fragment)) {
		std::cout << "fractal shader is not loaded !!!\n\n";
		return;
	}
	std::cout << "fractal shader was loaded\n\n";
}
void Graphics::set_shader_params(int frame, int max_iterations, double x0, double y0, double vsx, double vsy, float mod_x, float mod_y, float modM_x, float modM_y){
	fractal_shader.setParameter("current_frame", frame);
	fractal_shader.setParameter("max_iterations", max_iterations);
	fractal_shader.setParameter("math_pos", sf::Vector2f(x0,y0));
	fractal_shader.setParameter("math_viewsize", sf::Vector2f(vsx, vsy));
	fractal_shader.setParameter("modificators", modM_x, modM_y, mod_x, mod_y);

	fractal_shader.setParameter("resolution", sf::Vector2f(window->getSize()));
}