#include "sound.hpp"

Sounds::Sounds(){
	samples = std::vector<sf::Int16>(0, 0);
}

void Sounds::generate_samples(double x0, double x1, double delta){

	int sample_size = 44100 * delta;
	samples.resize(sample_size);

	double shift = (x1 - x0) / sample_size;
	for (int i = 0; i < sample_size; i++) {
		samples[i] = (x0 + shift * i) * 3000;
	}
}

sf::Sound Sounds::play_sound() {

	
	buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);

	sf::Sound the_sound;
	the_sound.setBuffer(buffer);
	return the_sound;
}