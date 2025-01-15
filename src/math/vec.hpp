#pragma once

#include <initializer_list>
#include <vector>


inline int inr(int p, int s);

struct Vec2 {
public:
	Vec2(int scallar = 0);
	Vec2(int x, int y);

	int x, y;

	Vec2 operator+(const Vec2&);
	Vec2 operator-(const Vec2&);
	Vec2 operator*(float);
	Vec2 operator/(float);
	bool operator==(const Vec2&);

	static Vec2* viev_directions;
};


struct uVec {
private:

	std::vector<float> numbers{};
	int s{ 0 };

public:
	uVec();
	uVec(const uVec& other);
	uVec(int count, int value);
	uVec(float* list, int size);
	uVec(const std::initializer_list<float>& list);

	// use function for all elements of vector
	void apply_function(float (*func) (float), int offset = 0);

	float& operator[](int index);
	float at(int index) const;

	int size() const;

	void print() const;
};