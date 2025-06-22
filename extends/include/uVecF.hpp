#pragma once

#include <initializer_list>
#include <vector>

struct uMtrxF;

struct uVecF {
private:

	std::vector<float> numbers{};

public:
	uVecF();
	uVecF(const uVecF& other);
	uVecF(int count, int value);
	uVecF(const std::initializer_list<float>& list);

	// use function for all elements of vector
	void apply_function(double (*func) (double), int offset = 0);

	float operator *(const uVecF& other) const;

	// multiply (*out_vec[ shift_out ]) <- vec[ shift_input : vec.size()] * mtrx 
	static void mulOnuMtrxF(const uMtrxF&, uVecF* vec_inp, uVecF* vec_out, int shift_out = 0);

	float& operator[](int index);
	float at(int index) const;

	int size() const;
};