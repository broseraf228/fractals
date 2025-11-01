#pragma once

#include <SFML/Audio.hpp>

class Sounds {
private:
	std::vector<sf::Int16> samples;
	sf::SoundBuffer buffer;

public:
	Sounds();

	void generate_samples(double x0, double x1, double delta);
	// возвращает сгенерированный звук
	sf::Sound play_sound();
};
