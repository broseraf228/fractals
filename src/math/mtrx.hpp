#pragma once

#include "vec.hpp"

struct uMtrx {


	uMtrx();
	uMtrx(const uMtrx& other);
	uMtrx(int sx, int sy, int value = 0);
	uMtrx(const std::initializer_list<uVec> & list);

	uMtrx static get_random(int sx, int sy);

	uVec& operator[](int index);
	const uVec& at(int index) const;

	// multiply matrix on vector
	uVec operator*(const uVec& vector);

	// write mtrx * iVec in oVec with offset by begin of oVec
	void static multiplication(const uMtrx& matrix, const uVec& input_vector, uVec* output_vector, int offset = 0);

	void print();

	int gsy() const;
	int gsx() const;

private:

	/*
	*	|	--- номер числа во входном векторе ---> A
	*	|
	*	|	___	___
	*	|	n11 n21 ... ...
	*	|	n12 n22
	*	|	n13 n23
	*	|	... ...
	*	|	___ ___
	*	|
	*	|
	*	номер числа в выходном векторе
	*	B
	*   [A][B]
	*/
	std::vector<uVec> matrix{};

	int sx{0}, sy{0};
};