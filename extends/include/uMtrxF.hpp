#pragma once

#include "uVecF.hpp"

struct uMtrxF {
public:

	uMtrxF();
	uMtrxF(const uMtrxF& other);
	uMtrxF(int sx, int sy, int value = 0);
	//
	// {[0 0], [0 1], [0 2]},
	// {[1 0], [1 1], [1 2]},
	// {[2 0], [2 1], [2 2]}
	//
	uMtrxF(const std::initializer_list<uVecF> & list);

	uMtrxF static get_random(int sx, int sy);

	uVecF& operator[](int index);
	const uVecF& at(int index) const;

	void print();

	int gsy() const;
	int gsx() const;

private:

	//
	// {[0 0], [0 1], [0 2]},
	// {[1 0], [1 1], [1 2]},
	// {[2 0], [2 1], [2 2]}
	//
	std::vector<uVecF> matrix{};

	int sx{0}, sy{0};
};