#include "vec.hpp"

#include "iostream"


inline int inr(int p, int s) {
	if (p < 0)
		return 0;
	if (p > s)
		return s;
	return p;
}


// VEC 2 ----------
Vec2* Vec2::viev_directions = new Vec2[8]
{
	Vec2(1, 0),
	Vec2(1, 1),
	Vec2(0, 1),
	Vec2(-1, 1),
	Vec2(-1, 0),
	Vec2(-1, -1),
	Vec2(0, 1),
	Vec2(1, -1)
};

Vec2::Vec2(int scallar) {
	x = scallar, y = scallar;
}
Vec2::Vec2(int x, int y) : x{ x }, y{ y }
{

}

Vec2 Vec2::operator*(float scallar) {
	return Vec2(x * scallar, y * scallar);
}
Vec2 Vec2::operator/(float scallar) {
	return Vec2(x / scallar, y / scallar);
}
Vec2 Vec2::operator+(const Vec2& vect) {
	return Vec2(x + vect.x, y + vect.y);
}
Vec2 Vec2::operator-(const Vec2& vect) {
	return Vec2(x - vect.x, y - vect.y);
}
bool Vec2::operator==(const Vec2& v) {
	return x == v.x && y == v.y;
}

// UVEC ----------
uVec::uVec(){
	numbers = std::vector<float>(0, 0);
	s = 0;
}
uVec::uVec(const uVec& other){
	numbers = other.numbers;
	s = other.s;
}
uVec::uVec(int count, int number){
	numbers = std::vector<float>(count, number);
	s = count;
}
uVec::uVec(float* list, int size) {
	numbers = std::vector<float>(size, 0);
	for (int i = 0; i < size; i++) {
		numbers[i] = list[i];
	}
	s = size;
}
uVec::uVec(const std::initializer_list<float>& list) {
	numbers = std::vector<float>(list);
	s = numbers.size();
}

void uVec::apply_function(float (*func) (float), int offset) {
	for (int i = offset; i < s; i++)
		numbers[i] = func(numbers[i]);
}

float& uVec::operator[](int index) {
	return numbers[index];
}
float uVec::at(int index) const {
	return numbers[index];
}

int uVec::size() const {
	return s;
} 

void uVec::print() const {

	for (int x = 0; x < s; x++) {
		std::cout << " | " << numbers[x] ;
	}
	std::cout << std::endl;
}