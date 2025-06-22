#include "../include/vec2i.hpp"

inline int inr(int p, int s) {
	if (p < 0)
		return 0;
	if (p > s)
		return s;
	return p;
}


// VEC 2 ----------
Vec2* Vec2::viev_directions_8 = new Vec2[8]
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
Vec2* Vec2::viev_directions_4 = new Vec2[4]
{
	Vec2(1, 0),
	Vec2(0, 1),
	Vec2(-1, 0),
	Vec2(0, -1)
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
Vec2& Vec2::operator+=(const Vec2& v) {
	x += v.x; y += v.y;
	return *this;
}
Vec2 Vec2::operator-(const Vec2& vect) {
	return Vec2(x - vect.x, y - vect.y);
}
bool Vec2::operator==(const Vec2& v) {
	return x == v.x && y == v.y;
}