#include "../include/uMtrxF.hpp"
#include "../include/uVecF.hpp"

inline int inr(int p, int s) {
	if (p < 0)
		return 0;
	if (p > s)
		return s;
	return p;
}

// UVEC ----------
uVecF::uVecF() {
	numbers = std::vector<float>(0, 0);
}
uVecF::uVecF(const uVecF& other) {
	numbers = other.numbers;
}
uVecF::uVecF(int count, int number) {
	numbers = std::vector<float>(count, number);
}
uVecF::uVecF(const std::initializer_list<float>& list) {
	numbers = std::vector<float>(list);
}

void uVecF::apply_function(double (*func) (double), int offset) {
	for (int i = offset; i < numbers.size(); i++)
		numbers[i] = func(numbers[i]);
}

float& uVecF::operator[](int index) {
	return numbers[index];
}
float uVecF::at(int index) const {
	return numbers[index];
}

int uVecF::size() const {
	return numbers.size();
}

float uVecF::operator *(const uVecF& other) const
{
	if (numbers.size() != other.size()) {
		throw "Attempt to multiply vectors of different sizes";
		return 0;
	}

	float s = 0;
	for (int i = 0; i < numbers.size(); i++) {
		s += numbers[i] * other.at(i);
	}

	return s;
}

// multiply (*out_vec[ shift_out ]) <- vec[ shift_input : vec.size()] * mtrx 
void uVecF::mulOnuMtrxF(const uMtrxF& mtrx, uVecF* vec_inp, uVecF* vec_out, int shift_out) {

	if (!vec_inp) {
		throw "is not possible to access a input vector by pointer equal nullptr";
		return;
	}
	if (!vec_out) {
		throw "is not possible to access a output vector by pointer equal nullptr";
		return;
	}

	if ((vec_inp->size() != mtrx.gsx()) ||
		(vec_out->size() - shift_out != mtrx.gsy())) {
		throw "Attempt to multiply vector and matrix with mismatched sizes";
		return;
	}

	for (int i = 0; i < vec_out->size() - shift_out; i++) {
		(*vec_out)[i + shift_out] = (*vec_inp) * mtrx.at(i);
	}

}