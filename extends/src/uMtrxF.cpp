#include "../include/uMtrxF.hpp"

#include "iostream"

uMtrxF::uMtrxF() {
	matrix = {};
}
uMtrxF::uMtrxF(const uMtrxF& other){
	sx = other.sx;
	sy = other.sy;
	matrix = other.matrix;
}
uMtrxF::uMtrxF(int sx, int sy, int value) : sx{ sx }, sy{ sy } {
	matrix = std::vector<uVecF>(sy, uVecF(sx, value));
}
uMtrxF::uMtrxF(const std::initializer_list<uVecF>& list) {
	matrix = list;
	sx = matrix[0].size();
	sy = matrix.size();
}

uMtrxF uMtrxF::get_random(int sx, int sy) {
	uMtrxF mtrx(sx, sy);
	for (int y = 0; y < sy; y++) {
		for (int x = 0; x < sx; x++) {
			mtrx[y][x] = ((rand() % 1000 ) * 0.001 - 0.5) * 2;
		}
	}
	return mtrx;
}

uVecF& uMtrxF::operator[](int index){
	return matrix[index];
}
const uVecF& uMtrxF::at(int index) const {
	return matrix[index];
}

void uMtrxF::print() {

	std::cout << "size: " << sx << " X " << sy << std::endl;

	for (int x = 0; x < sx; x++){
		for (int y = 0; y < sy; y++) {
			std::cout << "\t" << matrix[x][y] ;
		}
		std::cout << std::endl;
	}
}

int uMtrxF::gsx() const {
	return sx;
}
int uMtrxF::gsy() const {
	return sy;
}