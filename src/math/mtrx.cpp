#include "mtrx.hpp"

#include "iostream"

uMtrx::uMtrx() {
	matrix = {};
}
uMtrx::uMtrx(const uMtrx& other){
	sx = other.sx;
	sy = other.sy;
	matrix = other.matrix;
}
uMtrx::uMtrx(int sx, int sy, int value) : sx{ sx }, sy{ sy } {
	matrix = std::vector<uVec>(sx, uVec(sy, value));
}
uMtrx::uMtrx(const std::initializer_list<uVec>& list) {
	matrix = list;
}

uMtrx uMtrx::get_random(int sx, int sy) {
	uMtrx mtrx(sx, sy);
	for (int y = 0; y < sy; y++) {
		for (int x = 0; x < sx; x++) {
			mtrx[x][y] = (rand() % 1000 ) / 1000.0;
		}
	}
	return mtrx;
}

uVec& uMtrx::operator[](int index){
	return matrix[index];
}
const uVec& uMtrx::at(int index) const {
	return matrix[index];
}

uVec uMtrx::operator*(const uVec& vector) {
	uVec b(sy, 0);
	for (int m = 0; m < sy; m++) // iter for all output vector

		for (int n = 0; n < sx; n++) { // iteration of add vector[x] * weight[x]
			b[m] += vector.at(n) * matrix[n][m];
		}

	return b;
}

void uMtrx::print() {

	std::cout << "size: " << sx << " X " << sy << std::endl;

	for (int y = 0; y < sy; y++){
		for (int x = 0; x < sx; x++) {
			std::cout << " | " << matrix[x][y] ;
		}
		std::cout << std::endl;
	}
}