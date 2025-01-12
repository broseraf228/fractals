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
			mtrx[x][y] = (rand() % 100 ) * 0.001;
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

void uMtrx::multiplication(const uMtrx& matrix, const uVec& input_vector, uVec* output_vector, int offset){

	if (input_vector.size() != matrix.gsx())
		throw "size of input vector and matrix do not converge";

	int sy = matrix.gsy() + offset;
	while (sy >= output_vector->size())
		sy--; // 

	for (int m = 0; m < sy; m++) // iter for all output vector нгачиная со смещения

		for (int n = 0; n < matrix.gsx(); n++) { // iteration of output wector and add vector[x] * weight[x]
			output_vector->operator[](m + offset) += input_vector.at(n) * matrix.at(n).at(m);
		}
}

void uMtrx::print() {

	std::cout << "size: " << sx << " X " << sy << std::endl;

	for (int x = 0; x < sx; x++){
		for (int y = 0; y < sy; y++) {
			std::cout << "\t" << matrix[x][y] ;
		}
		std::cout << std::endl;
	}
}

int uMtrx::gsx() const {
	return sx;
}
int uMtrx::gsy() const {
	return sy;
}